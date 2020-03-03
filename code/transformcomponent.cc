#include "foundation/stdneb.h"
#include "transformcomponent.h"

namespace Components
{
	__ImplementClass(TransformComponent, 'TRFM', ComponentBase)
	__ImplementSingleton(TransformComponent)

	void TransformComponent::AppendDefault()
	{
		_data.transforms.Append(Math::matrix44::translation(Math::point(0, 0, 0)));
	}

	void TransformComponent::EraseInstance(const InstanceId instance)
	{
		_data.transforms.EraseIndexSwap(instance);
	}
}
