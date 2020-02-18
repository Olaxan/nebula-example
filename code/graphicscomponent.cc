#include "foundation/stdneb.h"
#include "graphicscomponent.h"

namespace Components
{
	__ImplementClass(GraphicsComponent, 'GFXC', ComponentBase)
	__ImplementSingleton(GraphicsComponent)

	void GraphicsComponent::OnActivate(InstanceId instance)
	{
		_data.uri.Append("");
	}
}