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
		GraphicsComponent()
		{
			RegisterComponent(this);
		};

	private:
		GraphicsData _data;
	};
}