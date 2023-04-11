/*
 *
 * Copyright 2023 Mark Grimes. Most/all of the work is copied from Apple so copyright is theirs if they want it.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// CoreVideo/CVMetalTextureCache.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "CoreVideoDefines.hpp"
#include "CVReturn.hpp"
#include "CVImageBuffer.hpp"
#include "CVMetalTexture.hpp"
#include <Metal/MTLDevice.hpp>
#include <Metal/MTLPixelFormat.hpp>

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace CV
{
	struct MetalTextureCache;
	using MetalTextureCacheRef = MetalTextureCache*;

	Return metalTextureCacheCreate( CFAllocatorRef allocator,
	                                CFDictionaryRef cacheAttributes,
	                                MTL::Device* metalDevice,
	                                CFDictionaryRef textureAttributes,
	                                MetalTextureCacheRef* cacheOut );

	Return metalTextureCacheCreateTextureFromImage( CFAllocatorRef allocator,
	                                                MetalTextureCacheRef textureCache,
	                                                ImageBufferRef sourceImage,
	                                                CFDictionaryRef textureAttributes,
	                                                MTL::PixelFormat pixelFormat,
	                                                size_t width,
	                                                size_t height,
	                                                size_t planeIndex,
	                                                MetalTextureRef* textureOut );
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#if defined(CV_PRIVATE_IMPLEMENTATION)

_CV_EXTERN CV::Return CVMetalTextureCacheCreate( CFAllocatorRef allocator,
                                                 CFDictionaryRef cacheAttributes,
                                                 MTL::Device* metalDevice,
                                                 CFDictionaryRef textureAttributes,
                                                 CV::MetalTextureCacheRef* cacheOut );

CV::Return CV::metalTextureCacheCreate( CFAllocatorRef allocator,
                                        CFDictionaryRef cacheAttributes,
                                        MTL::Device* metalDevice,
                                        CFDictionaryRef textureAttributes,
                                        MetalTextureCacheRef* cacheOut )
{
	return ::CVMetalTextureCacheCreate( allocator, cacheAttributes, metalDevice, textureAttributes, cacheOut );
}

_CV_EXTERN CV::Return CVMetalTextureCacheCreateTextureFromImage( CFAllocatorRef allocator,
																 CV::MetalTextureCacheRef textureCache,
																 CV::ImageBufferRef sourceImage,
																 CFDictionaryRef textureAttributes,
																 MTL::PixelFormat pixelFormat,
																 size_t width,
																 size_t height,
																 size_t planeIndex,
																 CV::MetalTextureRef* textureOut );

CV::Return CV::metalTextureCacheCreateTextureFromImage( CFAllocatorRef allocator,
													    MetalTextureCacheRef textureCache,
													    ImageBufferRef sourceImage,
													    CFDictionaryRef textureAttributes,
													    MTL::PixelFormat pixelFormat,
													    size_t width,
													    size_t height,
													    size_t planeIndex,
													    MetalTextureRef* textureOut )
{
    return ::CVMetalTextureCacheCreateTextureFromImage( allocator, textureCache, sourceImage, textureAttributes, pixelFormat, width, height, planeIndex, textureOut );
}

#endif // CV_PRIVATE_IMPLEMENTATION
