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
// CoreML/CoreMLPrivate.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <objc/runtime.h>
#include "CoreMLDefines.hpp"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#define _ML_PRIVATE_CLS( symbol )    ( Private::Class::s_k ## symbol )
#define _ML_PRIVATE_SEL( accessor )  ( Private::Selector::s_k ## accessor )

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#if defined( ML_PRIVATE_IMPLEMENTATION )

#define _ML_PRIVATE_VISIBILITY       __attribute__( ( visibility( "default" ) ) )
#define _ML_PRIVATE_IMPORT           __attribute__( ( weak_import ) )

#if __OBJC__
#define  _ML_PRIVATE_OBJC_LOOKUP_CLASS( symbol  )   ( ( __bridge void* ) objc_lookUpClass( # symbol ) )
#else
#define  _ML_PRIVATE_OBJC_LOOKUP_CLASS( symbol  )   objc_lookUpClass( # symbol )
#endif // __OBJC__

#define _ML_PRIVATE_DEF_CLS( symbol )            void*           s_k ## symbol     _ML_PRIVATE_VISIBILITY = _ML_PRIVATE_OBJC_LOOKUP_CLASS( symbol );
#define _ML_PRIVATE_DEF_SEL( accessor, symbol )  SEL             s_k ## accessor   _ML_PRIVATE_VISIBILITY = sel_registerName( symbol );
#define _ML_PRIVATE_DEF_CONST( type, symbol )    _ML_EXTERN type const    kML ## symbol   _ML_PRIVATE_IMPORT; \
                                                            type const    ML::symbol = ( nullptr != &kML ## symbol ) ? kML ## symbol : nullptr;

#else

#define _ML_PRIVATE_DEF_CLS( symbol )            extern void*     s_k ## symbol;
#define _ML_PRIVATE_DEF_SEL( accessor, symbol )  extern SEL       s_k ## accessor;
#define _ML_PRIVATE_DEF_CONST( type, symbol )


#endif // ML_PRIVATE_IMPLEMENTATION

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace ML::Private::Class
{
	_ML_PRIVATE_DEF_CLS( MLFeatureValue );
	_ML_PRIVATE_DEF_CLS( MLModel );
} // Class

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace ML::Private::Selector
{
	_ML_PRIVATE_DEF_SEL( compileModelAtURL_error_, "compileModelAtURL:error:" );
	_ML_PRIVATE_DEF_SEL( count, "count" );
	_ML_PRIVATE_DEF_SEL( dataPointer, "dataPointer" );
	_ML_PRIVATE_DEF_SEL( dataType, "dataType" );
	_ML_PRIVATE_DEF_SEL( dictionaryValue, "dictionaryValue" );
	_ML_PRIVATE_DEF_SEL( doubleValue, "doubleValue" );
	_ML_PRIVATE_DEF_SEL( featureValueWithDictionary_error_, "featureValueWithDictionary:error:" );
	_ML_PRIVATE_DEF_SEL( featureValueWithDouble_, "featureValueWithDouble:" );
	_ML_PRIVATE_DEF_SEL( featureValueWithInt64_, "featureValueWithInt64:" );
	_ML_PRIVATE_DEF_SEL( featureValueWithMultiArray_, "featureValueWithMultiArray:" );
	_ML_PRIVATE_DEF_SEL( featureValueWithPixelBuffer_, "featureValueWithPixelBuffer:" );
	_ML_PRIVATE_DEF_SEL( featureValueWithSequence_, "featureValueWithSequence:" );
	_ML_PRIVATE_DEF_SEL( featureValueWithString_, "featureValueWithString:" );
	_ML_PRIVATE_DEF_SEL( imageBufferValue, "imageBufferValue" );
	_ML_PRIVATE_DEF_SEL( int64Value, "int64Value" );
	_ML_PRIVATE_DEF_SEL( isEqualToFeatureValue_, "isEqualToFeatureValue:" );
	_ML_PRIVATE_DEF_SEL( isUndefined, "isUndefined" );
	_ML_PRIVATE_DEF_SEL( modelWithContentsOfURL_error_, "modelWithContentsOfURL:error:" );
	_ML_PRIVATE_DEF_SEL( multiArrayValue, "multiArrayValue" );
	_ML_PRIVATE_DEF_SEL( pixelBuffer, "pixelBuffer" );
	_ML_PRIVATE_DEF_SEL( sequenceValue, "sequenceValue" );
	_ML_PRIVATE_DEF_SEL( shape, "shape" );
	_ML_PRIVATE_DEF_SEL( strides, "strides" );
	_ML_PRIVATE_DEF_SEL( stringValue, "stringValue" );
	_ML_PRIVATE_DEF_SEL( type, "type" );
	_ML_PRIVATE_DEF_SEL( undefinedFeatureValueWithType_, "undefinedFeatureValueWithType:" );
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
