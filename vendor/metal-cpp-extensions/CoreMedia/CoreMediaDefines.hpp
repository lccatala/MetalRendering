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
// CoreMedia/CoreMediaDefines.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <Foundation/NSDefines.hpp>

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#define _CM_EXPORT _NS_EXPORT
#define _CM_EXTERN _NS_EXTERN
#define _CM_INLINE _NS_INLINE
#define _CM_PACKED _NS_PACKED

#define _CM_CONST(type, name) _NS_CONST(type, name)
#define _CM_ENUM(type, name) _NS_ENUM(type, name)
#define _CM_OPTIONS(type, name) _NS_OPTIONS(type, name)

#define _CM_VALIDATE_SIZE(ns, name) _NS_VALIDATE_SIZE(ns, name)
#define _CM_VALIDATE_ENUM(ns, name) _NS_VALIDATE_ENUM(ns, name)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
