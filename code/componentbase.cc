#include "componentbase.h"

namespace Components
{

	__ImplementAbstractClass(Components::ComponentBase, 'COMP', Core::RefCounted)
	__ImplementInterfaceSingleton(Components::ComponentBase)
	
	InstanceId ComponentBase::RegisterEntity(const Entities::GameEntityId e)
	{
		if (this->HasComponent(e))
			return this->GetComponent(e);

		AppendDefault();
		
		const InstanceId idx = _count;
		_entities.Add(e, idx);
		_owners.Append(e);
		this->OnActivate(idx);
		_count++;
		return idx;
	}

	void ComponentBase::DeregisterEntity(const Entities::GameEntityId e)
	{
		if (HasComponent(e))
		{
			const InstanceId idx = this->GetComponent(e);
			this->OnDeactivate(idx);

			const InstanceId last = _count - 1;
			const Entities::GameEntityId last_e = GetOwner(last);
			RemovePack(idx, last);
			
			_entities[last_e] = idx;
			_entities.Erase(e);

			_owners[last] = last_e;

			_count--;
		}
	}

	bool ComponentBase::HasComponent(const Entities::GameEntityId e) const
	{
		return _entities.Contains(e);
	}

	InstanceId ComponentBase::GetComponent(const Entities::GameEntityId e) const
	{
		return HasComponent(e) ? _entities[e] : 0;
	}

	Entities::GameEntityId ComponentBase::GetOwner(InstanceId idx) const
	{
		return _owners[idx];
	}
}
