
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
#include "graphicscomponent.h"

namespace py = pybind11;


PYBIND11_EMBEDDED_MODULE(graphics, m)
{

	m.def("get_resource_uri",
		[](const Entities::GameEntityId& id) -> Util::String
		{
			Components::InstanceId cid = Components::Graphics()->GetComponent(id);
			return Components::Graphics()->GetResourceUri(cid);
		}
	);

	m.def("set_resource_uri",
		[](const Entities::GameEntityId& id, const Util::String uri)
		{
			Components::InstanceId cid = Components::Graphics()->GetComponent(id);
			Components::Graphics()->SetResourceUri(cid, uri);
		}
	);

	m.def("get_tag",
		[](const Entities::GameEntityId& id) -> Util::String
		{
			Components::InstanceId cid = Components::Graphics()->GetComponent(id);
			return Components::Graphics()->GetTag(cid).AsString();
		}
	);

	m.def("set_tag",
		[](const Entities::GameEntityId& id, const Util::String tag)
		{
			Components::InstanceId cid = Components::Graphics()->GetComponent(id);
			Components::Graphics()->SetTag(cid, Util::StringAtom(tag));
		}
	);

	m.def("get_visibility_type",
		[](const Entities::GameEntityId& id) -> uint8_t
		{
			Components::InstanceId cid = Components::Graphics()->GetComponent(id);
			return Components::Graphics()->GetVisibilityType(cid);
		}
	);

	m.def("set_visibility_type",
		[](const Entities::GameEntityId& id, uint8_t visibility_type)
		{
			Components::InstanceId cid = Components::Graphics()->GetComponent(id);
			Components::Graphics()->SetVisibilityType(cid, static_cast<Visibility::VisibilityEntityType>(visibility_type));
		}
	);

	m.def("get_render_id",
		[](const Entities::GameEntityId& id)
		{
			Components::InstanceId cid = Components::Graphics()->GetComponent(id);
			return Components::Graphics()->GetRenderId(cid);
		}
	);

	m.def("setup",
		[](const Entities::GameEntityId id)
		{
			Components::InstanceId cid = Components::Graphics()->GetComponent(id);
			Components::Graphics()->Setup(cid);
		}
	);
}