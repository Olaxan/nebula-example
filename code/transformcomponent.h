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
		Util::Variant::Type GetTypeByName(Util::String data);
		bool SetDataByName(InstanceId instance, Util::String name, Util::Variant value);
		
		[[nodiscard]] Math::matrix44 GetWorldTransform(InstanceId idx) const { return _data.transform[idx]; }
		void SetWorldTransform(InstanceId idx, Math::matrix44 transform) { _data.transform[idx] = transform; }
		
	private:
		struct
		{
			Util::Array<Math::matrix44> transform;
		} _data;
	};

	inline TransformComponent* Transforms()
	{
		return TransformComponent::Instance();
	}
}