#include "componentmanager.h"

namespace Components
{
	__ImplementClass(ComponentManager, 'CMGR', Game::Manager)
	__ImplementSingleton(ComponentManager)

	void ComponentManager::RegisterComponent(ComponentBase* comp)
	{
		components.Append(comp);
	}

	void ComponentManager::DeregisterComponent(ComponentBase* comp)
	{
		auto it = components.Find(comp);
		if (it != components.End())
			components.Erase(it);
	}
}
