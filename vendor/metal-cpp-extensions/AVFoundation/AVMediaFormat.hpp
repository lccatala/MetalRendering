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
// AVFoundation/AVMediaFormat.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

#include "AVDefines.hpp"

namespace NS
{
	class String;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace AV
{
	using MediaType = NS::String*;
	_AV_CONST( MediaType, MediaTypeVideo );
	_AV_CONST( MediaType, MediaTypeAudio );
	_AV_CONST( MediaType, MediaTypeText );
	_AV_CONST( MediaType, MediaTypeClosedCaption );
	_AV_CONST( MediaType, MediaTypeSubtitle );
	_AV_CONST( MediaType, MediaTypeTimecode );
	_AV_CONST( MediaType, MediaTypeMetadata );
	_AV_CONST( MediaType, MediaTypeMuxed );

	using FileType = NS::String*;
	_AV_CONST( FileType, FileTypeQuickTimeMovie ) API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
	_AV_CONST( FileType, FileTypeMPEG4 ) API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
	_AV_CONST( FileType, FileTypeAppleM4V ) API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
	_AV_CONST( FileType, FileTypeAppleM4A ) API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
	_AV_CONST( FileType, FileType3GPP ) API_AVAILABLE(macos(10.11), ios(4.0), tvos(9.0), watchos(1.0));
	_AV_CONST( FileType, FileType3GPP2 ) API_AVAILABLE(macos(10.11), ios(4.0), tvos(9.0), watchos(1.0));
	_AV_CONST( FileType, FileTypeCoreAudioFormat ) API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
	_AV_CONST( FileType, FileTypeWAVE ) API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
	_AV_CONST( FileType, FileTypeAIFF ) API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
	_AV_CONST( FileType, FileTypeAIFC ) API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
	_AV_CONST( FileType, FileTypeAMR ) API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
	_AV_CONST( FileType, FileTypeMPEGLayer3 ) API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));
	_AV_CONST( FileType, FileTypeSunAU ) API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));
	_AV_CONST( FileType, FileTypeAC3 ) API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));
	_AV_CONST( FileType, FileTypeEnhancedAC3 ) API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0));
	_AV_CONST( FileType, FileTypeJPEG ) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
	_AV_CONST( FileType, FileTypeDNG ) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
	_AV_CONST( FileType, FileTypeHEIC ) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
	_AV_CONST( FileType, FileTypeAVCI ) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
	_AV_CONST( FileType, FileTypeHEIF ) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
	_AV_CONST( FileType, FileTypeTIFF ) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
	_AV_CONST( FileType, FileTypeAppleiTT ) API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, tvos, watchos);
	_AV_CONST( FileType, FileTypeSCC ) API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, tvos, watchos);
} // end of namespace AV

_AV_PRIVATE_DEF_CONST( AV::MediaType, MediaTypeVideo );
_AV_PRIVATE_DEF_CONST( AV::MediaType, MediaTypeAudio );
_AV_PRIVATE_DEF_CONST( AV::MediaType, MediaTypeText );
_AV_PRIVATE_DEF_CONST( AV::MediaType, MediaTypeClosedCaption );
_AV_PRIVATE_DEF_CONST( AV::MediaType, MediaTypeSubtitle );
_AV_PRIVATE_DEF_CONST( AV::MediaType, MediaTypeTimecode );
_AV_PRIVATE_DEF_CONST( AV::MediaType, MediaTypeMetadata );
_AV_PRIVATE_DEF_CONST( AV::MediaType, MediaTypeMuxed );


_AV_PRIVATE_DEF_CONST( AV::FileType, FileTypeQuickTimeMovie );
_AV_PRIVATE_DEF_CONST( AV::FileType, FileTypeMPEG4 );
_AV_PRIVATE_DEF_CONST( AV::FileType, FileTypeAppleM4V );
_AV_PRIVATE_DEF_CONST( AV::FileType, FileTypeAppleM4A );
_AV_PRIVATE_DEF_CONST( AV::FileType, FileType3GPP );
_AV_PRIVATE_DEF_CONST( AV::FileType, FileType3GPP2 );
_AV_PRIVATE_DEF_CONST( AV::FileType, FileTypeCoreAudioFormat );
_AV_PRIVATE_DEF_CONST( AV::FileType, FileTypeWAVE );
_AV_PRIVATE_DEF_CONST( AV::FileType, FileTypeAIFF );
_AV_PRIVATE_DEF_CONST( AV::FileType, FileTypeAIFC );
_AV_PRIVATE_DEF_CONST( AV::FileType, FileTypeAMR );
_AV_PRIVATE_DEF_CONST( AV::FileType, FileTypeMPEGLayer3 );
_AV_PRIVATE_DEF_CONST( AV::FileType, FileTypeSunAU );
_AV_PRIVATE_DEF_CONST( AV::FileType, FileTypeAC3 );
_AV_PRIVATE_DEF_CONST( AV::FileType, FileTypeEnhancedAC3 );
_AV_PRIVATE_DEF_CONST( AV::FileType, FileTypeJPEG );
_AV_PRIVATE_DEF_CONST( AV::FileType, FileTypeDNG );
_AV_PRIVATE_DEF_CONST( AV::FileType, FileTypeHEIC );
_AV_PRIVATE_DEF_CONST( AV::FileType, FileTypeAVCI );
_AV_PRIVATE_DEF_CONST( AV::FileType, FileTypeHEIF );
_AV_PRIVATE_DEF_CONST( AV::FileType, FileTypeTIFF );
_AV_PRIVATE_DEF_CONST( AV::FileType, FileTypeAppleiTT );
_AV_PRIVATE_DEF_CONST( AV::FileType, FileTypeSCC );
