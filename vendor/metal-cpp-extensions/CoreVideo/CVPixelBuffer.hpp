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
// CoreVideo/CVPixelBuffer.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "CoreVideoPrivate.hpp"
#include "CVImageBuffer.hpp"
#include "CVReturn.hpp"
#include "CVBase.hpp"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace CV
{

	enum : OSType
	{
		PixelFormatType_1Monochrome    = 0x00000001, /* 1 bit indexed */
		PixelFormatType_2Indexed       = 0x00000002, /* 2 bit indexed */
		PixelFormatType_4Indexed       = 0x00000004, /* 4 bit indexed */
		PixelFormatType_8Indexed       = 0x00000008, /* 8 bit indexed */
		PixelFormatType_1IndexedGray_WhiteIsZero = 0x00000021, /* 1 bit indexed gray, white is zero */
		PixelFormatType_2IndexedGray_WhiteIsZero = 0x00000022, /* 2 bit indexed gray, white is zero */
		PixelFormatType_4IndexedGray_WhiteIsZero = 0x00000024, /* 4 bit indexed gray, white is zero */
		PixelFormatType_8IndexedGray_WhiteIsZero = 0x00000028, /* 8 bit indexed gray, white is zero */
		PixelFormatType_16BE555        = 0x00000010, /* 16 bit BE RGB 555 */
		PixelFormatType_16LE555        = 'L555',     /* 16 bit LE RGB 555 */
		PixelFormatType_16LE5551       = '5551',     /* 16 bit LE RGB 5551 */
		PixelFormatType_16BE565        = 'B565',     /* 16 bit BE RGB 565 */
		PixelFormatType_16LE565        = 'L565',     /* 16 bit LE RGB 565 */
		PixelFormatType_24RGB          = 0x00000018, /* 24 bit RGB */
		PixelFormatType_24BGR          = '24BG',     /* 24 bit BGR */
		PixelFormatType_32ARGB         = 0x00000020, /* 32 bit ARGB */
		PixelFormatType_32BGRA         = 'BGRA',     /* 32 bit BGRA */
		PixelFormatType_32ABGR         = 'ABGR',     /* 32 bit ABGR */
		PixelFormatType_32RGBA         = 'RGBA',     /* 32 bit RGBA */
		PixelFormatType_64ARGB         = 'b64a',     /* 64 bit ARGB, 16-bit big-endian samples */
		PixelFormatType_64RGBALE       = 'l64r',     /* 64 bit RGBA, 16-bit little-endian full-range (0-65535) samples */
		PixelFormatType_48RGB          = 'b48r',     /* 48 bit RGB, 16-bit big-endian samples */
		PixelFormatType_32AlphaGray    = 'b32a',     /* 32 bit AlphaGray, 16-bit big-endian samples, black is zero */
		PixelFormatType_16Gray         = 'b16g',     /* 16 bit Grayscale, 16-bit big-endian samples, black is zero */
		PixelFormatType_30RGB          = 'R10k',     /* 30 bit RGB, 10-bit big-endian samples, 2 unused padding bits (at least significant end). */
		PixelFormatType_422YpCbCr8     = '2vuy',     /* Component Y'CbCr 8-bit 4:2:2, ordered Cb Y'0 Cr Y'1 */
		PixelFormatType_4444YpCbCrA8   = 'v408',     /* Component Y'CbCrA 8-bit 4:4:4:4, ordered Cb Y' Cr A */
		PixelFormatType_4444YpCbCrA8R  = 'r408',     /* Component Y'CbCrA 8-bit 4:4:4:4, rendering format. full range alpha, zero biased YUV, ordered A Y' Cb Cr */
		PixelFormatType_4444AYpCbCr8   = 'y408',     /* Component Y'CbCrA 8-bit 4:4:4:4, ordered A Y' Cb Cr, full range alpha, video range Y'CbCr. */
		PixelFormatType_4444AYpCbCr16  = 'y416',     /* Component Y'CbCrA 16-bit 4:4:4:4, ordered A Y' Cb Cr, full range alpha, video range Y'CbCr, 16-bit little-endian samples. */
		PixelFormatType_444YpCbCr8     = 'v308',     /* Component Y'CbCr 8-bit 4:4:4, ordered Cr Y' Cb, video range Y'CbCr */
		PixelFormatType_422YpCbCr16    = 'v216',     /* Component Y'CbCr 10,12,14,16-bit 4:2:2 */
		PixelFormatType_422YpCbCr10    = 'v210',     /* Component Y'CbCr 10-bit 4:2:2 */
		PixelFormatType_444YpCbCr10    = 'v410',     /* Component Y'CbCr 10-bit 4:4:4 */
		PixelFormatType_420YpCbCr8Planar = 'y420',   /* Planar Component Y'CbCr 8-bit 4:2:0.  baseAddr points to a big-endian CVPlanarPixelBufferInfo_YCbCrPlanar struct */
		PixelFormatType_420YpCbCr8PlanarFullRange    = 'f420',   /* Planar Component Y'CbCr 8-bit 4:2:0, full range.  baseAddr points to a big-endian CVPlanarPixelBufferInfo_YCbCrPlanar struct */
		PixelFormatType_422YpCbCr_4A_8BiPlanar = 'a2vy', /* First plane: Video-range Component Y'CbCr 8-bit 4:2:2, ordered Cb Y'0 Cr Y'1; second plane: alpha 8-bit 0-255 */
		PixelFormatType_420YpCbCr8BiPlanarVideoRange = '420v', /* Bi-Planar Component Y'CbCr 8-bit 4:2:0, video-range (luma=[16,235] chroma=[16,240]).  baseAddr points to a big-endian CVPlanarPixelBufferInfo_YCbCrBiPlanar struct */
		PixelFormatType_420YpCbCr8BiPlanarFullRange  = '420f', /* Bi-Planar Component Y'CbCr 8-bit 4:2:0, full-range (luma=[0,255] chroma=[1,255]).  baseAddr points to a big-endian CVPlanarPixelBufferInfo_YCbCrBiPlanar struct */
		PixelFormatType_422YpCbCr8BiPlanarVideoRange = '422v', /* Bi-Planar Component Y'CbCr 8-bit 4:2:2, video-range (luma=[16,235] chroma=[16,240]).  baseAddr points to a big-endian CVPlanarPixelBufferInfo_YCbCrBiPlanar struct */
		PixelFormatType_422YpCbCr8BiPlanarFullRange  = '422f', /* Bi-Planar Component Y'CbCr 8-bit 4:2:2, full-range (luma=[0,255] chroma=[1,255]).  baseAddr points to a big-endian CVPlanarPixelBufferInfo_YCbCrBiPlanar struct */
		PixelFormatType_444YpCbCr8BiPlanarVideoRange = '444v', /* Bi-Planar Component Y'CbCr 8-bit 4:4:4, video-range (luma=[16,235] chroma=[16,240]).  baseAddr points to a big-endian CVPlanarPixelBufferInfo_YCbCrBiPlanar struct */
		PixelFormatType_444YpCbCr8BiPlanarFullRange  = '444f', /* Bi-Planar Component Y'CbCr 8-bit 4:4:4, full-range (luma=[0,255] chroma=[1,255]).  baseAddr points to a big-endian CVPlanarPixelBufferInfo_YCbCrBiPlanar struct */
		PixelFormatType_422YpCbCr8_yuvs = 'yuvs',     /* Component Y'CbCr 8-bit 4:2:2, ordered Y'0 Cb Y'1 Cr */
		PixelFormatType_422YpCbCr8FullRange = 'yuvf', /* Component Y'CbCr 8-bit 4:2:2, full range, ordered Y'0 Cb Y'1 Cr */
		PixelFormatType_OneComponent8  = 'L008',     /* 8 bit one component, black is zero */
		PixelFormatType_TwoComponent8  = '2C08',     /* 8 bit two component, black is zero */
		PixelFormatType_30RGBLEPackedWideGamut = 'w30r', /* little-endian RGB101010, 2 MSB are zero, wide-gamut (384-895) */
		PixelFormatType_ARGB2101010LEPacked = 'l10r',     /* little-endian ARGB2101010 full-range ARGB */
		PixelFormatType_40ARGBLEWideGamut      = 'w40a', /* little-endian ARGB10101010, each 10 bits in the MSBs of 16bits, wide-gamut (384-895, including alpha) */
		PixelFormatType_40ARGBLEWideGamutPremultiplied = 'w40m', /* little-endian ARGB10101010, each 10 bits in the MSBs of 16bits, wide-gamut (384-895, including alpha). Alpha premultiplied */
		PixelFormatType_OneComponent10      = 'L010',     /* 10 bit little-endian one component, stored as 10 MSBs of 16 bits, black is zero */
		PixelFormatType_OneComponent12      = 'L012',     /* 12 bit little-endian one component, stored as 12 MSBs of 16 bits, black is zero */
		PixelFormatType_OneComponent16      = 'L016',     /* 16 bit little-endian one component, black is zero */
		PixelFormatType_TwoComponent16      = '2C16',     /* 16 bit little-endian two component, black is zero */
		PixelFormatType_OneComponent16Half  = 'L00h',     /* 16 bit one component IEEE half-precision float, 16-bit little-endian samples */
		PixelFormatType_OneComponent32Float = 'L00f',     /* 32 bit one component IEEE float, 32-bit little-endian samples */
		PixelFormatType_TwoComponent16Half  = '2C0h',     /* 16 bit two component IEEE half-precision float, 16-bit little-endian samples */
		PixelFormatType_TwoComponent32Float = '2C0f',     /* 32 bit two component IEEE float, 32-bit little-endian samples */
		PixelFormatType_64RGBAHalf          = 'RGhA',     /* 64 bit RGBA IEEE half-precision float, 16-bit little-endian samples */
		PixelFormatType_128RGBAFloat        = 'RGfA',     /* 128 bit RGBA IEEE float, 32-bit little-endian samples */
		PixelFormatType_14Bayer_GRBG        = 'grb4',     /* Bayer 14-bit Little-Endian, packed in 16-bits, ordered G R G R... alternating with B G B G... */
		PixelFormatType_14Bayer_RGGB        = 'rgg4',     /* Bayer 14-bit Little-Endian, packed in 16-bits, ordered R G R G... alternating with G B G B... */
		PixelFormatType_14Bayer_BGGR        = 'bgg4',     /* Bayer 14-bit Little-Endian, packed in 16-bits, ordered B G B G... alternating with G R G R... */
		PixelFormatType_14Bayer_GBRG        = 'gbr4',     /* Bayer 14-bit Little-Endian, packed in 16-bits, ordered G B G B... alternating with R G R G... */
		PixelFormatType_DisparityFloat16	 = 'hdis',     /* IEEE754-2008 binary16 (half float), describing the normalized shift when comparing two images. Units are 1/meters: ( pixelShift / (pixelFocalLength * baselineInMeters) ) */
		PixelFormatType_DisparityFloat32	 = 'fdis',     /* IEEE754-2008 binary32 float, describing the normalized shift when comparing two images. Units are 1/meters: ( pixelShift / (pixelFocalLength * baselineInMeters) ) */
		PixelFormatType_DepthFloat16	     = 'hdep',     /* IEEE754-2008 binary16 (half float), describing the depth (distance to an object) in meters */
		PixelFormatType_DepthFloat32	     = 'fdep',     /* IEEE754-2008 binary32 float, describing the depth (distance to an object) in meters */
		PixelFormatType_420YpCbCr10BiPlanarVideoRange = 'x420', /* 2 plane YCbCr10 4:2:0, each 10 bits in the MSBs of 16bits, video-range (luma=[64,940] chroma=[64,960]) */
		PixelFormatType_422YpCbCr10BiPlanarVideoRange = 'x422', /* 2 plane YCbCr10 4:2:2, each 10 bits in the MSBs of 16bits, video-range (luma=[64,940] chroma=[64,960]) */
		PixelFormatType_444YpCbCr10BiPlanarVideoRange = 'x444', /* 2 plane YCbCr10 4:4:4, each 10 bits in the MSBs of 16bits, video-range (luma=[64,940] chroma=[64,960]) */
		PixelFormatType_420YpCbCr10BiPlanarFullRange  = 'xf20', /* 2 plane YCbCr10 4:2:0, each 10 bits in the MSBs of 16bits, full-range (Y range 0-1023) */
		PixelFormatType_422YpCbCr10BiPlanarFullRange  = 'xf22', /* 2 plane YCbCr10 4:2:2, each 10 bits in the MSBs of 16bits, full-range (Y range 0-1023) */
		PixelFormatType_444YpCbCr10BiPlanarFullRange  = 'xf44', /* 2 plane YCbCr10 4:4:4, each 10 bits in the MSBs of 16bits, full-range (Y range 0-1023) */
		PixelFormatType_420YpCbCr8VideoRange_8A_TriPlanar   = 'v0a8', /* first and second planes as per 420YpCbCr8BiPlanarVideoRange (420v), alpha 8 bits in third plane full-range.  No CVPlanarPixelBufferInfo struct. */
		PixelFormatType_16VersatileBayer    = 'bp16',   /* Single plane Bayer 16-bit little-endian sensor element ("sensel") samples from full-size decoding of ProRes RAW images; Bayer pattern (sensel ordering) and other raw conversion information is described via buffer attachments */
		PixelFormatType_64RGBA_DownscaledProResRAW    = 'bp64',   /* Single plane 64-bit RGBA (16-bit little-endian samples) from downscaled decoding of ProRes RAW images; components--which may not be co-sited with one another--are sensel values and require raw conversion, information for which is described via buffer attachments */
		PixelFormatType_422YpCbCr16BiPlanarVideoRange       = 'sv22', /* 2 plane YCbCr16 4:2:2, video-range (luma=[4096,60160] chroma=[4096,61440]) */
		PixelFormatType_444YpCbCr16BiPlanarVideoRange       = 'sv44', /* 2 plane YCbCr16 4:4:4, video-range (luma=[4096,60160] chroma=[4096,61440]) */
		PixelFormatType_444YpCbCr16VideoRange_16A_TriPlanar = 's4as', /* 3 plane video-range YCbCr16 4:4:4 with 16-bit full-range alpha (luma=[4096,60160] chroma=[4096,61440] alpha=[0,65535]).  No CVPlanarPixelBufferInfo struct. */
	};

	typedef CF_OPTIONS( CV::OptionFlags, PixelBufferLockFlags )
	{
		kCVPixelBufferLock_ReadOnly = 0x00000001,
	};

	_CV_CONST( CFStringRef, PixelBufferPixelFormatTypeKey );
	_CV_CONST( CFStringRef, PixelBufferMemoryAllocatorKey );
	_CV_CONST( CFStringRef, PixelBufferWidthKey );
	_CV_CONST( CFStringRef, PixelBufferHeightKey );
	_CV_CONST( CFStringRef, PixelBufferExtendedPixelsLeftKey );
	_CV_CONST( CFStringRef, PixelBufferExtendedPixelsTopKey );
	_CV_CONST( CFStringRef, PixelBufferExtendedPixelsRightKey );
	_CV_CONST( CFStringRef, PixelBufferExtendedPixelsBottomKey );
	_CV_CONST( CFStringRef, PixelBufferBytesPerRowAlignmentKey );
	_CV_CONST( CFStringRef, PixelBufferCGBitmapContextCompatibilityKey );
	_CV_CONST( CFStringRef, PixelBufferCGImageCompatibilityKey );
	_CV_CONST( CFStringRef, PixelBufferOpenGLCompatibilityKey );
	_CV_CONST( CFStringRef, PixelBufferPlaneAlignmentKey );
	_CV_CONST( CFStringRef, PixelBufferIOSurfacePropertiesKey );
	_CV_CONST( CFStringRef, PixelBufferOpenGLESCompatibilityKey );
	_CV_CONST( CFStringRef, PixelBufferMetalCompatibilityKey );
	_CV_CONST( CFStringRef, PixelBufferOpenGLTextureCacheCompatibilityKey );
	_CV_CONST( CFStringRef, PixelBufferOpenGLESTextureCacheCompatibilityKey );

	using PixelBufferRef = ImageBufferRef;

	_CV_EXPORT CV::Return pixelBufferCreate( CFAllocatorRef allocator, size_t width, size_t height, OSType pixelFormatType, CFDictionaryRef pixelBufferAttributes, CV::PixelBufferRef* pixelBufferOut ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);
	_CV_EXPORT CV::Return pixelBufferLockBaseAddress( PixelBufferRef pixelBuffer, PixelBufferLockFlags lockFlags ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);
	_CV_EXPORT CV::Return pixelBufferUnlockBaseAddress( PixelBufferRef pixelBuffer, PixelBufferLockFlags unlockFlags ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);
	_CV_EXPORT size_t pixelBufferGetWidth( PixelBufferRef pixelBuffer );
	_CV_EXPORT size_t pixelBufferGetHeight( PixelBufferRef pixelBuffer );
	_CV_EXPORT OSType pixelBufferGetPixelFormatType( PixelBufferRef pixelBuffer );
	_CV_EXPORT void* pixelBufferGetBaseAddress( PixelBufferRef pixelBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);
	_CV_EXPORT size_t pixelBufferGetBytesPerRow( PixelBufferRef pixelBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);
	_CV_EXPORT size_t pixelBufferGetDataSize( PixelBufferRef pixelBuffer ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);
	_CV_EXPORT bool pixelBufferIsPlanar( PixelBufferRef pixelBuffer );
	_CV_EXPORT size_t pixelBufferGetPlaneCount( PixelBufferRef pixelBuffer );
	_CV_EXPORT size_t pixelBufferGetWidthOfPlane( PixelBufferRef pixelBuffer, size_t planeIndex );
	_CV_EXPORT size_t pixelBufferGetHeightOfPlane( PixelBufferRef pixelBuffer, size_t planeIndex );
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

_CV_PRIVATE_DEF_CONST( CFStringRef, PixelBufferPixelFormatTypeKey );
_CV_PRIVATE_DEF_CONST( CFStringRef, PixelBufferMemoryAllocatorKey );
_CV_PRIVATE_DEF_CONST( CFStringRef, PixelBufferWidthKey );
_CV_PRIVATE_DEF_CONST( CFStringRef, PixelBufferHeightKey );
_CV_PRIVATE_DEF_CONST( CFStringRef, PixelBufferExtendedPixelsLeftKey );
_CV_PRIVATE_DEF_CONST( CFStringRef, PixelBufferExtendedPixelsTopKey );
_CV_PRIVATE_DEF_CONST( CFStringRef, PixelBufferExtendedPixelsRightKey );
_CV_PRIVATE_DEF_CONST( CFStringRef, PixelBufferExtendedPixelsBottomKey );
_CV_PRIVATE_DEF_CONST( CFStringRef, PixelBufferBytesPerRowAlignmentKey );
_CV_PRIVATE_DEF_CONST( CFStringRef, PixelBufferCGBitmapContextCompatibilityKey );
_CV_PRIVATE_DEF_CONST( CFStringRef, PixelBufferCGImageCompatibilityKey );
_CV_PRIVATE_DEF_CONST( CFStringRef, PixelBufferOpenGLCompatibilityKey );
_CV_PRIVATE_DEF_CONST( CFStringRef, PixelBufferPlaneAlignmentKey );
_CV_PRIVATE_DEF_CONST( CFStringRef, PixelBufferIOSurfacePropertiesKey );
_CV_PRIVATE_DEF_CONST( CFStringRef, PixelBufferOpenGLESCompatibilityKey );
_CV_PRIVATE_DEF_CONST( CFStringRef, PixelBufferMetalCompatibilityKey );
_CV_PRIVATE_DEF_CONST( CFStringRef, PixelBufferOpenGLTextureCacheCompatibilityKey );
_CV_PRIVATE_DEF_CONST( CFStringRef, PixelBufferOpenGLESTextureCacheCompatibilityKey );

#if defined(CV_PRIVATE_IMPLEMENTATION)

_CV_EXTERN CV::Return CVPixelBufferCreate( CFAllocatorRef allocator, size_t width, size_t height, OSType pixelFormatType, CFDictionaryRef pixelBufferAttributes, CV::PixelBufferRef* pixelBufferOut ) __OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_4_0);
_CV_EXTERN CV::Return CVPixelBufferLockBaseAddress( CV::PixelBufferRef pixelBuffer, CV::PixelBufferLockFlags lockFlags );
_CV_EXTERN CV::Return CVPixelBufferUnlockBaseAddress( CV::PixelBufferRef pixelBuffer, CV::PixelBufferLockFlags unlockFlags );
_CV_EXTERN size_t CVPixelBufferGetWidth( CV::PixelBufferRef pixelBuffer );
_CV_EXTERN size_t CVPixelBufferGetHeight( CV::PixelBufferRef pixelBuffer );
_CV_EXTERN OSType CVPixelBufferGetPixelFormatType( CV::PixelBufferRef pixelBuffer );
_CV_EXTERN void* CVPixelBufferGetBaseAddress( CV::PixelBufferRef pixelBuffer );
_CV_EXTERN size_t CVPixelBufferGetBytesPerRow( CV::PixelBufferRef pixelBuffer );
_CV_EXTERN size_t CVPixelBufferGetDataSize( CV::PixelBufferRef pixelBuffer );
_CV_EXTERN bool CVPixelBufferIsPlanar( CV::PixelBufferRef pixelBuffer );
_CV_EXTERN size_t CVPixelBufferGetPlaneCount( CV::PixelBufferRef pixelBuffer );
_CV_EXTERN size_t CVPixelBufferGetWidthOfPlane( CV::PixelBufferRef pixelBuffer, size_t planeIndex );
_CV_EXTERN size_t CVPixelBufferGetHeightOfPlane( CV::PixelBufferRef pixelBuffer, size_t planeIndex );

CV::Return CV::pixelBufferCreate( CFAllocatorRef allocator, size_t width, size_t height, OSType pixelFormatType, CFDictionaryRef pixelBufferAttributes, CV::PixelBufferRef* pixelBufferOut )
{
	return CVPixelBufferCreate( allocator, width, height, pixelFormatType, pixelBufferAttributes, pixelBufferOut );
}

CV::Return CV::pixelBufferLockBaseAddress( CV::PixelBufferRef pixelBuffer, CV::PixelBufferLockFlags lockFlags )
{
	return CVPixelBufferLockBaseAddress( pixelBuffer, lockFlags );
}

CV::Return CV::pixelBufferUnlockBaseAddress( CV::PixelBufferRef pixelBuffer, CV::PixelBufferLockFlags unlockFlags )
{
	return CVPixelBufferUnlockBaseAddress( pixelBuffer, unlockFlags );
}

size_t CV::pixelBufferGetWidth( PixelBufferRef pixelBuffer )
{
	return ::CVPixelBufferGetWidth( pixelBuffer );
}

size_t CV::pixelBufferGetHeight( PixelBufferRef pixelBuffer )
{
	return ::CVPixelBufferGetHeight( pixelBuffer );
}

OSType CV::pixelBufferGetPixelFormatType( PixelBufferRef pixelBuffer )
{
	return ::CVPixelBufferGetPixelFormatType( pixelBuffer );
}

void* CV::pixelBufferGetBaseAddress( CV::PixelBufferRef pixelBuffer )
{
	return ::CVPixelBufferGetBaseAddress( pixelBuffer );
}

size_t CV::pixelBufferGetBytesPerRow( CV::PixelBufferRef pixelBuffer )
{
	return ::CVPixelBufferGetBytesPerRow( pixelBuffer );
}

size_t CV::pixelBufferGetDataSize( CV::PixelBufferRef pixelBuffer )
{
	return ::CVPixelBufferGetDataSize( pixelBuffer );
}

bool CV::pixelBufferIsPlanar( PixelBufferRef pixelBuffer )
{
	return ::CVPixelBufferIsPlanar( pixelBuffer );
}

size_t CV::pixelBufferGetPlaneCount( PixelBufferRef pixelBuffer )
{
	return ::CVPixelBufferGetPlaneCount( pixelBuffer );
}

size_t CV::pixelBufferGetWidthOfPlane( PixelBufferRef pixelBuffer, size_t planeIndex )
{
	return ::CVPixelBufferGetWidthOfPlane( pixelBuffer, planeIndex );
}

size_t CV::pixelBufferGetHeightOfPlane( PixelBufferRef pixelBuffer, size_t planeIndex )
{
	return ::CVPixelBufferGetHeightOfPlane( pixelBuffer, planeIndex );
}

#endif // CV_PRIVATE_IMPLEMENTATION
