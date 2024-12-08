// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MetalRHIPrivate.h"
#include "HAL/LowLevelMemTracker.h"
#include "Apple/AppleLLM.h"

@interface FMetalDeallocHandler : FApplePlatformObject<NSObject>
{
	dispatch_block_t Block;
}
-(instancetype)initWithBlock:(dispatch_block_t)InBlock;
-(void)dealloc;
@end

#if ENABLE_LOW_LEVEL_MEM_TRACKER

#define LLM_SCOPE_METAL(Tag) LLM_SCOPE((ELLMTag)Tag)
#define LLM_PLATFORM_SCOPE_METAL(Tag) LLM_PLATFORM_SCOPE((ELLMTag)Tag)

enum class ELLMTagMetal : LLM_TAG_TYPE
{
	Buffers = (LLM_TAG_TYPE)ELLMTagApple::AppleMetalTagsStart,
	Textures,
	Heaps,
	RenderTargets,
	
	Count
};

static_assert((int32)ELLMTagMetal::Count <= (int32)ELLMTagApple::AppleMetalTagsEnd, "too many ELLMTagMetal tags. Need to increase LLM_TAG_APPLE_NUM_METAL_TAGS_RESERVED");

namespace MetalLLM
{
	void Initialise();
}

#else

#define LLM_SCOPE_METAL(...)
#define LLM_PLATFORM_SCOPE_METAL(...)

#endif		// #if ENABLE_LOW_LEVEL_MEM_TRACKER

// These work without the LLM module
namespace MetalLLM
{
	void LogAllocTexture(MTL::Device* Device, MTL::TextureDescriptor* Desc, MTL::Texture* Texture);
	void LogAllocBuffer(MTL::Device* Device, FMetalBufferPtr Buffer);
    void LogAllocBufferNative(MTL::Device* Device, MTLBufferPtr Buffer);
	void LogAllocHeap(MTL::Device* Device, MTL::Heap* Heap);
	
	void LogAliasTexture(MTL::Texture* Texture);
}


