
#include "foundation/stdneb.h"
#include "util/string.h"
#include "math/matrix44.h"
#include "math/float4.h"
#include "math/vector.h"
#include "math/point.h"
#include "util/array.h"
#include "game/entity.h"
#include "pybind11/embed.h"
#include "scripting/bindings.h"
#include "pybind11/numpy.h"
#include "pybind11/operators.h"
#include "entitymanager.h"
#include "componentbase.h"
#include "componentmanager.h"

namespace py = pybind11;


PYBIND11_EMBEDDED_MODULE(entities, m)
{
	m.def("create_entity",
		[]()->Entities::GameEntityId
		{
			return Entities::CreateEntity();
		}
	);

	m.def("destroy_entity",
		[](Entities::GameEntityId e)
		{
			return Entities::DestroyEntity(e);
		}
	);

	py::class_<Entities::GameEntityId>(m, "entity")
		.def(py::init([](Ids::Id32 id)
			{
				Entities::GameEntityId e = id;
				return e;
			})
		)
		.def("is_valid",
			[](Entities::GameEntityId id) {
				return Entities::IsAlive(id);
			})
		.def("register_component",
				[](Entities::GameEntityId id, Util::String const& componentName) -> Components::InstanceId
				{
					Components::ComponentBase* component = Components::GetComponentByName(componentName);
					if (component != nullptr)
					{
						return component->RegisterEntity(id);
					}
					return 0;
				}
		)
		.def("deregister_component",
			[](Entities::GameEntityId id, Util::String const& componentName)
			{
				Components::ComponentBase* component = Components::GetComponentByName(componentName);
				if (component != nullptr)
				{
					component->DeregisterEntity(id);
				}
			}
		)
		.def("has_component",
			[](Entities::GameEntityId id, Util::String const& componentName) -> bool
			{
				Components::ComponentBase* component = Components::GetComponentByName(componentName);
				if (component != nullptr)
				{
					return (component->HasComponent(id));
				}
				return false;
			}
		);
}