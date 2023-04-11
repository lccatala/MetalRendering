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
// CoreML/MLFeatureType.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "CoreMLPrivate.hpp"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace ML
{
	/*!
	 * Supported data type enumeration
	 */
	_ML_ENUM( NS::Integer, FeatureType )
	{
		FeatureTypeInvalid = 0,

		/// Discrete values, sometimes used to hold numeric encoding of a categorical value
		FeatureTypeInt64 = 1,

		/// Continuous values
		FeatureTypeDouble = 2,

		// Text or categorical strings
		FeatureTypeString = 3,

		/// CVPixelBufferRef
		FeatureTypeImage = 4,

		/// MLMultiArray
		FeatureTypeMultiArray = 5,

		/// Numerically weighted hashable objects (e.g. word counts)
		FeatureTypeDictionary = 6,

		/// MLSequence. Ordered collection of feature values with the same type
		FeatureTypeSequence API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) = 7,
	};
} // end of namespace ML
