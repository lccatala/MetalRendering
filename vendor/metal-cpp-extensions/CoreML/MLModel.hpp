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
// CoreML/MLModel.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "CoreMLPrivate.hpp"
#include <Foundation/NSObject.hpp>


//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace NS
{
	class URL;
	class Error;
} // end of namespace NS

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace ML
{
	class Model : public NS::Referencing<Model>
	{
	public:
		/// @brief Construct a model with a default MLModelConfiguration object
		static ML::Model* model( NS::URL* url, NS::Error** error );

		// ---------- Methods from MLModel+MLModelCompilation.h ----------

		/** @brief Compile a .mlmodel for this device
		 *
		 * @param modelURL URL file path to .mlmodel file you wish to compile
		 * @param error Any errors are surfaced here
		 *
		 * @returns a URL to the compiled .mlmodelc directory if successful
		 * The model is compiled to a temporary location on disk
		 * You must move the compiled model to a permanent location if you wish to keep it
		 *
		 * @discussion The returned model can be loaded using:
		 * @code
		 * ML::Model::model( NS::URL* url, NS::Error** error )
		 * @endcode
		 */
		static NS::URL* compileModel( NS::URL* modelURL, NS::Error** error );
	}; // end of class Model
} // end of namespace ML

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

_ML_INLINE ML::Model* ML::Model::model( NS::URL* url, NS::Error** error )
{
	return NS::Object::sendMessage<ML::Model*>( _ML_PRIVATE_CLS( MLModel ), _ML_PRIVATE_SEL( modelWithContentsOfURL_error_ ), url, error );
}

_ML_INLINE NS::URL* ML::Model::compileModel( NS::URL* modelURL, NS::Error** error )
{
	return NS::Object::sendMessage<NS::URL*>( _ML_PRIVATE_CLS( MLModel ), _ML_PRIVATE_SEL( compileModelAtURL_error_ ), modelURL, error );
}
