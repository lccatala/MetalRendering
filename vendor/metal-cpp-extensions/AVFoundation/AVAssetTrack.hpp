/*
 *
 * Copyright 2023 Mark Grimes. Most/all of the work is copied from Apple so copyright is theirs if they want it.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *	 http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// AVFoundation/AVAssetTrack.hpp
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
	class URL;
	class Array;
} // end of namespace NS

namespace AV
{
	class SampleCursor;
} // end of namespace AV

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace AV
{
	class AssetTrack : public NS::Copying<AssetTrack>
	{
	public:
		MediaType mediaType() const;
		NS::Array* formatDescriptions() const;
		bool isPlayable() const;
		bool isDecodable() const;
		bool isEnabled() const;
		bool isSelfContained() const;
		long long totalSampleDataLength() const;
		float estimatedDataRate() const;
		NS::String * languageCode() const;
		NS::String * extendedLanguageTag() const;
		CGSize naturalSize() const;
		CGAffineTransform preferredTransform() const;
		float preferredVolume() const;
		bool hasAudioSampleDependencies() const;
		float nominalFrameRate() const;
		bool requiresFrameReordering() const;
		NS::Array* segments() const;
		NS::Array* commonMetadata() const;
		NS::Array* metadata() const;
		NS::Array* availableMetadataFormats() const;
		NS::Array* availableTrackAssociationTypes() const;
		SampleCursor* makeSampleCursorAtFirstSampleInDecodeOrder() const;
		SampleCursor* makeSampleCursorAtLastSampleInDecodeOrder() const;
		bool canProvideSampleCursors() const;
	}; // end of declaration of class Asset

} // end of namespace AV

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

_AV_INLINE AV::MediaType AV::AssetTrack::mediaType() const
{
	return NS::Object::sendMessage<MediaType>( this, _AV_PRIVATE_SEL( mediaType ) );
}

_AV_INLINE NS::Array* AV::AssetTrack::formatDescriptions() const
{
	return NS::Object::sendMessage<NS::Array*>( this, _AV_PRIVATE_SEL( formatDescriptions ) );
}

_AV_INLINE bool AV::AssetTrack::isPlayable() const
{
	return NS::Object::sendMessage<bool>( this, _AV_PRIVATE_SEL( isPlayable ) );
}

_AV_INLINE bool AV::AssetTrack::isDecodable() const
{
	return NS::Object::sendMessage<bool>( this, _AV_PRIVATE_SEL( isDecodable ) );
}

_AV_INLINE bool AV::AssetTrack::isEnabled() const
{
	return NS::Object::sendMessage<bool>( this, _AV_PRIVATE_SEL( isEnabled ) );
}

_AV_INLINE bool AV::AssetTrack::isSelfContained() const
{
	return NS::Object::sendMessage<bool>( this, _AV_PRIVATE_SEL( isSelfContained ) );
}

_AV_INLINE long long AV::AssetTrack::totalSampleDataLength() const
{
	return NS::Object::sendMessage<long long>( this, _AV_PRIVATE_SEL( totalSampleDataLength ) );
}

_AV_INLINE float AV::AssetTrack::estimatedDataRate() const
{
	return NS::Object::sendMessage<float>( this, _AV_PRIVATE_SEL( estimatedDataRate ) );
}

_AV_INLINE NS::String* AV::AssetTrack::languageCode() const
{
	return NS::Object::sendMessage<NS::String*>( this, _AV_PRIVATE_SEL( languageCode ) );
}

_AV_INLINE NS::String* AV::AssetTrack::extendedLanguageTag() const
{
	return NS::Object::sendMessage<NS::String*>( this, _AV_PRIVATE_SEL( extendedLanguageTag ) );
}

_AV_INLINE CGSize AV::AssetTrack::naturalSize() const
{
	return NS::Object::sendMessage<CGSize>( this, _AV_PRIVATE_SEL( naturalSize ) );
}

_AV_INLINE CGAffineTransform AV::AssetTrack::preferredTransform() const
{
	return NS::Object::sendMessage<CGAffineTransform>( this, _AV_PRIVATE_SEL( preferredTransform ) );
}

_AV_INLINE float AV::AssetTrack::preferredVolume() const
{
	return NS::Object::sendMessage<float>( this, _AV_PRIVATE_SEL( preferredVolume ) );
}

_AV_INLINE bool AV::AssetTrack::hasAudioSampleDependencies() const
{
	return NS::Object::sendMessage<bool>( this, _AV_PRIVATE_SEL( hasAudioSampleDependencies ) );
}

_AV_INLINE float AV::AssetTrack::nominalFrameRate() const
{
	return NS::Object::sendMessage<float>( this, _AV_PRIVATE_SEL( nominalFrameRate ) );
}

_AV_INLINE bool AV::AssetTrack::requiresFrameReordering() const
{
	return NS::Object::sendMessage<bool>( this, _AV_PRIVATE_SEL( requiresFrameReordering ) );
}

_AV_INLINE NS::Array* AV::AssetTrack::segments() const
{
	return NS::Object::sendMessage<NS::Array*>( this, _AV_PRIVATE_SEL( segments ) );
}

_AV_INLINE NS::Array* AV::AssetTrack::commonMetadata() const
{
	return NS::Object::sendMessage<NS::Array*>( this, _AV_PRIVATE_SEL( commonMetadata ) );
}

_AV_INLINE NS::Array* AV::AssetTrack::metadata() const
{
	return NS::Object::sendMessage<NS::Array*>( this, _AV_PRIVATE_SEL( metadata ) );
}

_AV_INLINE NS::Array* AV::AssetTrack::availableMetadataFormats() const
{
	return NS::Object::sendMessage<NS::Array*>( this, _AV_PRIVATE_SEL( availableMetadataFormats ) );
}

_AV_INLINE NS::Array* AV::AssetTrack::availableTrackAssociationTypes() const
{
	return NS::Object::sendMessage<NS::Array*>( this, _AV_PRIVATE_SEL( availableTrackAssociationTypes ) );
}

_AV_INLINE AV::SampleCursor* AV::AssetTrack::makeSampleCursorAtFirstSampleInDecodeOrder() const
{
	return NS::Object::sendMessage<AV::SampleCursor*>( this, _AV_PRIVATE_SEL( makeSampleCursorAtFirstSampleInDecodeOrder ) );
}

_AV_INLINE AV::SampleCursor* AV::AssetTrack::makeSampleCursorAtLastSampleInDecodeOrder() const
{
	return NS::Object::sendMessage<AV::SampleCursor*>( this, _AV_PRIVATE_SEL( makeSampleCursorAtLastSampleInDecodeOrder ) );
}

_AV_INLINE bool AV::AssetTrack::canProvideSampleCursors() const
{
	return NS::Object::sendMessage<bool>( this, _AV_PRIVATE_SEL( canProvideSampleCursors ) );
}
