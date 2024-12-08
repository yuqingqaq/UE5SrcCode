// Copyright Epic Games, Inc. All Rights Reserved.

#include "Insights/ViewModels/ThreadTrackEvent.h"

#include "Insights/ViewModels/GraphTrack.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

INSIGHTS_IMPLEMENT_RTTI(FThreadTrackEvent)

////////////////////////////////////////////////////////////////////////////////////////////////////

FThreadTrackEvent::FThreadTrackEvent(const TSharedRef<const FBaseTimingTrack> InTrack, double InStartTime, double InEndTime, uint32 InDepth)
	: FTimingEvent(InTrack, InStartTime, InEndTime, InDepth)
{}

////////////////////////////////////////////////////////////////////////////////////////////////////

uint32 FThreadTrackEvent::GetTimerIndex() const
{
	return TimerIndex;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FThreadTrackEvent::SetTimerIndex(uint32 InTimerIndex)
{
	TimerIndex = InTimerIndex;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

uint32 FThreadTrackEvent::GetTimerId() const
{
	return (uint32)GetType();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FThreadTrackEvent::SetTimerId(uint32 InTimerId)
{
	SetType(InTimerId);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
