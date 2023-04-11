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
// CoreML/MLMultiArray.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <Foundation/NSObject.hpp>
#include "CoreMLDefines.hpp"
#include <CoreVideo/CVPixelBuffer.hpp>

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace ML
{
	_ML_ENUM( NS::Integer, MultiArrayDataType )
	{
		MultiArrayDataTypeDouble  = 0x10000 | 64,
		MultiArrayDataTypeFloat64 API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x10000 | 64,
		MultiArrayDataTypeFloat32 = 0x10000 | 32,
		MultiArrayDataTypeFloat16 API_AVAILABLE(macos(12.0), ios(16.0), watchos(9.0), tvos(16.0)) = 0x10000 | 16,
		MultiArrayDataTypeFloat   API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x10000 | 32,
		MultiArrayDataTypeInt32   = 0x20000 | 32,
	} API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

	class MultiArray : NS::Referencing<MultiArray>
	{
	public:
		void* dataPointer();
		ML::MultiArrayDataType dataType();
		NS::Array* shape();
		NS::Array* strides();
		NS::Integer count();
		CV::PixelBufferRef pixelBuffer();
	}; // end of class MultiArray
} // end of namespace ML


// ------------------------------------------------------------

_ML_INLINE void* ML::MultiArray::dataPointer()
{
	return Object::sendMessage<void *>( this, _ML_PRIVATE_SEL(dataPointer) );
}

_ML_INLINE ML::MultiArrayDataType ML::MultiArray::dataType()
{
	return Object::sendMessage<ML::MultiArrayDataType>( this, _ML_PRIVATE_SEL(dataType) );
}

_ML_INLINE NS::Array* ML::MultiArray::shape()
{
	return Object::sendMessage<NS::Array*>( this, _ML_PRIVATE_SEL(shape) );
}

_ML_INLINE NS::Array* ML::MultiArray::strides()
{
	return Object::sendMessage<NS::Array*>( this, _ML_PRIVATE_SEL(strides) );
}

_ML_INLINE NS::Integer ML::MultiArray::count()
{
	return Object::sendMessage<NS::Integer>( this, _ML_PRIVATE_SEL(count) );
}

_ML_INLINE CV::PixelBufferRef ML::MultiArray::pixelBuffer()
{
	return Object::sendMessage<CV::PixelBufferRef>( this, _ML_PRIVATE_SEL(pixelBuffer) );
}
