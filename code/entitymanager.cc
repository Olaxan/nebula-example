//------------------------------------------------------------------------------
// entitymanager.cc
// (C)2017-2020 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "foundation/stdneb.h"
#include "entitymanager.h"
#include "componentmanager.h"
#include "io/jsonreader.h"

namespace Entities
{

	__ImplementClass(Entities::GameEntityManager, 'EMGR', Core::RefCounted);
	__ImplementSingleton(Entities::GameEntityManager);
	
	//------------------------------------------------------------------------------
	/**
	*/
	GameEntityManager::GameEntityManager() : count(0)
	{
		__ConstructSingleton;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	GameEntityManager::~GameEntityManager()
	{
		__DestructSingleton;
	}
	
	GameEntityId GameEntityManager::CreateGameEntity()
	{
		Entities::GameEntityId e;
		pool.Allocate(e.id);
		count++;
		return e;
	}

	bool GameEntityManager::IsAlive(const GameEntityId e) const
	{
		return pool.IsValid(e.id);
	}
	
	void GameEntityManager::DestroyGameEntity(GameEntityId e)
	{
		if (IsAlive(e))
		{
			pool.Deallocate(e.id);
			Components::ComponentManager::Instance()->OnDestroy(e);
			count--;
		}
	}

	void GameEntityManager::Load(const IO::URI& file)
	{
		Ptr<IO::JsonReader> reader = IO::JsonReader::Create();
		reader->SetStream(IO::IoServer::Instance()->CreateStream(file));
		if (reader->Open())
		{

			reader->SetToFirstChild();
			do
			{
				GameEntityId entity = CreateGameEntity();

				if (reader->HasNode("components"))
				{
					reader->SetToFirstChild("components");
					reader->SetToFirstChild();
					do
					{
						Util::String name = reader->GetCurrentNodeName();
						Components::ComponentBase* component = Components::GetComponentByName(name);

						if (component == nullptr)
							continue;

						Components::InstanceId instance = component->RegisterEntity(entity);

						auto attrs = reader->GetAttrs();

						for (auto data : attrs)
						{
							Util::Variant value;
							value.SetType(component->GetTypeByName(data));

							if (reader->GetOpt(value, data.AsCharPtr()))
							{
								component->SetDataByName(instance, data, value);
							}
						}

						component->OnLoad(instance);

					} while (reader->SetToNextChild());

					reader->SetToParent();
				}

			} while (reader->SetToNextChild());

			reader->Close();
		}
	}
}
