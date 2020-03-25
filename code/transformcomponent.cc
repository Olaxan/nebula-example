#include "foundation/stdneb.h"
#include "transformcomponent.h"
#include "graphicscomponent.h"

namespace Components
{
	__ImplementClass(TransformComponent, 'TRFM', ComponentBase)
	__ImplementSingleton(TransformComponent)

	void TransformComponent::AppendDefault()
	{
		_data.transform.Append(Math::matrix44::translation(Math::point(0, 0, 0)));
	}

	void TransformComponent::EraseInstance(const InstanceId instance)
	{
		_data.transform.EraseIndexSwap(instance);
	}

	Util::Variant::Type TransformComponent::GetTypeByName(Util::String data)
	{
		if (data == "transform")
		{
			return Util::Variant::Type::Matrix44;
		}

		return Util::Variant::Type::Void;
	}

	bool TransformComponent::SetDataByName(InstanceId instance, Util::String name, Util::Variant value)
	{
		if (name == "transform")
		{
			_data.transform[instance] = value.GetMatrix44();
			return true;
		}
		return false;
	}
}
