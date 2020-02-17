#pragma once

#include "componentbase.h"
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
		GraphicsComponent() = default;

	private:
		GraphicsData _data;
	};
}