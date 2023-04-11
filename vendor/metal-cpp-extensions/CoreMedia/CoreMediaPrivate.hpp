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
// CoreMedia/CoreMediaPrivate.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <objc/runtime.h>
#include "CoreMediaDefines.hpp"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#define _CM_PRIVATE_CLS( symbol )    ( Private::Class::s_k ## symbol )
#define _CM_PRIVATE_SEL( accessor )  ( Private::Selector::s_k ## accessor )

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#if defined( CM_PRIVATE_IMPLEMENTATION )

#define _CM_PRIVATE_VISIBILITY       __attribute__( ( visibility( "default" ) ) )
#define _CM_PRIVATE_IMPORT           __attribute__( ( weak_import ) )

#if __OBJC__
#define  _CM_PRIVATE_OBJC_LOOKUP_CLASS( symbol  )   ( ( __bridge void* ) objc_lookUpClass( # symbol ) )
#else
#define  _CM_PRIVATE_OBJC_LOOKUP_CLASS( symbol  )   objc_lookUpClass( # symbol )
#endif // __OBJC__

#define _CM_PRIVATE_DEF_CLS( symbol )            void*           s_k ## symbol     _CM_PRIVATE_VISIBILITY = _CM_PRIVATE_OBJC_LOOKUP_CLASS( symbol );
#define _CM_PRIVATE_DEF_SEL( accessor, symbol )  SEL             s_k ## accessor   _CM_PRIVATE_VISIBILITY = sel_registerName( symbol );
#define _CM_PRIVATE_DEF_CONST( type, symbol )    _CM_EXTERN type const    CM ## symbol   _CM_PRIVATE_IMPORT; \
													type const            CM::symbol = ( nullptr != &CM ## symbol ) ? CM ## symbol : nullptr;


#else

#define _CM_PRIVATE_DEF_CLS( symbol )            extern void*     s_k ## symbol;
#define _CM_PRIVATE_DEF_SEL( accessor, symbol )  extern SEL       s_k ## accessor;
#define _CM_PRIVATE_DEF_CONST( type, symbol )


#endif // CM_PRIVATE_IMPLEMENTATION

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace CM::Private::Class
{


} // Class

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace CM::Private::Selector
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
