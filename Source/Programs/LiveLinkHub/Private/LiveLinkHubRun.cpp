// Copyright Epic Games, Inc. All Rights Reserved.

#include "LiveLinkHubRun.h"

#include "Misc/App.h"
#include "Misc/PackageName.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformApplicationMisc.h"
#include "HAL/PlatformFileManager.h"
#include "Interfaces/IPluginManager.h"
#include "LaunchEngineLoop.h"
#include "Misc/CommandLine.h"

#ifndef WITH_ASSET_LOADING_AUDIT
#define WITH_ASSET_LOADING_AUDIT 0
#endif

#ifndef COOKED_EDITOR_DISTRIBUTION
#define COOKED_EDITOR_DISTRIBUTION 0
#endif

DEFINE_LOG_CATEGORY_STATIC(LogLiveLinkHub, Log, All);

int32 RunLiveLinkHub(const TCHAR* CommandLine)
{
	FTaskTagScope Scope(ETaskTag::EGameThread);

#if WITH_ASSET_LOADING_AUDIT
	FCoreDelegates::OnSyncLoadPackage.AddLambda([](const FString& PackageName)
		{
			UE_LOG(LogLiveLinkHub, Display, TEXT("Audit: Loaded %s"), *PackageName);
		});
#endif

	// Must match the path in LiveLinkHubStaging.cs / StageLiveLinkHub.automation.cs
	const FString RemappedFolder = FPaths::EngineDir() / TEXT("Programs/LiveLinkHub/Staged");

	const FString RemappedConfigs = RemappedFolder / TEXT("Config");
	const FString RemappedContent = RemappedFolder / TEXT("Content");
	const FString RemappedPlugins = RemappedFolder / TEXT("Plugins");

	// Needs to be initialized early for mount points / plugin search paths.
	FCommandLine::Set(CommandLine);

#if COOKED_EDITOR_DISTRIBUTION

	/** If LLH runs in a cooked editor distribution, then we must mount our RemappedEngineFiles folder to the /Engine/ folder in order to
	 * 	have access to the uncooked content necessary for starting LiveLinkHub.
	 */
	if (!IFileManager::Get().DirectoryExists(*RemappedContent))
	{
		IFileManager::Get().MakeDirectory(*RemappedContent, true);
	}

	if (!IFileManager::Get().DirectoryExists(*RemappedPlugins))
	{
		IFileManager::Get().MakeDirectory(*RemappedPlugins, true);
	}

	/** Only copy the configs if they aren't present to prevent overwriting them. */
	const FString TargetConfigPath = FPaths::EngineDir() / TEXT("Config/Base.ini");
	if (!IFileManager::Get().FileExists(*TargetConfigPath) && IFileManager::Get().DirectoryExists(*RemappedConfigs))
	{
		FPlatformFileManager::Get().GetPlatformFile().CopyDirectoryTree(*(FPaths::EngineDir() / TEXT("Config")), *RemappedConfigs, false);
	}

	// Map the engine's content to LiveLinkHub's content folder
	FPackageName::RegisterMountPoint(TEXT("/Engine/"), RemappedFolder / TEXT("Content"));
	FPackageName::RegisterMountPoint(TEXT("/Engine/Plugins/"), RemappedFolder / TEXT("Plugins"));

	// This is needed to ensure that content generated by the hub will be discoverable (ie. LiveLink recordings)
	const FString GameContentPath = FPaths::Combine(FPlatformProcess::UserSettingsDir(), *FApp::GetEpicProductIdentifier(), TEXT("LiveLinkHub"), TEXT("Content"));
	FPackageName::RegisterMountPoint(TEXT("/Game/"), GameContentPath);
#endif

	// Needed to avoid assertion in scoped slow task
	GWarn = FPlatformApplicationMisc::GetFeedbackContext();

	// Add staged plugins to the search path so LLH can find the manifest and content.
	IPluginManager::Get().AddPluginSearchPath(RemappedPlugins, /*bShouldRefresh*/ true);

	// Disable this when going through PreInit to prevent the console window from appearing.
	GIsSilent = true;

	// Start up the main loop, adding some extra command line arguments:
	const int32 Result = GEngineLoop.PreInit(*FString::Printf(TEXT("%s %s"), CommandLine, TEXT("LiveLinkHubCommandlet -Messaging -DDC=NoShared -NoShaderCompile")));

	if (Result != 0)
	{
		UE_LOG(LogLiveLinkHub, Error, TEXT("EngineLoop PreInit failed!"));
		return Result;
	}

	GEngineLoop.Exit();

	return Result;
}