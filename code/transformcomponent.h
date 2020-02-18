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
			Util::Array<Math::matrix44> transforms;
		};

	public:
		TransformComponent() { __ConstructSingleton; }
		~TransformComponent() { __DestructSingleton; }

		Math::matrix44 GetWorldTransform(InstanceId idx) { return _data.transforms[idx]; }
		void SetWorldTransform(InstanceId idx, Math::matrix44 transform) { _data.transforms[idx] = transform; }
		
	private:
		TransformData _data;
	};
}