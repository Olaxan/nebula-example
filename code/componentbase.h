#pragma once

#include "core/refcounted.h"
#include "gameentity.h"

namespace Components
{
	typedef unsigned InstanceId;

	class ComponentBase : public Core::RefCounted
	{
		__DeclareAbstractClass(ComponentBase)

	public:
		ComponentBase() = default;
		virtual ~ComponentBase() = default;
		
		InstanceId RegisterEntity(Entities::GameEntityId e);
		void DeregisterEntity(Entities::GameEntityId e);
		
		bool HasComponent(Entities::GameEntityId e) const;
		InstanceId GetComponent(Entities::GameEntityId e) const;
		
		virtual void OnActivate(InstanceId instance)	{};
		virtual void OnDeactivate(InstanceId instance)	{};
		virtual void OnBeginFrame()						{};
		virtual void OnRender()							{};
		virtual void OnEndFrame()						{};

	private:
		Util::HashTable<Entities::GameEntityId, InstanceId> _entities;
		Util::Array<Entities::GameEntityId> _owners;
	};

	template<typename COMPONENT>
	InstanceId Register(Entities::GameEntityId e)
	{
		return COMPONENT::Instance()->RegisterEntity(e);
	}
	
	template<typename COMPONENT>
	void Deregister(Entities::GameEntityId e)
	{
		COMPONENT::Instance()->DeregisterEntity(e);
	}
	
	template<typename COMPONENT>
	static bool HasComponent(Entities::GameEntityId e)
	{
		return COMPONENT::Instance()->HasComponent(e);
	}

	template<typename COMPONENT>
	InstanceId GetComponent(Entities::GameEntityId e)
	{
		return COMPONENT::Instance()->GetComponent(e);
	}
}
