#include "componentmanager.h"

namespace Components
{
	__ImplementClass(ComponentManager, 'CMGR', Core::RefCounted)
	__ImplementSingleton(ComponentManager)
	
	void ComponentManager::RegisterComponent(ComponentBase* comp)
	{
		_components.Append(comp);
	}

	void ComponentManager::DeregisterComponent(ComponentBase* comp)
	{
		const auto it = _components.Find(comp);
		if (it != _components.End())
			_components.Erase(it);
	}

	void ComponentManager::Message(const Entities::GameEntityId e, int msg)
	{
		for (auto comp : _components)
		{
			InstanceId idx = comp->GetComponent(e);
			comp->OnMessage(idx, msg);
		}
	}
}
