#pragma once

#include "game/manager.h"
#include "componentbase.h"

namespace Components
{
	class ComponentManager : public Game::Manager
	{
		__DeclareClass(ComponentManager)
		__DeclareSingleton(ComponentManager)

	public:

		ComponentManager() = default;
		~ComponentManager() = default;
		
		void RegisterComponent(ComponentBase* comp);
		void DeregisterComponent(ComponentBase* comp);
		
		void OnBeginFrame() override
		{
			for (auto comp : components)
			{
				comp->OnBeginFrame();
			}
		}
		void OnFrame() override
		{
			for (auto comp : components)
			{
				comp->OnRender();
			}
		}
		void OnEndFrame() override
		{
			for (auto comp : components)
			{
				comp->OnEndFrame();
			}
		}

	private:
		Util::Array<ComponentBase*> components;
	};

	inline void RegisterComponent(ComponentBase* comp)
	{
		ComponentManager::Instance()->RegisterComponent(comp);
	}

	inline void DeregisterComponent(ComponentBase* comp)
	{
		ComponentManager::Instance()->DeregisterComponent(comp);
	}
	
}