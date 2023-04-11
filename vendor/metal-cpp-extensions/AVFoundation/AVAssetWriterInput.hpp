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
// AVFoundation/AVAssetWriterInput.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <Foundation/NSObject.hpp>
#include <CoreVideo/CVPixelBuffer.hpp>
#include <CoreMedia/CMTime.h>
#include "AVMediaFormat.hpp"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace NS
{
	class Array;
	class Dictionary;
} // end of namespace NS

namespace CM
{
	struct SampleBuffer;
	using SampleBufferRef = SampleBuffer*;

	struct FormatDescription;
	using FormatDescriptionRef = FormatDescription*;
} // end of namespace CM

namespace AV
{
	class TimedMetadataGroup;
} // end of namespace AV

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace AV
{
	class AssetWriterInput : public NS::Referencing<AssetWriterInput>
	{
	public:
		AV::AssetWriterInput* init();
		static AV::AssetWriterInput* assetWriterInputWithMediaTypeOutputSettings(AV::MediaType mediaType, NS::Dictionary* outputSettings);
		static AV::AssetWriterInput* assetWriterInputWithMediaTypeOutputSettingsSourceFormatHint(AV::MediaType mediaType, NS::Dictionary* outputSettings, CM::FormatDescriptionRef sourceFormatHint);
		AV::AssetWriterInput* initWithMediaTypeOutputSettings(AV::MediaType mediaType, NS::Dictionary* outputSettings);
		AV::AssetWriterInput* initWithMediaTypeOutputSettingsSourceFormatHint(AV::MediaType mediaType, NS::Dictionary* outputSettings, CM::FormatDescriptionRef sourceFormatHint);
		BOOL appendSampleBuffer(CM::SampleBufferRef sampleBuffer);
		void markAsFinished();
		AV::MediaType mediaType();
		NS::Dictionary* outputSettings();
		CM::FormatDescriptionRef sourceFormatHint();
		NS::Array* metadata();
		void setMetadata(NS::Array* metadata);
		BOOL isReadyForMoreMediaData();
		BOOL expectsMediaDataInRealTime();
		void setExpectsMediaDataInRealTime(BOOL expectsMediaDataInRealTime);
	}; // end of class AssetWriterInput

	class AssetWriterInputPassDescription : public NS::Referencing<AssetWriterInput>
	{
	public:
		AV::AssetWriterInputPassDescription* init();
		NS::Array* sourceTimeRanges();
	}; // end of class AssetWriterInputPassDescription

	class AssetWriterInputPixelBufferAdaptor : public NS::Referencing<AssetWriterInput>
	{
	public:
		AV::AssetWriterInputPixelBufferAdaptor* init();
		static AV::AssetWriterInputPixelBufferAdaptor* assetWriterInputPixelBufferAdaptorWithAssetWriterInputSourcePixelBufferAttributes(AV::AssetWriterInput* input, NS::Dictionary* sourcePixelBufferAttributes);
		AV::AssetWriterInputPixelBufferAdaptor* initWithAssetWriterInputSourcePixelBufferAttributes(AV::AssetWriterInput* input, NS::Dictionary* sourcePixelBufferAttributes);
		BOOL appendPixelBufferWithPresentationTime(CV::PixelBufferRef pixelBuffer, CMTime presentationTime);
		AV::AssetWriterInput* assetWriterInput();
		NS::Dictionary* sourcePixelBufferAttributes();
	}; // end of class AssetWriterInputPixelBufferAdaptor

	class AssetWriterInputMetadataAdaptor : public NS::Referencing<AssetWriterInput>
	{
	public:
		AV::AssetWriterInputMetadataAdaptor* init();
		static AV::AssetWriterInputMetadataAdaptor* assetWriterInputMetadataAdaptorWithAssetWriterInput(AV::AssetWriterInput* input);
		AV::AssetWriterInputMetadataAdaptor* initWithAssetWriterInput(AV::AssetWriterInput* input);
		BOOL appendTimedMetadataGroup(AV::TimedMetadataGroup* timedMetadataGroup);
		AV::AssetWriterInput* assetWriterInput();
	}; // end of class AssetWriterInputMetadataAdaptor

	class AssetWriterInputCaptionAdaptor : public NS::Referencing<AssetWriterInput>
	{
	public:
		AV::AssetWriterInputCaptionAdaptor* init();
		static AV::AssetWriterInputCaptionAdaptor* assetWriterInputCaptionAdaptorWithAssetWriterInput(AV::AssetWriterInput* input);
		AV::AssetWriterInputCaptionAdaptor* initWithAssetWriterInput(AV::AssetWriterInput* input);
		AV::AssetWriterInput* assetWriterInput();
	}; // end of class AssetWriterInputCaptionAdaptor

} // end of namespace AV


// ------------------------------------------------------------

_AV_INLINE AV::AssetWriterInput* AV::AssetWriterInput::init()
{
	return Object::sendMessage<AV::AssetWriterInput*>( this, _AV_PRIVATE_SEL(init) );
}

_AV_INLINE AV::AssetWriterInput* AV::AssetWriterInput::assetWriterInputWithMediaTypeOutputSettings(AV::MediaType mediaType, NS::Dictionary* outputSettings)
{
	return Object::sendMessage<AV::AssetWriterInput*>( _AV_PRIVATE_CLS(AVAssetWriterInput), _AV_PRIVATE_SEL(assetWriterInputWithMediaType_outputSettings_), mediaType, outputSettings );
}

_AV_INLINE AV::AssetWriterInput* AV::AssetWriterInput::assetWriterInputWithMediaTypeOutputSettingsSourceFormatHint(AV::MediaType mediaType, NS::Dictionary* outputSettings, CM::FormatDescriptionRef sourceFormatHint)
{
	return Object::sendMessage<AV::AssetWriterInput*>( _AV_PRIVATE_CLS(AVAssetWriterInput), _AV_PRIVATE_SEL(assetWriterInputWithMediaType_outputSettings_sourceFormatHint_), mediaType, outputSettings, sourceFormatHint );
}

_AV_INLINE AV::AssetWriterInput* AV::AssetWriterInput::initWithMediaTypeOutputSettings(AV::MediaType mediaType, NS::Dictionary* outputSettings)
{
	return Object::sendMessage<AV::AssetWriterInput*>( this, _AV_PRIVATE_SEL(initWithMediaType_outputSettings_), mediaType, outputSettings );
}

_AV_INLINE AV::AssetWriterInput* AV::AssetWriterInput::initWithMediaTypeOutputSettingsSourceFormatHint(AV::MediaType mediaType, NS::Dictionary* outputSettings, CM::FormatDescriptionRef sourceFormatHint)
{
	return Object::sendMessage<AV::AssetWriterInput*>( this, _AV_PRIVATE_SEL(initWithMediaType_outputSettings_sourceFormatHint_), mediaType, outputSettings, sourceFormatHint );
}

_AV_INLINE BOOL AV::AssetWriterInput::appendSampleBuffer(CM::SampleBufferRef sampleBuffer)
{
	return Object::sendMessage<BOOL>( this, _AV_PRIVATE_SEL(appendSampleBuffer_), sampleBuffer );
}

_AV_INLINE void AV::AssetWriterInput::markAsFinished()
{
	return Object::sendMessage<void>( this, _AV_PRIVATE_SEL(markAsFinished) );
}

_AV_INLINE AV::MediaType AV::AssetWriterInput::mediaType()
{
	return Object::sendMessage<AV::MediaType>( this, _AV_PRIVATE_SEL(mediaType) );
}

_AV_INLINE NS::Dictionary* AV::AssetWriterInput::outputSettings()
{
	return Object::sendMessage<NS::Dictionary*>( this, _AV_PRIVATE_SEL(outputSettings) );
}

_AV_INLINE CM::FormatDescriptionRef AV::AssetWriterInput::sourceFormatHint()
{
	return Object::sendMessage<CM::FormatDescriptionRef>( this, _AV_PRIVATE_SEL(sourceFormatHint) );
}

_AV_INLINE NS::Array* AV::AssetWriterInput::metadata()
{
	return Object::sendMessage<NS::Array*>( this, _AV_PRIVATE_SEL(metadata) );
}

_AV_INLINE void AV::AssetWriterInput::setMetadata(NS::Array* metadata)
{
	return Object::sendMessage<void>( this, _AV_PRIVATE_SEL(setMetadata_), metadata );
}

_AV_INLINE BOOL AV::AssetWriterInput::isReadyForMoreMediaData()
{
	return Object::sendMessage<BOOL>( this, _AV_PRIVATE_SEL(isReadyForMoreMediaData) );
}

_AV_INLINE BOOL AV::AssetWriterInput::expectsMediaDataInRealTime()
{
	return Object::sendMessage<BOOL>( this, _AV_PRIVATE_SEL(expectsMediaDataInRealTime) );
}

_AV_INLINE void AV::AssetWriterInput::setExpectsMediaDataInRealTime(BOOL expectsMediaDataInRealTime)
{
	return Object::sendMessage<void>( this, _AV_PRIVATE_SEL(setExpectsMediaDataInRealTime_), expectsMediaDataInRealTime );
}

// ------------------------------------------------------------

_AV_INLINE AV::AssetWriterInputPassDescription* AV::AssetWriterInputPassDescription::init()
{
	return Object::sendMessage<AV::AssetWriterInputPassDescription*>( this, _AV_PRIVATE_SEL(init) );
}

_AV_INLINE NS::Array* AV::AssetWriterInputPassDescription::sourceTimeRanges()
{
	return Object::sendMessage<NS::Array*>( this, _AV_PRIVATE_SEL(sourceTimeRanges) );
}

// ------------------------------------------------------------

_AV_INLINE AV::AssetWriterInputPixelBufferAdaptor* AV::AssetWriterInputPixelBufferAdaptor::init()
{
	return Object::sendMessage<AV::AssetWriterInputPixelBufferAdaptor*>( this, _AV_PRIVATE_SEL(init) );
}

_AV_INLINE AV::AssetWriterInputPixelBufferAdaptor* AV::AssetWriterInputPixelBufferAdaptor::assetWriterInputPixelBufferAdaptorWithAssetWriterInputSourcePixelBufferAttributes(AV::AssetWriterInput* input, NS::Dictionary* sourcePixelBufferAttributes)
{
	return Object::sendMessage<AV::AssetWriterInputPixelBufferAdaptor*>( _AV_PRIVATE_CLS(AVAssetWriterInputPixelBufferAdaptor), _AV_PRIVATE_SEL(assetWriterInputPixelBufferAdaptorWithAssetWriterInput_sourcePixelBufferAttributes_), input, sourcePixelBufferAttributes );
}

_AV_INLINE AV::AssetWriterInputPixelBufferAdaptor* AV::AssetWriterInputPixelBufferAdaptor::initWithAssetWriterInputSourcePixelBufferAttributes(AV::AssetWriterInput* input, NS::Dictionary* sourcePixelBufferAttributes)
{
	return Object::sendMessage<AV::AssetWriterInputPixelBufferAdaptor*>( this, _AV_PRIVATE_SEL(initWithAssetWriterInput_sourcePixelBufferAttributes_), input, sourcePixelBufferAttributes );
}

_AV_INLINE BOOL AV::AssetWriterInputPixelBufferAdaptor::appendPixelBufferWithPresentationTime(CV::PixelBufferRef pixelBuffer, CMTime presentationTime)
{
	return Object::sendMessage<BOOL>( this, _AV_PRIVATE_SEL(appendPixelBuffer_withPresentationTime_), pixelBuffer, presentationTime );
}

_AV_INLINE AV::AssetWriterInput* AV::AssetWriterInputPixelBufferAdaptor::assetWriterInput()
{
	return Object::sendMessage<AV::AssetWriterInput*>( this, _AV_PRIVATE_SEL(assetWriterInput) );
}

_AV_INLINE NS::Dictionary* AV::AssetWriterInputPixelBufferAdaptor::sourcePixelBufferAttributes()
{
	return Object::sendMessage<NS::Dictionary*>( this, _AV_PRIVATE_SEL(sourcePixelBufferAttributes) );
}

// ------------------------------------------------------------

_AV_INLINE AV::AssetWriterInputMetadataAdaptor* AV::AssetWriterInputMetadataAdaptor::init()
{
	return Object::sendMessage<AV::AssetWriterInputMetadataAdaptor*>( this, _AV_PRIVATE_SEL(init) );
}

_AV_INLINE AV::AssetWriterInputMetadataAdaptor* AV::AssetWriterInputMetadataAdaptor::assetWriterInputMetadataAdaptorWithAssetWriterInput(AV::AssetWriterInput* input)
{
	return Object::sendMessage<AV::AssetWriterInputMetadataAdaptor*>( _AV_PRIVATE_CLS(AVAssetWriterInputMetadataAdaptor), _AV_PRIVATE_SEL(assetWriterInputMetadataAdaptorWithAssetWriterInput_), input );
}

_AV_INLINE AV::AssetWriterInputMetadataAdaptor* AV::AssetWriterInputMetadataAdaptor::initWithAssetWriterInput(AV::AssetWriterInput* input)
{
	return Object::sendMessage<AV::AssetWriterInputMetadataAdaptor*>( this, _AV_PRIVATE_SEL(initWithAssetWriterInput_), input );
}

_AV_INLINE BOOL AV::AssetWriterInputMetadataAdaptor::appendTimedMetadataGroup(AV::TimedMetadataGroup* timedMetadataGroup)
{
	return Object::sendMessage<BOOL>( this, _AV_PRIVATE_SEL(appendTimedMetadataGroup_), timedMetadataGroup );
}

_AV_INLINE AV::AssetWriterInput* AV::AssetWriterInputMetadataAdaptor::assetWriterInput()
{
	return Object::sendMessage<AV::AssetWriterInput*>( this, _AV_PRIVATE_SEL(assetWriterInput) );
}

// ------------------------------------------------------------

_AV_INLINE AV::AssetWriterInputCaptionAdaptor* AV::AssetWriterInputCaptionAdaptor::init()
{
	return Object::sendMessage<AV::AssetWriterInputCaptionAdaptor*>( this, _AV_PRIVATE_SEL(init) );
}

_AV_INLINE AV::AssetWriterInputCaptionAdaptor* AV::AssetWriterInputCaptionAdaptor::assetWriterInputCaptionAdaptorWithAssetWriterInput(AV::AssetWriterInput* input)
{
	return Object::sendMessage<AV::AssetWriterInputCaptionAdaptor*>( _AV_PRIVATE_CLS(AVAssetWriterInputCaptionAdaptor), _AV_PRIVATE_SEL(assetWriterInputCaptionAdaptorWithAssetWriterInput_), input );
}

_AV_INLINE AV::AssetWriterInputCaptionAdaptor* AV::AssetWriterInputCaptionAdaptor::initWithAssetWriterInput(AV::AssetWriterInput* input)
{
	return Object::sendMessage<AV::AssetWriterInputCaptionAdaptor*>( this, _AV_PRIVATE_SEL(initWithAssetWriterInput_), input );
}

_AV_INLINE AV::AssetWriterInput* AV::AssetWriterInputCaptionAdaptor::assetWriterInput()
{
	return Object::sendMessage<AV::AssetWriterInput*>( this, _AV_PRIVATE_SEL(assetWriterInput) );
}
