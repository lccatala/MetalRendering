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

#include "VisionPrivate.hpp"
#include "VisionDefines.hpp"
#include <Foundation/NSObject.hpp>


//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace NS
{
	class Array;
	class URL;
	class Error;
	class IndexSet;
} // end of namespace NS

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace VN
{
	class Request : public NS::Copying<Request>
	{
	public:
		VN::Request* init();
		void cancel();
		BOOL preferBackgroundProcessing();
		void setPreferBackgroundProcessing( BOOL preferBackgroundProcessing );
		BOOL usesCPUOnly();
		void setUsesCPUOnly( BOOL usesCPUOnly );
		NS::Array* results();
		NS::UInteger revision();
		void setRevision(NS::UInteger revision);
		static NS::IndexSet* supportedRevisions();
		static NS::UInteger defaultRevision();
		static NS::UInteger currentRevision();
	};

	class ImageBasedRequest : public NS::Copying<ImageBasedRequest,Request>
	{
	public:
		CGRect regionOfInterest();
		void setRegionOfInterest(CGRect regionOfInterest);
	};
} // end of namespace VN

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

_VN_INLINE VN::Request* VN::Request::init()
{
	return Object::sendMessage<VN::Request*>( this, _VN_PRIVATE_SEL(init) );
}

_VN_INLINE void VN::Request::cancel()
{
	return Object::sendMessage<void>( this, _VN_PRIVATE_SEL(cancel) );
}

_VN_INLINE BOOL VN::Request::preferBackgroundProcessing()
{
	return Object::sendMessage<BOOL>( this, _VN_PRIVATE_SEL(preferBackgroundProcessing) );
}

_VN_INLINE void VN::Request::setPreferBackgroundProcessing( BOOL preferBackgroundProcessing )
{
	return Object::sendMessage<void>( this, _VN_PRIVATE_SEL(setPreferBackgroundProcessing_), preferBackgroundProcessing );
}

_VN_INLINE BOOL VN::Request::usesCPUOnly()
{
	return Object::sendMessage<BOOL>( this, _VN_PRIVATE_SEL(usesCPUOnly) );
}

_VN_INLINE void VN::Request::setUsesCPUOnly( BOOL usesCPUOnly )
{
	return Object::sendMessage<void>( this, _VN_PRIVATE_SEL(setUsesCPUOnly_), usesCPUOnly );
}

_VN_INLINE NS::Array* VN::Request::results()
{
	return Object::sendMessage<NS::Array*>( this, _VN_PRIVATE_SEL(results) );
}

_VN_INLINE NS::UInteger VN::Request::revision()
{
	return Object::sendMessage<NS::UInteger>( this, _VN_PRIVATE_SEL(revision) );
}

_VN_INLINE void VN::Request::setRevision( NS::UInteger revision )
{
	return Object::sendMessage<void>( this, _VN_PRIVATE_SEL(setRevision_), revision );
}

_VN_INLINE NS::IndexSet* VN::Request::supportedRevisions()
{
	return Object::sendMessage<NS::IndexSet*>( _VN_PRIVATE_CLS(VNRequest), _VN_PRIVATE_SEL(supportedRevisions) );
}

_VN_INLINE NS::UInteger VN::Request::defaultRevision()
{
	return Object::sendMessage<NS::UInteger>( _VN_PRIVATE_CLS(VNRequest), _VN_PRIVATE_SEL(defaultRevision) );
}

_VN_INLINE NS::UInteger VN::Request::currentRevision()
{
	return Object::sendMessage<NS::UInteger>( _VN_PRIVATE_CLS(VNRequest), _VN_PRIVATE_SEL(currentRevision) );
}

// ------------------------------------------------------------

_VN_INLINE CGRect VN::ImageBasedRequest::regionOfInterest()
{
	return Object::sendMessage<CGRect>( this, _VN_PRIVATE_SEL(regionOfInterest) );
}

_VN_INLINE void VN::ImageBasedRequest::setRegionOfInterest(CGRect regionOfInterest)
{
	return Object::sendMessage<void>( this, _VN_PRIVATE_SEL(setRegionOfInterest_), regionOfInterest );
}
