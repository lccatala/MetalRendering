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
#include <Metal/MTLTexture.hpp>

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace CV
{
	struct MetalTexture : public NS::Referencing<MetalTexture>
	{
		// Opaque type
	};
	using MetalTextureRef = MetalTexture*;

	MTL::Texture* metalTextureGetTexture( MetalTextureRef image );
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#if defined(CV_PRIVATE_IMPLEMENTATION)

_CV_EXTERN MTL::Texture* CVMetalTextureGetTexture( CV::MetalTextureRef image );

MTL::Texture* CV::metalTextureGetTexture( MetalTextureRef image )
{
	return ::CVMetalTextureGetTexture( image );
}

#endif // CV_PRIVATE_IMPLEMENTATION
