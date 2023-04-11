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
// AVFoundation/AVAssetReaderOutput.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "AVDefines.hpp"
#include "AVFoundationPrivate.hpp"
#include "AVMediaFormat.hpp"
#include "Foundation/NSObject.hpp"

namespace NS
{
	class Array;
	class Dictionary;
	class String;
} // end of namespace NS

namespace AV
{
	class AssetTrack;
}

namespace CM
{
	struct SampleBuffer;
	using SampleBufferRef = SampleBuffer*;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace AV
{
	class AssetReaderOutput : public NS::Referencing<AssetReaderOutput>
	{
	public:
		CM::SampleBufferRef copyNextSampleBuffer();

		MediaType mediaType() const;
		bool alwaysCopiesSampleData() const;
		void setAlwaysCopiesSampleData( bool alwaysCopiesSampleData );
		void resetForReadingTimeRanges( NS::Array* timeRanges );
		void markConfigurationAsFinal();
		bool supportsRandomAccess() const;
		void setSupportsRandomAccess( bool supportsRandomAccess );
	}; // end of class AVAssetReaderOutput

	class AssetReaderTrackOutput : public AssetReaderOutput
	{
	public:
		static AssetReaderTrackOutput* assetReaderTrackOutput();
		static AssetReaderTrackOutput* assetReaderTrackOutput( AssetTrack* track, NS::Dictionary* outputSettings );
		AssetReaderTrackOutput* init();
		AssetReaderTrackOutput* init( AssetTrack* track, NS::Dictionary* outputSettings );
		AssetTrack* track();
		NS::Dictionary* outputSettings();
	}; // end of declaration of class AVAssetReaderTrackOutput


} // end of namespace AV

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

_AV_INLINE CM::SampleBufferRef AV::AssetReaderOutput::copyNextSampleBuffer()
{
	return NS::Object::sendMessage<CM::SampleBufferRef>( this, _AV_PRIVATE_SEL( copyNextSampleBuffer ) );
}

_AV_INLINE AV::MediaType AV::AssetReaderOutput::mediaType() const
{
	return NS::Object::sendMessage<AV::MediaType>( this, _AV_PRIVATE_SEL( mediaType ) );
}

_AV_INLINE bool AV::AssetReaderOutput::alwaysCopiesSampleData() const
{
	return NS::Object::sendMessage<bool>( this, _AV_PRIVATE_SEL( alwaysCopiesSampleData ) );
}

_AV_INLINE void AV::AssetReaderOutput::setAlwaysCopiesSampleData( bool alwaysCopiesSampleData )
{
	return NS::Object::sendMessage<void>( this, _AV_PRIVATE_SEL( setAlwaysCopiesSampleData_ ), alwaysCopiesSampleData );
}

_AV_INLINE void AV::AssetReaderOutput::resetForReadingTimeRanges( NS::Array* timeRanges )
{
	return NS::Object::sendMessage<void>( this, _AV_PRIVATE_SEL( resetForReadingTimeRanges_ ), timeRanges );
}

_AV_INLINE void AV::AssetReaderOutput::markConfigurationAsFinal()
{
	return NS::Object::sendMessage<void>( this, _AV_PRIVATE_SEL( markConfigurationAsFinal ) );
}

_AV_INLINE bool AV::AssetReaderOutput::supportsRandomAccess() const
{
	return NS::Object::sendMessage<bool>( this, _AV_PRIVATE_SEL( supportsRandomAccess ) );
}

_AV_INLINE void AV::AssetReaderOutput::setSupportsRandomAccess( bool supportsRandomAccess )
{
	return NS::Object::sendMessage<void>( this, _AV_PRIVATE_SEL( setSupportsRandomAccess_ ), supportsRandomAccess );
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

_AV_INLINE AV::AssetReaderTrackOutput* AV::AssetReaderTrackOutput::assetReaderTrackOutput()
{
	return NS::Object::sendMessage<AV::AssetReaderTrackOutput*>( _AV_PRIVATE_CLS( AVAssetReaderTrackOutput ), _AV_PRIVATE_SEL( assetReaderTrackOutput ) );
}

_AV_INLINE AV::AssetReaderTrackOutput* AV::AssetReaderTrackOutput::assetReaderTrackOutput( AssetTrack* track, NS::Dictionary* outputSettings )
{
	return NS::Object::sendMessage<AV::AssetReaderTrackOutput*>( _AV_PRIVATE_CLS( AVAssetReaderTrackOutput ), _AV_PRIVATE_SEL( assetReaderTrackOutputWithTrack_outputSettings_ ), track, outputSettings );
}

_AV_INLINE AV::AssetReaderTrackOutput* AV::AssetReaderTrackOutput::init()
{
	return NS::Object::sendMessage<AV::AssetReaderTrackOutput*>( this, _AV_PRIVATE_SEL( init ) );
}

_AV_INLINE AV::AssetReaderTrackOutput* AV::AssetReaderTrackOutput::init( AssetTrack* track, NS::Dictionary* outputSettings )
{
	return NS::Object::sendMessage<AV::AssetReaderTrackOutput*>( this, _AV_PRIVATE_SEL( initWithTrack_outputSettings_ ), track, outputSettings );
}

_AV_INLINE AV::AssetTrack* AV::AssetReaderTrackOutput::track()
{
	return NS::Object::sendMessage<AV::AssetTrack*>( this, _AV_PRIVATE_SEL( track ) );
}

_AV_INLINE NS::Dictionary* AV::AssetReaderTrackOutput::outputSettings()
{
	return NS::Object::sendMessage<NS::Dictionary*>( this, _AV_PRIVATE_SEL( outputSettings ) );
}
