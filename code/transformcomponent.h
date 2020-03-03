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

	public:
		TransformComponent() { __ConstructSingleton; }
		~TransformComponent() { __DestructSingleton; }

		void AppendDefault() override;
		void EraseInstance(InstanceId instance) override;
		
		[[nodiscard]] Math::matrix44 GetWorldTransform(InstanceId idx) const { return _data.transforms[idx]; }
		void SetWorldTransform(InstanceId idx, Math::matrix44 transform) { _data.transforms[idx] = transform; }
		
	private:
		struct TransformData
		{
			Util::Array<Math::matrix44> transforms;
		} _data;
	};

	inline TransformComponent* Transforms()
	{
		return TransformComponent::Instance();
	}
}