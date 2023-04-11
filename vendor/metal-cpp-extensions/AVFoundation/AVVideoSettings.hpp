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

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "AVFoundationPrivate.hpp"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace NS
{
	class String;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace AV
{
	_AV_CONST( NS::String*, VideoCodecKey );

	using VideoCodecType = NS::String*;
	_AV_CONST( VideoCodecType, VideoCodecTypeHEVC );
	_AV_CONST( VideoCodecType, VideoCodecTypeH264 );
	_AV_CONST( VideoCodecType, VideoCodecTypeJPEG );
	_AV_CONST( VideoCodecType, VideoCodecTypeAppleProRes4444 );
	_AV_CONST( VideoCodecType, VideoCodecTypeAppleProRes422 );
	_AV_CONST( VideoCodecType, VideoCodecTypeAppleProRes422HQ );
	_AV_CONST( VideoCodecType, VideoCodecTypeAppleProRes422LT );
	_AV_CONST( VideoCodecType, VideoCodecTypeAppleProRes422Proxy );


	_AV_CONST( NS::String*, VideoWidthKey );
	_AV_CONST( NS::String*, VideoHeightKey );
} // end of namespace AV

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

_AV_PRIVATE_DEF_CONST( NS::String*, VideoCodecKey );

_AV_PRIVATE_DEF_CONST( AV::VideoCodecType, VideoCodecTypeHEVC );
_AV_PRIVATE_DEF_CONST( AV::VideoCodecType, VideoCodecTypeH264 );
_AV_PRIVATE_DEF_CONST( AV::VideoCodecType, VideoCodecTypeJPEG );
_AV_PRIVATE_DEF_CONST( AV::VideoCodecType, VideoCodecTypeAppleProRes4444 );
_AV_PRIVATE_DEF_CONST( AV::VideoCodecType, VideoCodecTypeAppleProRes422 );
_AV_PRIVATE_DEF_CONST( AV::VideoCodecType, VideoCodecTypeAppleProRes422HQ );
_AV_PRIVATE_DEF_CONST( AV::VideoCodecType, VideoCodecTypeAppleProRes422LT );
_AV_PRIVATE_DEF_CONST( AV::VideoCodecType, VideoCodecTypeAppleProRes422Proxy );

_AV_PRIVATE_DEF_CONST( NS::String*, VideoWidthKey );
_AV_PRIVATE_DEF_CONST( NS::String*, VideoHeightKey );
