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
		
		void RegisterComponent(ComponentBase* comp);
		void DeregisterComponent(ComponentBase* comp);
		void Message(Entities::GameEntityId e, int msg);
		
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
				comp->DeregisterEntity(e);
			}
		}

	private:
		Util::Array<ComponentBase*> _components;
	};

	template<typename COMPONENT>
	void RegisterComponent()
	{
		if (!COMPONENT::HasInstance()) { COMPONENT::Create(); }
		
		ComponentManager::Instance()->RegisterComponent(COMPONENT::Instance());
	}

	inline void DeregisterComponent(ComponentBase* comp)
	{
		ComponentManager::Instance()->DeregisterComponent(comp);
	}

	inline void Message(Entities::GameEntityId e, int temp_msg)
	{
		ComponentManager::Instance()->Message(e, temp_msg);
	}
	
}