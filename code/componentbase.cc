#include "componentbase.h"

namespace Components
{

	__ImplementAbstractClass(Components::ComponentBase, 'COMP', Core::RefCounted)
	__ImplementInterfaceSingleton(Components::ComponentBase)
	
	InstanceId ComponentBase::RegisterEntity(const Entities::GameEntityId e)
	{
		if (this->HasComponent(e))
			return this->GetComponent(e);

		_owners.Append(e);
		AppendDefault();
		
		const InstanceId idx = _count;
		_entities.Add(e, idx);
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
			
			_owners.EraseIndexSwap(idx);
			EraseInstance(idx);

			_entities[last_e] = idx;
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
		n_assert2(HasComponent(e), "Entity doesn't have requested component");
		return _entities[e];
	}

	Entities::GameEntityId ComponentBase::GetOwner(InstanceId idx) const
	{
		return _owners[idx];
	}
}
