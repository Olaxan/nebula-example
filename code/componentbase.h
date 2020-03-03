#pragma once

#include "core/refcounted.h"
#include "gameentity.h"

namespace Components
{
	typedef unsigned InstanceId;

	class ComponentBase : public Core::RefCounted
	{
		__DeclareAbstractClass(ComponentBase)
		__DeclareInterfaceSingleton(ComponentBase)

	public:
		ComponentBase() : _count(0) {};
		virtual ~ComponentBase() = default;
		
		[[nodiscard]] InstanceId RegisterEntity(Entities::GameEntityId e);
		void DeregisterEntity(Entities::GameEntityId e);

		[[nodiscard]] bool HasComponent(Entities::GameEntityId e) const;
		[[nodiscard]] InstanceId GetComponent(Entities::GameEntityId e) const;
		[[nodiscard]] Entities::GameEntityId GetOwner(InstanceId idx) const;
		[[nodiscard]] SizeT Count() const { return _count; }

		virtual void AppendDefault() = 0;
		virtual void EraseInstance(InstanceId instance) = 0;

		virtual void OnActivate(InstanceId instance)			{}
		virtual void OnDeactivate(InstanceId instance)			{}
		virtual void OnDestroy(Entities::GameEntityId entity)	{}
		virtual void OnBeginFrame()								{}
		virtual void OnRender()									{}
		virtual void OnEndFrame()								{}
		virtual void OnMessage(InstanceId instance, int msg)	{}

	protected:
		Util::HashTable<Entities::GameEntityId, InstanceId> _entities;
		Util::Array<Entities::GameEntityId> _owners;
		SizeT _count;
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
