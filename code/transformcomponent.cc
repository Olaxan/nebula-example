#include "foundation/stdneb.h"
#include "transformcomponent.h"

namespace Components
{
	__ImplementClass(TransformComponent, 'TRFM', ComponentBase)
	__ImplementSingleton(TransformComponent)

	void TransformComponent::InitializeDefault()
	{
		_data.transforms.Append(Math::matrix44::translation(Math::point(0, 0, 0)));
	}
}