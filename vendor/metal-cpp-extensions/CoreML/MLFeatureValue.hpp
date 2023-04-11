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
// CoreML/MLFeatureValue.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "CoreMLPrivate.hpp"
#include "MLFeatureType.hpp"
#include <CoreVideo/CVPixelBuffer.hpp>

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace ML
{
	class MultiArray;
	class Sequence;
} // end of namespace ML

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace ML
{
	class FeatureValue : public NS::Copying<FeatureValue>
	{
	public:
		static ML::FeatureValue* featureValueWithInt64(int64_t value);
		static ML::FeatureValue* featureValueWithDouble(double value);
		static ML::FeatureValue* featureValueWithString(NS::String* value);
		static ML::FeatureValue* featureValueWithMultiArray(ML::MultiArray* value);
		static ML::FeatureValue* featureValueWithPixelBuffer(CV::PixelBufferRef value);
		static ML::FeatureValue* featureValueWithSequence(ML::Sequence* sequence);
		static ML::FeatureValue* undefinedFeatureValueWithType(ML::FeatureType type);
		static ML::FeatureValue* featureValueWithDictionaryError(NS::Dictionary* value, NS::Error** error);
		BOOL isEqualToFeatureValue(ML::FeatureValue* value);
		ML::FeatureType type();
		BOOL isUndefined();
		int64_t int64Value();
		double doubleValue();
		NS::String* stringValue();
		ML::MultiArray* multiArrayValue();
		NS::Dictionary* dictionaryValue();
		CV::PixelBufferRef imageBufferValue();
		ML::Sequence* sequenceValue();
	}; // end of class FeatureValue

} // end of namespace ML


// ------------------------------------------------------------

_ML_INLINE ML::FeatureValue* ML::FeatureValue::featureValueWithInt64(int64_t value)
{
	return Object::sendMessage<ML::FeatureValue*>( _ML_PRIVATE_CLS(MLFeatureValue), _ML_PRIVATE_SEL(featureValueWithInt64_), value );
}

_ML_INLINE ML::FeatureValue* ML::FeatureValue::featureValueWithDouble(double value)
{
	return Object::sendMessage<ML::FeatureValue*>( _ML_PRIVATE_CLS(MLFeatureValue), _ML_PRIVATE_SEL(featureValueWithDouble_), value );
}

_ML_INLINE ML::FeatureValue* ML::FeatureValue::featureValueWithString(NS::String* value)
{
	return Object::sendMessage<ML::FeatureValue*>( _ML_PRIVATE_CLS(MLFeatureValue), _ML_PRIVATE_SEL(featureValueWithString_), value );
}

_ML_INLINE ML::FeatureValue* ML::FeatureValue::featureValueWithMultiArray(ML::MultiArray* value)
{
	return Object::sendMessage<ML::FeatureValue*>( _ML_PRIVATE_CLS(MLFeatureValue), _ML_PRIVATE_SEL(featureValueWithMultiArray_), value );
}

_ML_INLINE ML::FeatureValue* ML::FeatureValue::featureValueWithPixelBuffer(CV::PixelBufferRef value)
{
	return Object::sendMessage<ML::FeatureValue*>( _ML_PRIVATE_CLS(MLFeatureValue), _ML_PRIVATE_SEL(featureValueWithPixelBuffer_), value );
}

_ML_INLINE ML::FeatureValue* ML::FeatureValue::featureValueWithSequence(ML::Sequence* sequence)
{
	return Object::sendMessage<ML::FeatureValue*>( _ML_PRIVATE_CLS(MLFeatureValue), _ML_PRIVATE_SEL(featureValueWithSequence_), sequence );
}

_ML_INLINE ML::FeatureValue* ML::FeatureValue::undefinedFeatureValueWithType(ML::FeatureType type)
{
	return Object::sendMessage<ML::FeatureValue*>( _ML_PRIVATE_CLS(MLFeatureValue), _ML_PRIVATE_SEL(undefinedFeatureValueWithType_), type );
}

_ML_INLINE ML::FeatureValue* ML::FeatureValue::featureValueWithDictionaryError(NS::Dictionary* value, NS::Error** error)
{
	return Object::sendMessage<ML::FeatureValue*>( _ML_PRIVATE_CLS(MLFeatureValue), _ML_PRIVATE_SEL(featureValueWithDictionary_error_), value, error );
}

_ML_INLINE BOOL ML::FeatureValue::isEqualToFeatureValue(ML::FeatureValue* value)
{
	return Object::sendMessage<BOOL>( this, _ML_PRIVATE_SEL(isEqualToFeatureValue_), value );
}

_ML_INLINE ML::FeatureType ML::FeatureValue::type()
{
	return Object::sendMessage<ML::FeatureType>( this, _ML_PRIVATE_SEL(type) );
}

_ML_INLINE BOOL ML::FeatureValue::isUndefined()
{
	return Object::sendMessage<BOOL>( this, _ML_PRIVATE_SEL(isUndefined) );
}

_ML_INLINE int64_t ML::FeatureValue::int64Value()
{
	return Object::sendMessage<int64_t>( this, _ML_PRIVATE_SEL(int64Value) );
}

_ML_INLINE double ML::FeatureValue::doubleValue()
{
	return Object::sendMessage<double>( this, _ML_PRIVATE_SEL(doubleValue) );
}

_ML_INLINE NS::String* ML::FeatureValue::stringValue()
{
	return Object::sendMessage<NS::String*>( this, _ML_PRIVATE_SEL(stringValue) );
}

_ML_INLINE ML::MultiArray* ML::FeatureValue::multiArrayValue()
{
	return Object::sendMessage<ML::MultiArray*>( this, _ML_PRIVATE_SEL(multiArrayValue) );
}

_ML_INLINE NS::Dictionary* ML::FeatureValue::dictionaryValue()
{
	return Object::sendMessage<NS::Dictionary*>( this, _ML_PRIVATE_SEL(dictionaryValue) );
}

_ML_INLINE CV::PixelBufferRef ML::FeatureValue::imageBufferValue()
{
	return Object::sendMessage<CV::PixelBufferRef>( this, _ML_PRIVATE_SEL(imageBufferValue) );
}

_ML_INLINE ML::Sequence* ML::FeatureValue::sequenceValue()
{
	return Object::sendMessage<ML::Sequence*>( this, _ML_PRIVATE_SEL(sequenceValue) );
}
