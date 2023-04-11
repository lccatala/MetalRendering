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
// Vision/VNTypes.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace VN
{
	using Confidence = float;
	using AspectRatio = float;
	using Degrees = float;

	_NS_ENUM (NS::UInteger, ImageCropAndScaleOption )
	{
		ImageCropAndScaleOptionCenterCrop = 0,  // scale image maintaining aspect ratio to fit on the short side and crop centered on the long side
		ImageCropAndScaleOptionScaleFit = 1,    // scale to size required by algorithm while maintaining the original aspect ratio
		ImageCropAndScaleOptionScaleFill = 2,
		ImageCropAndScaleOptionScaleFitRotate90CCW = 0x100 + ImageCropAndScaleOptionScaleFit, // scale image maintaining aspect ratio to fit on the long side but also rotate by 90 degrees counter clockwise to optimize portrait images to fit into landscape buffers for algorithms that are rotation agnostic
		ImageCropAndScaleOptionScaleFillRotate90CCW = 0x100 + ImageCropAndScaleOptionScaleFill, // scale image and rotate by 90 degrees counter clockwise to optimize portrait images to fill into landscape buffers for algorithms that are rotation agnostic
	};

	_NS_ENUM( NS::UInteger, ElementType )
	{
		ElementTypeUnknown = 0,
		ElementTypeFloat   = 1,		// IEEE 754 single-precision floating point value
		ElementTypeDouble  = 2,		// IEEE 754 double-precision floating point value
	};
} // end of namespace VN
