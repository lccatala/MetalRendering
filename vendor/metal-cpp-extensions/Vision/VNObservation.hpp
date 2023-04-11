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
// Vision/VNRequest.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <CoreFoundation/CoreFoundation.h>
#include <Foundation/NSTypes.hpp>
#include <CoreVideo/CVPixelBuffer.hpp>
#include <simd/simd.h>
#include "VNTypes.hpp"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace NS
{
	class UUID;
	class Array;
	class Dictionary;
	class Number;
	class String;
	class IndexPath;
} // end of namespace NS

namespace ML
{
	class FeatureValue;
} // end of namespace ML

namespace VN
{
	class Contour;
	class RecognizedPoint;
	class RecognizedPointsObservation;
} // end of namespace VN

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace VN
{
	class Observation : public NS::Copying<Observation>
	{
	public:
		NS::UUID* uuid();
		VN::Confidence confidence();
	}; // end of class Observation

	class PixelBufferObservation;

	class DetectedObjectObservation : public Observation
	{
	public:
		static VN::DetectedObjectObservation* observationWithBoundingBox(CGRect boundingBox);
		static VN::DetectedObjectObservation* observationWithRequestRevisionBoundingBox( NS::UInteger requestRevision, CGRect boundingBox );
		CGRect boundingBox();
		VN::PixelBufferObservation* globalSegmentationMask();
	}; // end of class DetectedObjectObservation

	class FaceObservation : public DetectedObjectObservation
	{
	public:
		static VN::FaceObservation* faceObservationWithRequestRevisionBoundingBoxRollYaw( NS::UInteger requestRevision, CGRect boundingBox, NS::Number* roll, NS::Number* yaw );
		static VN::FaceObservation* faceObservationWithRequestRevisionBoundingBoxRollYawPitch( NS::UInteger requestRevision, CGRect boundingBox, NS::Number* roll, NS::Number* yaw, NS::Number* pitch );
		NS::Number* faceCaptureQuality();
		NS::Number* roll();
		NS::Number* yaw();
		NS::Number* pitch();
	}; // end of class FaceObservation

	class ClassificationObservation : public Observation
	{
	public:
		NS::String* identifier();
	}; // end of class ClassificationObservation

	class RecognizedObjectObservation : public DetectedObjectObservation
	{
	public:
		NS::Array* labels();
	}; // end of class RecognizedObjectObservation

	class CoreMLFeatureValueObservation : public Observation
	{
	public:
		ML::FeatureValue* featureValue();
		NS::String* featureName();
	}; // end of class CoreMLFeatureValueObservation

	class PixelBufferObservation : public Observation
	{
	public:
		CV::PixelBufferRef pixelBuffer();
		NS::String* featureName();
	}; // end of class PixelBufferObservation

	class RectangleObservation : public DetectedObjectObservation
	{
	public:
		static VN::RectangleObservation* rectangleObservationWithRequestRevisionTopLeftBottomLeftBottomRightTopRight( NS::UInteger requestRevision, CGPoint topLeft, CGPoint bottomLeft, CGPoint bottomRight, CGPoint topRight );
		CGPoint topLeft();
		CGPoint topRight();
		CGPoint bottomLeft();
		CGPoint bottomRight();
	}; // end of class RectangleObservation

	class TrajectoryObservation : public Observation
	{
	public:
		NS::Array* detectedPoints();
		NS::Array* projectedPoints();
		simd_float3 equationCoefficients();
		CGFloat movingAverageRadius();
	}; // end of class TrajectoryObservation

	class TextObservation : public RectangleObservation
	{
	public:
		NS::Array* characterBoxes();
	}; // end of class TextObservation

	class RecognizedText : public NS::Copying<Observation>
	{
	public:
		VN::RectangleObservation* boundingBoxForRangeError(NS::Range range, NS::Error** error);
		NS::String* string();
		VN::Confidence confidence();
	}; // end of class RecognizedText

	class RecognizedTextObservation : public RectangleObservation
	{
	public:
		NS::Array* topCandidates(NS::UInteger maxCandidateCount);
	}; // end of class RecognizedTextObservation

	class BarcodeObservation : public RectangleObservation
	{
	public:
		NS::String* payloadStringValue();
	}; // end of class BarcodeObservation

	class HorizonObservation : public Observation
	{
	public:
		CGAffineTransform transformForImageWidthHeight(size_t width, size_t height);
		CGAffineTransform transform();
		CGFloat angle();
	}; // end of class HorizonObservation

	class ImageAlignmentObservation : public Observation
	{
	public:
	}; // end of class ImageAlignmentObservation

	class ImageTranslationAlignmentObservation : public ImageAlignmentObservation
	{
	public:
		CGAffineTransform alignmentTransform();
	}; // end of class ImageTranslationAlignmentObservation

	class ImageHomographicAlignmentObservation : public ImageAlignmentObservation
	{
	public:
		matrix_float3x3 warpTransform();
	}; // end of class ImageHomographicAlignmentObservation

	class SaliencyImageObservation : public PixelBufferObservation
	{
	public:
		NS::Array* salientObjects();
	}; // end of class SaliencyImageObservation

	class FeaturePrintObservation : public Observation
	{
	public:
		BOOL computeDistanceToFeaturePrintObservationError(float * outDistance, VN::FeaturePrintObservation* featurePrint, NS::Error** error);
		VN::ElementType elementType();
		NS::UInteger elementCount();
		NS::Data* data();
	}; // end of class FeaturePrintObservation

	class ContoursObservation : public Observation
	{
	public:
		VN::Contour* contourAtIndexError(NS::Integer contourIndex, NS::Error** error);
		VN::Contour* contourAtIndexPathError(NS::IndexPath* indexPath, NS::Error** error);
		NS::Integer contourCount();
		NS::Integer topLevelContourCount();
		NS::Array* topLevelContours();
	}; // end of class ContoursObservation

	class RecognizedPointsObservation : public Observation
	{
	public:
		VN::RecognizedPointsObservation* init();
		NS::Array* availableKeys();
		NS::Array* availableGroupKeys();
	}; // end of class RecognizedPointsObservation

	class HumanObservation : public DetectedObjectObservation
	{
	public:
		BOOL upperBodyOnly();
	}; // end of class HumanObservation

} // end of namespace VN


// ------------------------------------------------------------

_VN_INLINE NS::UUID* VN::Observation::uuid()
{
	return Object::sendMessage<NS::UUID*>( this, _VN_PRIVATE_SEL(uuid) );
}

_VN_INLINE VN::Confidence VN::Observation::confidence()
{
	return Object::sendMessage<VN::Confidence>( this, _VN_PRIVATE_SEL(confidence) );
}

// ------------------------------------------------------------

_VN_INLINE VN::DetectedObjectObservation* VN::DetectedObjectObservation::observationWithBoundingBox(CGRect boundingBox)
{
	return Object::sendMessage<VN::DetectedObjectObservation*>( _VN_PRIVATE_CLS(VNDetectedObjectObservation), _VN_PRIVATE_SEL(observationWithBoundingBox_), boundingBox );
}

_VN_INLINE VN::DetectedObjectObservation* VN::DetectedObjectObservation::observationWithRequestRevisionBoundingBox(NS::UInteger requestRevision, CGRect boundingBox)
{
	return Object::sendMessage<VN::DetectedObjectObservation*>( _VN_PRIVATE_CLS(VNDetectedObjectObservation), _VN_PRIVATE_SEL(observationWithRequestRevision_boundingBox_), requestRevision, boundingBox );
}

_VN_INLINE CGRect VN::DetectedObjectObservation::boundingBox()
{
	return Object::sendMessage<CGRect>( this, _VN_PRIVATE_SEL(boundingBox) );
}

_VN_INLINE VN::PixelBufferObservation* VN::DetectedObjectObservation::globalSegmentationMask()
{
	return Object::sendMessage<VN::PixelBufferObservation*>( this, _VN_PRIVATE_SEL(globalSegmentationMask) );
}

// ------------------------------------------------------------

_VN_INLINE VN::FaceObservation* VN::FaceObservation::faceObservationWithRequestRevisionBoundingBoxRollYaw(NS::UInteger requestRevision, CGRect boundingBox, NS::Number* roll, NS::Number* yaw)
{
	return Object::sendMessage<VN::FaceObservation*>( _VN_PRIVATE_CLS(VNFaceObservation), _VN_PRIVATE_SEL(faceObservationWithRequestRevision_boundingBox_roll_yaw_), requestRevision, boundingBox, roll, yaw );
}

_VN_INLINE VN::FaceObservation* VN::FaceObservation::faceObservationWithRequestRevisionBoundingBoxRollYawPitch(NS::UInteger requestRevision, CGRect boundingBox, NS::Number* roll, NS::Number* yaw, NS::Number* pitch)
{
	return Object::sendMessage<VN::FaceObservation*>( _VN_PRIVATE_CLS(VNFaceObservation), _VN_PRIVATE_SEL(faceObservationWithRequestRevision_boundingBox_roll_yaw_pitch_), requestRevision, boundingBox, roll, yaw, pitch );
}

_VN_INLINE NS::Number* VN::FaceObservation::faceCaptureQuality()
{
	return Object::sendMessage<NS::Number*>( this, _VN_PRIVATE_SEL(faceCaptureQuality) );
}

_VN_INLINE NS::Number* VN::FaceObservation::roll()
{
	return Object::sendMessage<NS::Number*>( this, _VN_PRIVATE_SEL(roll) );
}

_VN_INLINE NS::Number* VN::FaceObservation::yaw()
{
	return Object::sendMessage<NS::Number*>( this, _VN_PRIVATE_SEL(yaw) );
}

_VN_INLINE NS::Number* VN::FaceObservation::pitch()
{
	return Object::sendMessage<NS::Number*>( this, _VN_PRIVATE_SEL(pitch) );
}

// ------------------------------------------------------------

_VN_INLINE NS::String* VN::ClassificationObservation::identifier()
{
	return Object::sendMessage<NS::String*>( this, _VN_PRIVATE_SEL(identifier) );
}

// ------------------------------------------------------------

_VN_INLINE NS::Array* VN::RecognizedObjectObservation::labels()
{
	return Object::sendMessage<NS::Array*>( this, _VN_PRIVATE_SEL(labels) );
}

// ------------------------------------------------------------

_VN_INLINE ML::FeatureValue* VN::CoreMLFeatureValueObservation::featureValue()
{
	return Object::sendMessage<ML::FeatureValue*>( this, _VN_PRIVATE_SEL(featureValue) );
}

_VN_INLINE NS::String* VN::CoreMLFeatureValueObservation::featureName()
{
	return Object::sendMessage<NS::String*>( this, _VN_PRIVATE_SEL(featureName) );
}

// ------------------------------------------------------------

_VN_INLINE CV::PixelBufferRef VN::PixelBufferObservation::pixelBuffer()
{
	return Object::sendMessage<CV::PixelBufferRef>( this, _VN_PRIVATE_SEL(pixelBuffer) );
}

_VN_INLINE NS::String* VN::PixelBufferObservation::featureName()
{
	return Object::sendMessage<NS::String*>( this, _VN_PRIVATE_SEL(featureName) );
}

// ------------------------------------------------------------

_VN_INLINE VN::RectangleObservation* VN::RectangleObservation::rectangleObservationWithRequestRevisionTopLeftBottomLeftBottomRightTopRight(NS::UInteger requestRevision, CGPoint topLeft, CGPoint bottomLeft, CGPoint bottomRight, CGPoint topRight)
{
	return Object::sendMessage<VN::RectangleObservation*>( _VN_PRIVATE_CLS(VNRectangleObservation), _VN_PRIVATE_SEL(rectangleObservationWithRequestRevision_topLeft_bottomLeft_bottomRight_topRight_), requestRevision, topLeft, bottomLeft, bottomRight, topRight );
}

_VN_INLINE CGPoint VN::RectangleObservation::topLeft()
{
	return Object::sendMessage<CGPoint>( this, _VN_PRIVATE_SEL(topLeft) );
}

_VN_INLINE CGPoint VN::RectangleObservation::topRight()
{
	return Object::sendMessage<CGPoint>( this, _VN_PRIVATE_SEL(topRight) );
}

_VN_INLINE CGPoint VN::RectangleObservation::bottomLeft()
{
	return Object::sendMessage<CGPoint>( this, _VN_PRIVATE_SEL(bottomLeft) );
}

_VN_INLINE CGPoint VN::RectangleObservation::bottomRight()
{
	return Object::sendMessage<CGPoint>( this, _VN_PRIVATE_SEL(bottomRight) );
}

// ------------------------------------------------------------

_VN_INLINE NS::Array* VN::TrajectoryObservation::detectedPoints()
{
	return Object::sendMessage<NS::Array*>( this, _VN_PRIVATE_SEL(detectedPoints) );
}

_VN_INLINE NS::Array* VN::TrajectoryObservation::projectedPoints()
{
	return Object::sendMessage<NS::Array*>( this, _VN_PRIVATE_SEL(projectedPoints) );
}

_VN_INLINE simd_float3 VN::TrajectoryObservation::equationCoefficients()
{
	return Object::sendMessage<simd_float3>( this, _VN_PRIVATE_SEL(equationCoefficients) );
}

_VN_INLINE CGFloat VN::TrajectoryObservation::movingAverageRadius()
{
	return Object::sendMessage<CGFloat>( this, _VN_PRIVATE_SEL(movingAverageRadius) );
}

// ------------------------------------------------------------

_VN_INLINE NS::Array* VN::TextObservation::characterBoxes()
{
	return Object::sendMessage<NS::Array*>( this, _VN_PRIVATE_SEL(characterBoxes) );
}

// ------------------------------------------------------------

_VN_INLINE VN::RectangleObservation* VN::RecognizedText::boundingBoxForRangeError(NS::Range range, NS::Error** error)
{
	return Object::sendMessage<VN::RectangleObservation*>( this, _VN_PRIVATE_SEL(boundingBoxForRange_error_), range, error );
}

_VN_INLINE NS::String* VN::RecognizedText::string()
{
	return Object::sendMessage<NS::String*>( this, _VN_PRIVATE_SEL(string) );
}

_VN_INLINE VN::Confidence VN::RecognizedText::confidence()
{
	return Object::sendMessage<VN::Confidence>( this, _VN_PRIVATE_SEL(confidence) );
}

// ------------------------------------------------------------

_VN_INLINE NS::Array* VN::RecognizedTextObservation::topCandidates(NS::UInteger maxCandidateCount)
{
	return Object::sendMessage<NS::Array*>( this, _VN_PRIVATE_SEL(topCandidates_), maxCandidateCount );
}

// ------------------------------------------------------------

_VN_INLINE NS::String* VN::BarcodeObservation::payloadStringValue()
{
	return Object::sendMessage<NS::String*>( this, _VN_PRIVATE_SEL(payloadStringValue) );
}

// ------------------------------------------------------------

_VN_INLINE CGAffineTransform VN::HorizonObservation::transformForImageWidthHeight(size_t width, size_t height)
{
	return Object::sendMessage<CGAffineTransform>( this, _VN_PRIVATE_SEL(transformForImageWidth_height_), width, height );
}

_VN_INLINE CGAffineTransform VN::HorizonObservation::transform()
{
	return Object::sendMessage<CGAffineTransform>( this, _VN_PRIVATE_SEL(transform) );
}

_VN_INLINE CGFloat VN::HorizonObservation::angle()
{
	return Object::sendMessage<CGFloat>( this, _VN_PRIVATE_SEL(angle) );
}

// ------------------------------------------------------------

_VN_INLINE CGAffineTransform VN::ImageTranslationAlignmentObservation::alignmentTransform()
{
	return Object::sendMessage<CGAffineTransform>( this, _VN_PRIVATE_SEL(alignmentTransform) );
}

// ------------------------------------------------------------

_VN_INLINE matrix_float3x3 VN::ImageHomographicAlignmentObservation::warpTransform()
{
	return Object::sendMessage<matrix_float3x3>( this, _VN_PRIVATE_SEL(warpTransform) );
}

// ------------------------------------------------------------

_VN_INLINE NS::Array* VN::SaliencyImageObservation::salientObjects()
{
	return Object::sendMessage<NS::Array*>( this, _VN_PRIVATE_SEL(salientObjects) );
}

// ------------------------------------------------------------

_VN_INLINE BOOL VN::FeaturePrintObservation::computeDistanceToFeaturePrintObservationError(float * outDistance, VN::FeaturePrintObservation* featurePrint, NS::Error** error)
{
	return Object::sendMessage<BOOL>( this, _VN_PRIVATE_SEL(computeDistance_toFeaturePrintObservation_error_), outDistance, featurePrint, error );
}

_VN_INLINE VN::ElementType VN::FeaturePrintObservation::elementType()
{
	return Object::sendMessage<VN::ElementType>( this, _VN_PRIVATE_SEL(elementType) );
}

_VN_INLINE NS::UInteger VN::FeaturePrintObservation::elementCount()
{
	return Object::sendMessage<NS::UInteger>( this, _VN_PRIVATE_SEL(elementCount) );
}

_VN_INLINE NS::Data* VN::FeaturePrintObservation::data()
{
	return Object::sendMessage<NS::Data*>( this, _VN_PRIVATE_SEL(data) );
}

// ------------------------------------------------------------

_VN_INLINE VN::Contour* VN::ContoursObservation::contourAtIndexError(NS::Integer contourIndex, NS::Error** error)
{
	return Object::sendMessage<VN::Contour*>( this, _VN_PRIVATE_SEL(contourAtIndex_error_), contourIndex, error );
}

_VN_INLINE VN::Contour* VN::ContoursObservation::contourAtIndexPathError(NS::IndexPath* indexPath, NS::Error** error)
{
	return Object::sendMessage<VN::Contour*>( this, _VN_PRIVATE_SEL(contourAtIndexPath_error_), indexPath, error );
}

_VN_INLINE NS::Integer VN::ContoursObservation::contourCount()
{
	return Object::sendMessage<NS::Integer>( this, _VN_PRIVATE_SEL(contourCount) );
}

_VN_INLINE NS::Integer VN::ContoursObservation::topLevelContourCount()
{
	return Object::sendMessage<NS::Integer>( this, _VN_PRIVATE_SEL(topLevelContourCount) );
}

_VN_INLINE NS::Array* VN::ContoursObservation::topLevelContours()
{
	return Object::sendMessage<NS::Array*>( this, _VN_PRIVATE_SEL(topLevelContours) );
}

// ------------------------------------------------------------

_VN_INLINE VN::RecognizedPointsObservation* VN::RecognizedPointsObservation::init()
{
	return Object::sendMessage<VN::RecognizedPointsObservation*>( this, _VN_PRIVATE_SEL(init) );
}

_VN_INLINE NS::Array* VN::RecognizedPointsObservation::availableKeys()
{
	return Object::sendMessage<NS::Array*>( this, _VN_PRIVATE_SEL(availableKeys) );
}

_VN_INLINE NS::Array* VN::RecognizedPointsObservation::availableGroupKeys()
{
	return Object::sendMessage<NS::Array*>( this, _VN_PRIVATE_SEL(availableGroupKeys) );
}

// ------------------------------------------------------------

_VN_INLINE BOOL VN::HumanObservation::upperBodyOnly()
{
	return Object::sendMessage<BOOL>( this, _VN_PRIVATE_SEL(upperBodyOnly) );
}
