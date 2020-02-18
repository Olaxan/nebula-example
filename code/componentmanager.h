#pragma once

#include "game/manager.h"
#include "componentbase.h"

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
		
		void OnBeginFrame()
		{
			for (auto comp : components)
			{
				comp->OnBeginFrame();
			}
		}
		void OnFrame()
		{
			for (auto comp : components)
			{
				comp->OnRender();
			}
		}
		void OnEndFrame()
		{
			for (auto comp : components)
			{
				comp->OnEndFrame();
			}
		}

	private:
		Util::Array<ComponentBase*> components;
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
	
}