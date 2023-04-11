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
// AVFoundation/AVAssetWriter.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <Foundation/NSObject.hpp>
#include <CoreMedia/CMTime.h>

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace NS
{
	class URL;
	class Error;
	class Dictionary;
} // end of namespace NS

namespace UT
{
	class Type;
} // end of namespace UT

namespace AV
{
	class AssetWriterInput;
} // end of namespace AV

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace AV
{
	_NS_ENUM( NS::Integer, AssetWriterStatus )
	{
		AssetWriterStatusUnknown = 0,
		AssetWriterStatusWriting = 1,
		AssetWriterStatusCompleted = 2,
		AssetWriterStatusFailed = 3,
		AssetWriterStatusCancelled = 4
	};

	class AssetWriter : public NS::Referencing<AssetWriter>
	{
	public:
		AV::AssetWriter* init();
		static AV::AssetWriter* alloc();
		static AV::AssetWriter* assetWriter(NS::URL* outputURL, AV::FileType outputFileType, NS::Error** outError);
		AV::AssetWriter* init(NS::URL* outputURL, AV::FileType outputFileType, NS::Error** outError);
		AV::AssetWriter* init(UT::Type* outputContentType);
		BOOL canApplyOutputSettingsForMediaType(NS::Dictionary* outputSettings, AV::MediaType mediaType);
		BOOL canAddInput(AV::AssetWriterInput* input);
		void addInput(AV::AssetWriterInput* input);
		BOOL startWriting();
		void startSessionAtSourceTime(CMTime startTime);
		void endSessionAtSourceTime(CMTime endTime);
		void cancelWriting();
		BOOL finishWriting();
		// void finishWritingWithCompletionHandler(void (^)(void) handler);
		NS::URL* outputURL();
		AV::FileType outputFileType();
		NS::Array* availableMediaTypes();
		AV::AssetWriterStatus status();
		NS::Error* error();
		NS::Array* metadata();
		void setMetadata(NS::Array* metadata);
		BOOL shouldOptimizeForNetworkUse();
		void setShouldOptimizeForNetworkUse(BOOL shouldOptimizeForNetworkUse);
		NS::URL* directoryForTemporaryFiles();
		void setDirectoryForTemporaryFiles(NS::URL* directoryForTemporaryFiles);
		NS::Array* inputs();
	}; // end of class AssetWriter

	class AssetWriterInputGroup : public NS::Referencing<AssetWriter>
	{
	public:
		AV::AssetWriterInputGroup* init();
		static AV::AssetWriterInputGroup* alloc();
		static AV::AssetWriterInputGroup* assetWriterInputGroup(NS::Array* inputs, AV::AssetWriterInput* defaultInput);
		AV::AssetWriterInputGroup* init(NS::Array* inputs, AV::AssetWriterInput* defaultInput);
		NS::Array* inputs();
		AV::AssetWriterInput* defaultInput();
	}; // end of class AssetWriterInputGroup

} // end of namespace AV


// ------------------------------------------------------------

_AV_INLINE AV::AssetWriter* AV::AssetWriter::init()
{
	return Object::sendMessage<AV::AssetWriter*>( this, _AV_PRIVATE_SEL(init) );
}

_AV_INLINE AV::AssetWriter* AV::AssetWriter::alloc()
{
	return Object::sendMessage<AV::AssetWriter*>( _AV_PRIVATE_CLS(AVAssetWriter), _AV_PRIVATE_SEL(new) );
}

_AV_INLINE AV::AssetWriter* AV::AssetWriter::assetWriter(NS::URL* outputURL, AV::FileType outputFileType, NS::Error** outError)
{
	return Object::sendMessage<AV::AssetWriter*>( _AV_PRIVATE_CLS(AVAssetWriter), _AV_PRIVATE_SEL(assetWriterWithURL_fileType_error_), outputURL, outputFileType, outError );
}

_AV_INLINE AV::AssetWriter* AV::AssetWriter::init(NS::URL* outputURL, AV::FileType outputFileType, NS::Error** outError)
{
	return Object::sendMessage<AV::AssetWriter*>( this, _AV_PRIVATE_SEL(initWithURL_fileType_error_), outputURL, outputFileType, outError );
}

_AV_INLINE AV::AssetWriter* AV::AssetWriter::init(UT::Type* outputContentType)
{
	return Object::sendMessage<AV::AssetWriter*>( this, _AV_PRIVATE_SEL(initWithContentType_), outputContentType );
}

_AV_INLINE BOOL AV::AssetWriter::canApplyOutputSettingsForMediaType(NS::Dictionary* outputSettings, AV::MediaType mediaType)
{
	return Object::sendMessage<BOOL>( this, _AV_PRIVATE_SEL(canApplyOutputSettings_forMediaType_), outputSettings, mediaType );
}

_AV_INLINE BOOL AV::AssetWriter::canAddInput(AV::AssetWriterInput* input)
{
	return Object::sendMessage<BOOL>( this, _AV_PRIVATE_SEL(canAddInput_), input );
}

_AV_INLINE void AV::AssetWriter::addInput(AV::AssetWriterInput* input)
{
	return Object::sendMessage<void>( this, _AV_PRIVATE_SEL(addInput_), input );
}

_AV_INLINE BOOL AV::AssetWriter::startWriting()
{
	return Object::sendMessage<BOOL>( this, _AV_PRIVATE_SEL(startWriting) );
}

_AV_INLINE void AV::AssetWriter::startSessionAtSourceTime(CMTime startTime)
{
	return Object::sendMessage<void>( this, _AV_PRIVATE_SEL(startSessionAtSourceTime_), startTime );
}

_AV_INLINE void AV::AssetWriter::endSessionAtSourceTime(CMTime endTime)
{
	return Object::sendMessage<void>( this, _AV_PRIVATE_SEL(endSessionAtSourceTime_), endTime );
}

_AV_INLINE void AV::AssetWriter::cancelWriting()
{
	return Object::sendMessage<void>( this, _AV_PRIVATE_SEL(cancelWriting) );
}

_AV_INLINE BOOL AV::AssetWriter::finishWriting()
{
	return Object::sendMessage<BOOL>( this, _AV_PRIVATE_SEL(finishWriting) );
}

// _AV_INLINE void AV::AssetWriter::finishWritingWithCompletionHandler(void (^)(void) handler)
// {
// 	return Object::sendMessage<void>( this, _AV_PRIVATE_SEL(finishWritingWithCompletionHandler_), handler );
// }

_AV_INLINE NS::URL* AV::AssetWriter::outputURL()
{
	return Object::sendMessage<NS::URL*>( this, _AV_PRIVATE_SEL(outputURL) );
}

_AV_INLINE AV::FileType AV::AssetWriter::outputFileType()
{
	return Object::sendMessage<AV::FileType>( this, _AV_PRIVATE_SEL(outputFileType) );
}

_AV_INLINE NS::Array* AV::AssetWriter::availableMediaTypes()
{
	return Object::sendMessage<NS::Array*>( this, _AV_PRIVATE_SEL(availableMediaTypes) );
}

_AV_INLINE AV::AssetWriterStatus AV::AssetWriter::status()
{
	return Object::sendMessage<AV::AssetWriterStatus>( this, _AV_PRIVATE_SEL(status) );
}

_AV_INLINE NS::Error* AV::AssetWriter::error()
{
	return Object::sendMessage<NS::Error*>( this, _AV_PRIVATE_SEL(error) );
}

_AV_INLINE NS::Array* AV::AssetWriter::metadata()
{
	return Object::sendMessage<NS::Array*>( this, _AV_PRIVATE_SEL(metadata) );
}

_AV_INLINE void AV::AssetWriter::setMetadata(NS::Array* metadata)
{
	return Object::sendMessage<void>( this, _AV_PRIVATE_SEL(setMetadata_), metadata );
}

_AV_INLINE BOOL AV::AssetWriter::shouldOptimizeForNetworkUse()
{
	return Object::sendMessage<BOOL>( this, _AV_PRIVATE_SEL(shouldOptimizeForNetworkUse) );
}

_AV_INLINE void AV::AssetWriter::setShouldOptimizeForNetworkUse(BOOL shouldOptimizeForNetworkUse)
{
	return Object::sendMessage<void>( this, _AV_PRIVATE_SEL(setShouldOptimizeForNetworkUse_), shouldOptimizeForNetworkUse );
}

_AV_INLINE NS::URL* AV::AssetWriter::directoryForTemporaryFiles()
{
	return Object::sendMessage<NS::URL*>( this, _AV_PRIVATE_SEL(directoryForTemporaryFiles) );
}

_AV_INLINE void AV::AssetWriter::setDirectoryForTemporaryFiles(NS::URL* directoryForTemporaryFiles)
{
	return Object::sendMessage<void>( this, _AV_PRIVATE_SEL(setDirectoryForTemporaryFiles_), directoryForTemporaryFiles );
}

_AV_INLINE NS::Array* AV::AssetWriter::inputs()
{
	return Object::sendMessage<NS::Array*>( this, _AV_PRIVATE_SEL(inputs) );
}

// ------------------------------------------------------------

_AV_INLINE AV::AssetWriterInputGroup* AV::AssetWriterInputGroup::init()
{
	return Object::sendMessage<AV::AssetWriterInputGroup*>( this, _AV_PRIVATE_SEL(init) );
}

_AV_INLINE AV::AssetWriterInputGroup* AV::AssetWriterInputGroup::alloc()
{
	return Object::sendMessage<AV::AssetWriterInputGroup*>( _AV_PRIVATE_CLS(AVAssetWriterInputGroup), _AV_PRIVATE_SEL(new) );
}

_AV_INLINE AV::AssetWriterInputGroup* AV::AssetWriterInputGroup::assetWriterInputGroup(NS::Array* inputs, AV::AssetWriterInput* defaultInput)
{
	return Object::sendMessage<AV::AssetWriterInputGroup*>( _AV_PRIVATE_CLS(AVAssetWriterInputGroup), _AV_PRIVATE_SEL(assetWriterInputGroupWithInputs_defaultInput_), inputs, defaultInput );
}

_AV_INLINE AV::AssetWriterInputGroup* AV::AssetWriterInputGroup::init(NS::Array* inputs, AV::AssetWriterInput* defaultInput)
{
	return Object::sendMessage<AV::AssetWriterInputGroup*>( this, _AV_PRIVATE_SEL(initWithInputs_defaultInput_), inputs, defaultInput );
}

_AV_INLINE NS::Array* AV::AssetWriterInputGroup::inputs()
{
	return Object::sendMessage<NS::Array*>( this, _AV_PRIVATE_SEL(inputs) );
}

_AV_INLINE AV::AssetWriterInput* AV::AssetWriterInputGroup::defaultInput()
{
	return Object::sendMessage<AV::AssetWriterInput*>( this, _AV_PRIVATE_SEL(defaultInput) );
}
