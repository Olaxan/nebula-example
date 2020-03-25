#pragma once

#include "componentbase.h"
#include "gameentity.h"

namespace Components
{
	class ComponentManager : public Core::RefCounted
	{
		__DeclareClass(ComponentManager)
		__DeclareSingleton(ComponentManager)

	public:

		ComponentManager() { __ConstructSingleton }
		~ComponentManager() { __DestructSingleton }
		
		void RegisterComponent(ComponentBase* comp, Util::FourCC fcc, Util::StringAtom name);
		void DeregisterComponent(ComponentBase* comp);
		void Message(Entities::GameEntityId e, int msg);

		ComponentBase* GetComponentByFourCC(Util::FourCC fcc);
		ComponentBase* GetComponentByName(Util::StringAtom name);
		
		void OnBeginFrame()
		{
			for (auto comp : _components)
			{
				comp->OnBeginFrame();
			}
		}
		void OnFrame()
		{
			for (auto comp : _components)
			{
				comp->OnRender();
			}
		}
		void OnEndFrame()
		{
			for (auto comp : _components)
			{
				comp->OnEndFrame();
			}
		}
		void OnDestroy(Entities::GameEntityId e)
		{
			for (auto comp: _components)
			{
				comp->OnDestroy(e);
				comp->DeregisterEntity(e);
			}
		}

	private:
		Util::Array<ComponentBase*> _components;
		Util::HashTable<Util::FourCC, ComponentBase*> _components_fcc;
		Util::HashTable<Util::StringAtom, ComponentBase*> _components_name;
	};

	template<typename COMPONENT>
	void RegisterComponent(Util::FourCC fcc, Util::StringAtom name)
	{
		if (!COMPONENT::HasInstance()) { COMPONENT::Create(); }
		
		ComponentManager::Instance()->RegisterComponent(COMPONENT::Instance(), fcc, name);
	}

	inline void DeregisterComponent(ComponentBase* comp)
	{
		ComponentManager::Instance()->DeregisterComponent(comp);
	}

	inline ComponentBase* GetComponentByFourCC(Util::FourCC fcc)
	{
		return ComponentManager::Instance()->GetComponentByFourCC(fcc);
	}

	inline ComponentBase* GetComponentByName(Util::StringAtom name)
	{
		return ComponentManager::Instance()->GetComponentByName(name);
	}

	inline void Message(Entities::GameEntityId e, int temp_msg)
	{
		ComponentManager::Instance()->Message(e, temp_msg);
	}
	
}