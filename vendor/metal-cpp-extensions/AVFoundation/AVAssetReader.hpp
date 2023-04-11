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
// AVFoundation/AVAsset.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "AVDefines.hpp"
#include "AVFoundationPrivate.hpp"
#include "Foundation/NSObject.hpp"

namespace NS
{
	class Array;
	class Error;
} // end of namespace NS

namespace AV
{
	class Asset;
	class AssetReaderOutput;
} // end of namespace AV

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace AV
{

	class AssetReader : public NS::Referencing<Asset>
	{
	public:
		static AssetReader* assetReader();
		static AssetReader* assetReader( Asset* asset, NS::Error** outError );
		AssetReader* init();
		AssetReader* init( Asset* asset, NS::Error** outError );
		bool canAddOutput( AssetReaderOutput* output );
		void addOutput( AssetReaderOutput* output );
		bool startReading();
		void cancelReading();
		Asset* asset();
		NS::Error* error();
		NS::Array* outputs();
	}; // end of declaration of class AssetReader

} // end of namespace AV

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

_AV_INLINE AV::AssetReader* AV::AssetReader::assetReader()
{
	return NS::Object::sendMessage<AV::AssetReader*>( _AV_PRIVATE_CLS( AVAssetReader ), _AV_PRIVATE_SEL( tracks ) );
}

_AV_INLINE AV::AssetReader* AV::AssetReader::assetReader( Asset* asset, NS::Error** outError )
{
	return NS::Object::sendMessage<AV::AssetReader*>( _AV_PRIVATE_CLS( AVAssetReader ), _AV_PRIVATE_SEL( assetReaderWithAsset_error_ ), asset, outError );
}

_AV_INLINE AV::AssetReader* AV::AssetReader::init()
{
	return NS::Object::sendMessage<AV::AssetReader*>( this, _AV_PRIVATE_SEL( init ) );
}

_AV_INLINE AV::AssetReader* AV::AssetReader::init( Asset* asset, NS::Error** outError )
{
	return NS::Object::sendMessage<AV::AssetReader*>( this, _AV_PRIVATE_SEL( initWithAsset_error_ ), asset, outError );
}

_AV_INLINE bool AV::AssetReader::canAddOutput( AssetReaderOutput* output )
{
	return NS::Object::sendMessage<bool>( this, _AV_PRIVATE_SEL( canAddOutput_ ), output );
}

_AV_INLINE void AV::AssetReader::addOutput( AssetReaderOutput* output )
{
	return NS::Object::sendMessage<void>( this, _AV_PRIVATE_SEL( addOutput_ ), output );
}

_AV_INLINE bool AV::AssetReader::startReading()
{
	return NS::Object::sendMessage<bool>( this, _AV_PRIVATE_SEL( startReading ) );
}

_AV_INLINE void AV::AssetReader::cancelReading()
{
	return NS::Object::sendMessage<void>( this, _AV_PRIVATE_SEL( cancelReading ) );
}

_AV_INLINE AV::Asset* AV::AssetReader::asset()
{
	return NS::Object::sendMessage<AV::Asset*>( this, _AV_PRIVATE_SEL( asset ) );
}

_AV_INLINE NS::Error* AV::AssetReader::error()
{
	return NS::Object::sendMessage<NS::Error*>( this, _AV_PRIVATE_SEL( error ) );
}

_AV_INLINE NS::Array* AV::AssetReader::outputs()
{
	return NS::Object::sendMessage<NS::Array*>( this, _AV_PRIVATE_SEL( outputs ) );
}
