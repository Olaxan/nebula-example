#include "componentmanager.h"

namespace Components
{
	__ImplementClass(Components::ComponentManager, 'CMGR', Core::RefCounted)
	__ImplementSingleton(Components::ComponentManager)
	
	void ComponentManager::RegisterComponent(ComponentBase* comp, Util::FourCC fcc, Util::StringAtom name)
	{
		_components.Append(comp);
		_components_fcc.Add(fcc, comp);
		_components_name.Add(name, comp);
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
			const InstanceId idx = comp->GetComponent(e);
			comp->OnMessage(idx, msg);
		}
	}

	ComponentBase* ComponentManager::GetComponentByFourCC(Util::FourCC fcc)
	{
		IndexT idx = this->_components_fcc.FindIndex(fcc);
		if (idx != InvalidIndex)
		{
			return this->_components_fcc.ValueAtIndex(fcc, idx);
		}
		return nullptr;;
	}

	ComponentBase* ComponentManager::GetComponentByName(Util::StringAtom name)
	{
		IndexT idx = this->_components_name.FindIndex(name);
		if (idx != InvalidIndex)
		{
			return this->_components_name.ValueAtIndex(name, idx);
		}
		return nullptr;
	}
}
