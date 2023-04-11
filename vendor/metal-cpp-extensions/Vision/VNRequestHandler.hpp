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
// Vision/VNRequestHandler.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "VisionPrivate.hpp"
#include <Foundation/NSObject.hpp>
#include <CoreVideo/CVPixelBuffer.hpp>

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace NS
{
	class Array;
	class Error;
} // end of namespace NS

namespace CM
{
	struct SampleBuffer;
	using SampleBufferRef = SampleBuffer*;
} // end of namespace CM

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace VN
{
	class ImageRequestHandler : public NS::Referencing<ImageRequestHandler>
	{
	public:
		static ImageRequestHandler* alloc();
		ImageRequestHandler* init();
		ImageRequestHandler* init( CV::PixelBufferRef pixelBuffer, NS::Dictionary* options );
		ImageRequestHandler* init( NS::URL* imageURL, NS::Dictionary* options );
		ImageRequestHandler* init( NS::Data* imageData, NS::Dictionary* options );
		ImageRequestHandler* init( CM::SampleBufferRef sampleBuffer, NS::Dictionary* options );
		bool performRequests( NS::Array* requests, NS::Error** error );
	}; // end of class ImageRequestHandler

	class SequenceRequestHandler : public NS::Referencing<SequenceRequestHandler>
	{
	public:
		static SequenceRequestHandler* alloc();
		SequenceRequestHandler* init();

		bool performRequests( NS::Array* requests, CV::PixelBufferRef pixelBuffer, NS::Error** error );
		bool performRequests( NS::Array* requests, NS::URL* imageURL, NS::Error** error );
		bool performRequests( NS::Array* requests, NS::Data* imageData, NS::Error** error );
		bool performRequests( NS::Array* requests, CM::SampleBufferRef sampleBuffer, NS::Error** error );

	}; // end of class SequenceRequestHandler
} // end of namespace VN

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

_VN_INLINE VN::ImageRequestHandler* VN::ImageRequestHandler::alloc()
{
	return NS::Object::alloc<VN::ImageRequestHandler>( _VN_PRIVATE_CLS( VNImageRequestHandler ) );
}

_VN_INLINE VN::ImageRequestHandler* VN::ImageRequestHandler::init()
{
	return NS::Object::sendMessage<VN::ImageRequestHandler*>( this, _VN_PRIVATE_SEL( init ) );
}

_VN_INLINE VN::ImageRequestHandler* VN::ImageRequestHandler::init( CV::PixelBufferRef pixelBuffer, NS::Dictionary* options )
{
	return NS::Object::sendMessage<VN::ImageRequestHandler*>( this, _VN_PRIVATE_SEL( initWithCVPixelBuffer_options_ ), pixelBuffer, options );
}

_VN_INLINE VN::ImageRequestHandler* VN::ImageRequestHandler::init( NS::URL* imageURL, NS::Dictionary* options )
{
	return NS::Object::sendMessage<VN::ImageRequestHandler*>( this, _VN_PRIVATE_SEL( initWithURL_options_ ), imageURL, options );
}

_VN_INLINE VN::ImageRequestHandler* VN::ImageRequestHandler::init( NS::Data* imageData, NS::Dictionary* options )
{
	return NS::Object::sendMessage<VN::ImageRequestHandler*>( this, _VN_PRIVATE_SEL( initWithData_options_ ), imageData, options );
}

_VN_INLINE VN::ImageRequestHandler* VN::ImageRequestHandler::init( CM::SampleBufferRef sampleBuffer, NS::Dictionary* options )
{
	return NS::Object::sendMessage<VN::ImageRequestHandler*>( this, _VN_PRIVATE_SEL( initWithCMSampleBuffer_options_ ), sampleBuffer, options );
}

_VN_INLINE bool VN::ImageRequestHandler::performRequests( NS::Array* requests, NS::Error** error )
{
	return NS::Object::sendMessage<bool>( this, _VN_PRIVATE_SEL( performRequests_error_ ), requests, error );
}

// ------------------------------------------------------------

_VN_INLINE VN::SequenceRequestHandler* VN::SequenceRequestHandler::alloc()
{
	return NS::Object::alloc<VN::SequenceRequestHandler>( _VN_PRIVATE_CLS( VNSequenceRequestHandler ) );
}

_VN_INLINE VN::SequenceRequestHandler* VN::SequenceRequestHandler::init()
{
	return NS::Object::sendMessage<VN::SequenceRequestHandler*>( this, _VN_PRIVATE_SEL( init ) );
}

_VN_INLINE bool VN::SequenceRequestHandler::performRequests( NS::Array* requests, CV::PixelBufferRef pixelBuffer, NS::Error** error )
{
	return NS::Object::sendMessage<bool>( this, _VN_PRIVATE_SEL( performRequests_onCVPixelBuffer_error_ ), requests, pixelBuffer, error );
}

_VN_INLINE bool VN::SequenceRequestHandler::performRequests( NS::Array* requests, NS::URL* imageURL, NS::Error** error )
{
	return NS::Object::sendMessage<bool>( this, _VN_PRIVATE_SEL( performRequests_onImageURL_error_ ), requests, imageURL, error );
}

_VN_INLINE bool VN::SequenceRequestHandler::performRequests( NS::Array* requests, NS::Data* imageData, NS::Error** error )
{
	return NS::Object::sendMessage<bool>( this, _VN_PRIVATE_SEL( performRequests_onImageData_error_ ), requests, imageData, error );
}

_VN_INLINE bool VN::SequenceRequestHandler::performRequests( NS::Array* requests, CM::SampleBufferRef sampleBuffer, NS::Error** error )
{
	return NS::Object::sendMessage<bool>( this, _VN_PRIVATE_SEL( performRequests_onCMSampleBuffer_error_ ), requests, sampleBuffer, error );
}
