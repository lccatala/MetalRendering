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
// Vision/VisionPrivate.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <objc/runtime.h>
#include "VisionDefines.hpp"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#define _VN_PRIVATE_CLS( symbol )    ( Private::Class::s_k ## symbol )
#define _VN_PRIVATE_SEL( accessor )  ( Private::Selector::s_k ## accessor )

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#if defined( VN_PRIVATE_IMPLEMENTATION )

#define _VN_PRIVATE_VISIBILITY       __attribute__( ( visibility( "default" ) ) )
#define _VN_PRIVATE_IMPORT           __attribute__( ( weak_import ) )

#if __OBJC__
#define  _VN_PRIVATE_OBJC_LOOKUP_CLASS( symbol  )   ( ( __bridge void* ) objc_lookUpClass( # symbol ) )
#else
#define  _VN_PRIVATE_OBJC_LOOKUP_CLASS( symbol  )   objc_lookUpClass( # symbol )
#endif // __OBJC__

#define _VN_PRIVATE_DEF_CLS( symbol )            void*           s_k ## symbol     _VN_PRIVATE_VISIBILITY = _VN_PRIVATE_OBJC_LOOKUP_CLASS( symbol );
#define _VN_PRIVATE_DEF_SEL( accessor, symbol )  SEL             s_k ## accessor   _VN_PRIVATE_VISIBILITY = sel_registerName( symbol );
#define _VN_PRIVATE_DEF_CONST( type, symbol )    _VN_EXTERN type const    kVN ## symbol   _VN_PRIVATE_IMPORT; \
                                                            type const    VN::symbol = ( nullptr != &kVN ## symbol ) ? kVN ## symbol : nullptr;

#else

#define _VN_PRIVATE_DEF_CLS( symbol )            extern void*     s_k ## symbol;
#define _VN_PRIVATE_DEF_SEL( accessor, symbol )  extern SEL       s_k ## accessor;
#define _VN_PRIVATE_DEF_CONST( type, symbol )


#endif // VN_PRIVATE_IMPLEMENTATION

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace VN::Private::Class
{
	_VN_PRIVATE_DEF_CLS(VNBarcodeObservation);
	_VN_PRIVATE_DEF_CLS(VNClassificationObservation);
	_VN_PRIVATE_DEF_CLS(VNContoursObservation);
	_VN_PRIVATE_DEF_CLS(VNCoreMLFeatureValueObservation);
	_VN_PRIVATE_DEF_CLS(VNCoreMLModel);
	_VN_PRIVATE_DEF_CLS(VNCoreMLRequest);
	_VN_PRIVATE_DEF_CLS(VNDetectedObjectObservation);
	_VN_PRIVATE_DEF_CLS(VNFaceObservation);
	_VN_PRIVATE_DEF_CLS(VNFeaturePrintObservation);
	_VN_PRIVATE_DEF_CLS(VNHorizonObservation);
	_VN_PRIVATE_DEF_CLS(VNHumanObservation);
	_VN_PRIVATE_DEF_CLS(VNImageAlignmentObservation);
	_VN_PRIVATE_DEF_CLS(VNImageBasedRequest);
	_VN_PRIVATE_DEF_CLS(VNImageHomographicAlignmentObservation);
	_VN_PRIVATE_DEF_CLS(VNImageRequestHandler);
	_VN_PRIVATE_DEF_CLS(VNImageTranslationAlignmentObservation);
	_VN_PRIVATE_DEF_CLS(VNObservation);
	_VN_PRIVATE_DEF_CLS(VNPixelBufferObservation);
	_VN_PRIVATE_DEF_CLS(VNRecognizedObjectObservation);
	_VN_PRIVATE_DEF_CLS(VNRecognizedPointsObservation);
	_VN_PRIVATE_DEF_CLS(VNRecognizedText);
	_VN_PRIVATE_DEF_CLS(VNRecognizedTextObservation);
	_VN_PRIVATE_DEF_CLS(VNRectangleObservation);
	_VN_PRIVATE_DEF_CLS(VNRequest);
	_VN_PRIVATE_DEF_CLS(VNSaliencyImageObservation);
	_VN_PRIVATE_DEF_CLS(VNSequenceRequestHandler);
	_VN_PRIVATE_DEF_CLS(VNTextObservation);
	_VN_PRIVATE_DEF_CLS(VNTrajectoryObservation);
} // Class

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace VN::Private::Selector
{
	_VN_PRIVATE_DEF_SEL( alignmentTransform, "alignmentTransform" );
	_VN_PRIVATE_DEF_SEL( angle, "angle" );
	_VN_PRIVATE_DEF_SEL( availableGroupKeys, "availableGroupKeys" );
	_VN_PRIVATE_DEF_SEL( availableKeys, "availableKeys" );
	_VN_PRIVATE_DEF_SEL( bottomLeft, "bottomLeft" );
	_VN_PRIVATE_DEF_SEL( bottomRight, "bottomRight" );
	_VN_PRIVATE_DEF_SEL( boundingBox, "boundingBox" );
	_VN_PRIVATE_DEF_SEL( boundingBoxForRange_error_, "boundingBoxForRange:error:" );
	_VN_PRIVATE_DEF_SEL( cancel, "cancel" );
	_VN_PRIVATE_DEF_SEL( characterBoxes, "characterBoxes" );
	_VN_PRIVATE_DEF_SEL( computeDistance_toFeaturePrintObservation_error_, "computeDistance:toFeaturePrintObservation:error:" );
	_VN_PRIVATE_DEF_SEL( confidence, "confidence" );
	_VN_PRIVATE_DEF_SEL( contourAtIndex_error_, "contourAtIndex:error:" );
	_VN_PRIVATE_DEF_SEL( contourAtIndexPath_error_, "contourAtIndexPath:error:" );
	_VN_PRIVATE_DEF_SEL( contourCount, "contourCount" );
	_VN_PRIVATE_DEF_SEL( currentRevision, "currentRevision" );
	_VN_PRIVATE_DEF_SEL( data, "data" );
	_VN_PRIVATE_DEF_SEL( defaultRevision, "defaultRevision" );
	_VN_PRIVATE_DEF_SEL( detectedPoints, "detectedPoints" );
	_VN_PRIVATE_DEF_SEL( elementCount, "elementCount" );
	_VN_PRIVATE_DEF_SEL( elementType, "elementType" );
	_VN_PRIVATE_DEF_SEL( equationCoefficients, "equationCoefficients" );
	_VN_PRIVATE_DEF_SEL( faceCaptureQuality, "faceCaptureQuality" );
	_VN_PRIVATE_DEF_SEL( faceObservationWithRequestRevision_boundingBox_roll_yaw_, "faceObservationWithRequestRevision:boundingBox:roll:yaw:" );
	_VN_PRIVATE_DEF_SEL( faceObservationWithRequestRevision_boundingBox_roll_yaw_pitch_, "faceObservationWithRequestRevision:boundingBox:roll:yaw:pitch:" );
	_VN_PRIVATE_DEF_SEL( featureName, "featureName" );
	_VN_PRIVATE_DEF_SEL( featureValue, "featureValue" );
	_VN_PRIVATE_DEF_SEL( globalSegmentationMask, "globalSegmentationMask" );
	_VN_PRIVATE_DEF_SEL( identifier, "identifier" );
	_VN_PRIVATE_DEF_SEL( imageCropAndScaleOption, "imageCropAndScaleOption" );
	_VN_PRIVATE_DEF_SEL( init, "init" );
	_VN_PRIVATE_DEF_SEL( initWithCMSampleBuffer_options_, "initWithCMSampleBuffer:options:" );
	_VN_PRIVATE_DEF_SEL( initWithCVPixelBuffer_options_, "initWithCVPixelBuffer:options:" );
	_VN_PRIVATE_DEF_SEL( initWithData_options_, "initWithData:options:" );
	_VN_PRIVATE_DEF_SEL( initWithModel_, "initWithModel:" );
	_VN_PRIVATE_DEF_SEL( initWithURL_options_, "initWithURL:options:" );
	_VN_PRIVATE_DEF_SEL( labels, "labels" );
	_VN_PRIVATE_DEF_SEL( landmarks, "landmarks" );
	_VN_PRIVATE_DEF_SEL( modelForMLModel_error_, "modelForMLModel:error:" );
	_VN_PRIVATE_DEF_SEL( movingAverageRadius, "movingAverageRadius" );
	_VN_PRIVATE_DEF_SEL( normalizedPath, "normalizedPath" );
	_VN_PRIVATE_DEF_SEL( observationWithBoundingBox_, "observationWithBoundingBox:" );
	_VN_PRIVATE_DEF_SEL( observationWithRequestRevision_boundingBox_, "observationWithRequestRevision:boundingBox:" );
	_VN_PRIVATE_DEF_SEL( payloadStringValue, "payloadStringValue" );
	_VN_PRIVATE_DEF_SEL( performRequests_error_, "performRequests:error:" );
	_VN_PRIVATE_DEF_SEL( performRequests_onCMSampleBuffer_error_, "performRequests:onCMSampleBuffer:error:" );
	_VN_PRIVATE_DEF_SEL( performRequests_onCVPixelBuffer_error_, "performRequests:onCVPixelBuffer:error:" );
	_VN_PRIVATE_DEF_SEL( performRequests_onImageData_error_, "performRequests:onImageData:error:" );
	_VN_PRIVATE_DEF_SEL( performRequests_onImageURL_error_, "performRequests:onImageURL:error:" );
	_VN_PRIVATE_DEF_SEL( pitch, "pitch" );
	_VN_PRIVATE_DEF_SEL( pixelBuffer, "pixelBuffer" );
	_VN_PRIVATE_DEF_SEL( preferBackgroundProcessing, "preferBackgroundProcessing" );
	_VN_PRIVATE_DEF_SEL( projectedPoints, "projectedPoints" );
	_VN_PRIVATE_DEF_SEL( rectangleObservationWithRequestRevision_topLeft_bottomLeft_bottomRight_topRight_, "rectangleObservationWithRequestRevision:topLeft:bottomLeft:bottomRight:topRight:" );
	_VN_PRIVATE_DEF_SEL( regionOfInterest, "regionOfInterest" );
	_VN_PRIVATE_DEF_SEL( results, "results" );
	_VN_PRIVATE_DEF_SEL( revision, "revision" );
	_VN_PRIVATE_DEF_SEL( roll, "roll" );
	_VN_PRIVATE_DEF_SEL( salientObjects, "salientObjects" );
	_VN_PRIVATE_DEF_SEL( setImageCropAndScaleOption_, "setImageCropAndScaleOption:" );
	_VN_PRIVATE_DEF_SEL( setPreferBackgroundProcessing_, "setPreferBackgroundProcessing:" );
	_VN_PRIVATE_DEF_SEL( setRegionOfInterest_, "setRegionOfInterest:" );
	_VN_PRIVATE_DEF_SEL( setRevision_, "setRevision:" );
	_VN_PRIVATE_DEF_SEL( setUsesCPUOnly_, "setUsesCPUOnly:" );
	_VN_PRIVATE_DEF_SEL( string, "string" );
	_VN_PRIVATE_DEF_SEL( supportedRevisions, "supportedRevisions" );
	_VN_PRIVATE_DEF_SEL( symbology, "symbology" );
	_VN_PRIVATE_DEF_SEL( topCandidates_, "topCandidates:" );
	_VN_PRIVATE_DEF_SEL( topLeft, "topLeft" );
	_VN_PRIVATE_DEF_SEL( topLevelContourCount, "topLevelContourCount" );
	_VN_PRIVATE_DEF_SEL( topLevelContours, "topLevelContours" );
	_VN_PRIVATE_DEF_SEL( topRight, "topRight" );
	_VN_PRIVATE_DEF_SEL( transform, "transform" );
	_VN_PRIVATE_DEF_SEL( transformForImageWidth_height_, "transformForImageWidth:height:" );
	_VN_PRIVATE_DEF_SEL( upperBodyOnly, "upperBodyOnly" );
	_VN_PRIVATE_DEF_SEL( usesCPUOnly, "usesCPUOnly" );
	_VN_PRIVATE_DEF_SEL( uuid, "uuid" );
	_VN_PRIVATE_DEF_SEL( warpTransform, "warpTransform" );
	_VN_PRIVATE_DEF_SEL( yaw, "yaw" );
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
