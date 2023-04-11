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
// Vision/VNCoreMLRequest.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "VisionPrivate.hpp"
#include <Foundation/NSObject.hpp>
#include "VNRequest.hpp"
#include "VNTypes.hpp"


//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace NS
{
	class URL;
	class Error;
} // end of namespace NS

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace VN
{
	class CoreMLModel : public NS::Referencing<CoreMLModel>
	{
	public:
		static CoreMLModel* model( ML::Model* model, NS::Error** error );
	}; // end of class CoreMLModel

	class CoreMLRequest : public NS::Copying<CoreMLRequest,ImageBasedRequest>
	{
	public:
		static CoreMLRequest* alloc();

		/*!
			@brief Create a new request with a model.
			@param model		The VNCoreMLModel to be used.
		*/
		CoreMLRequest* init( VN::CoreMLModel* model );

		VN::ImageCropAndScaleOption imageCropAndScaleOption();
		void setImageCropAndScaleOption( VN::ImageCropAndScaleOption imageCropAndScaleOption );
	}; // end of class CoreMLRequest
} // end of namespace VN

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

_VN_INLINE VN::CoreMLModel* VN::CoreMLModel::model( ML::Model* model, NS::Error** error )
{
	return NS::Object::sendMessage<VN::CoreMLModel*>( _VN_PRIVATE_CLS( VNCoreMLModel ), _VN_PRIVATE_SEL( modelForMLModel_error_ ), model, error );
}

_VN_INLINE VN::CoreMLRequest* VN::CoreMLRequest::alloc()
{
	return NS::Object::alloc<VN::CoreMLRequest>( _VN_PRIVATE_CLS( VNCoreMLRequest ) );
}

_VN_INLINE VN::CoreMLRequest* VN::CoreMLRequest::init( VN::CoreMLModel* model )
{
	return NS::Object::sendMessage<VN::CoreMLRequest*>( this, _VN_PRIVATE_SEL( initWithModel_ ), model );
}

_VN_INLINE VN::ImageCropAndScaleOption VN::CoreMLRequest::imageCropAndScaleOption()
{
	return NS::Object::sendMessage<VN::ImageCropAndScaleOption>( this, _VN_PRIVATE_SEL(imageCropAndScaleOption) );
}

_VN_INLINE void VN::CoreMLRequest::setImageCropAndScaleOption( VN::ImageCropAndScaleOption imageCropAndScaleOption )
{
	return NS::Object::sendMessage<void>( this, _VN_PRIVATE_SEL(setImageCropAndScaleOption_), imageCropAndScaleOption );
}
