#pragma once

#include "componentbase.h"
#include "componentmanager.h"
#include "core/refcounted.h"
#include "core/singleton.h"

namespace Components
{
	class TransformComponent : public ComponentBase
	{
		__DeclareClass(TransformComponent)
		__DeclareSingleton(TransformComponent)

		struct TransformData
		{
			Math::matrix44 transform;
		};

	public:
		TransformComponent()
		{
			RegisterComponent(this);
		};

	private:
		TransformData _data;
	};
}