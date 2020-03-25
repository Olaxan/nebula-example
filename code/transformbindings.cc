
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
#include "transformcomponent.h"

namespace py = pybind11;


PYBIND11_EMBEDDED_MODULE(transform, m)
{

	m.def("get_world_transform",
		[](const Entities::GameEntityId& id) -> Math::matrix44
		{
			Components::InstanceId cid = Components::Transforms()->GetComponent(id);
			return Components::Transforms()->GetWorldTransform(cid);
		}
	);

	m.def("set_world_transform",
		[](const Entities::GameEntityId& id, const Math::matrix44& mat)
		{
			Components::InstanceId cid = Components::Transforms()->GetComponent(id);
			Components::Transforms()->SetWorldTransform(cid, mat);
		}
	);
}