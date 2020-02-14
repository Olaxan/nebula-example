//------------------------------------------------------------------------------
// entitymanager.cc
// (C)2017-2020 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "foundation/stdneb.h"
#include "entitymanager.h"

namespace Entities
{

	__ImplementClass(Entities::GameEntityManager, 'EMGR', Game::Manager);
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
		pool.Deallocate(e.id);
		count--;
	}


}
