#pragma once

#include "componentbase.h"
#include "componentmanager.h"
#include "core/refcounted.h"
#include "core/singleton.h"

namespace Components
{
	class GraphicsComponent : public ComponentBase
	{
		__DeclareClass(GraphicsComponent)
		__DeclareSingleton(GraphicsComponent)

		struct GraphicsData
		{
			Util::Array<Util::String> uri;
		};
		
	public:
		GraphicsComponent() { __ConstructSingleton; }
		~GraphicsComponent() { __DestructSingleton; }

		Util::String GetResourceUri(const InstanceId idx) { return _data.uri[idx]; }
		void SetResourceUri(const InstanceId idx, const Util::String uri) { _data.uri[idx] = uri; }

	private:
		GraphicsData _data;
	};
}