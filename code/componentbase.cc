#include "componentbase.h"

namespace Components
{

	__ImplementClass(ComponentBase, 'COMP', Core::RefCounted)
	
	InstanceId ComponentBase::RegisterEntity(const Entities::GameEntityId e)
	{
		const unsigned idx = _entities.Size() + 1;
		_entities.Add(e, idx);
		return idx;
	}

	void ComponentBase::DeregisterEntity(const Entities::GameEntityId e)
	{
		if (HasComponent(e))
			_entities.Erase(e);
	}

	bool ComponentBase::HasComponent(const Entities::GameEntityId e) const
	{
		return _entities.Contains(e);
	}

	InstanceId ComponentBase::GetComponent(const Entities::GameEntityId e) const
	{
		return HasComponent(e) ? _entities[e] : 0;
	}
}
