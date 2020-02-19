#include "componentbase.h"

namespace Components
{

	__ImplementAbstractClass(Components::ComponentBase, 'COMP', Core::RefCounted)
	__ImplementInterfaceSingleton(ComponentBase)
	
	InstanceId ComponentBase::RegisterEntity(const Entities::GameEntityId e)
	{
		if (this->HasComponent(e))
			return this->GetComponent(e);

		InitializeDefault();
		
		const InstanceId idx = _entities.Size();
		_entities.Add(e, idx);
		_owners.Add(idx, e);
		_count++;
		this->OnActivate(idx);
		return idx;
	}

	void ComponentBase::DeregisterEntity(const Entities::GameEntityId e)
	{
		if (HasComponent(e))
		{
			const InstanceId idx = this->GetComponent(e);
			this->OnDeactivate(idx);
			_entities.Erase(e);
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
		return _owners.Contains(idx) ? _owners[idx] : 0; //TODO: Return a better invalid-value.
	}
}
