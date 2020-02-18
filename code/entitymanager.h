#pragma once

#include "core/refcounted.h"
#include "ids/idgenerationpool.h"
#include "ids/id.h"
#include "gameentity.h"

namespace Entities
{
	class GameEntityManager : public Core::RefCounted
	{
		__DeclareClass(GameEntityManager);
		__DeclareSingleton(GameEntityManager);

	public:
		/// constructor
		GameEntityManager();
		/// destructor
		~GameEntityManager();

		GameEntityId CreateGameEntity();
		bool IsAlive(GameEntityId e) const;
		void DestroyGameEntity(GameEntityId e);
		uint Count() const { return count; }
		
	private:

		SizeT count;
		Ids::IdGenerationPool pool;
	};

	static GameEntityId
	CreateEntity()
	{
		return GameEntityManager::Instance()->CreateGameEntity();
	}

	static void
	DestroyEntity(const GameEntityId id)
	{
		GameEntityManager::Instance()->DestroyGameEntity(id);
	}
}
