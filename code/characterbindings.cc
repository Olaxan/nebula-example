
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
#include "charactercomponent.h"

namespace py = pybind11;


PYBIND11_EMBEDDED_MODULE(character, m)
{

	m.def("get_skeleton_uri",
		[](const Entities::GameEntityId& id) -> Util::String
		{
			Components::InstanceId cid = Components::Characters()->GetComponent(id);
			return Components::Characters()->GetSkeletonUri(cid);
		}
	);

	m.def("set_skeleton_uri",
		[](const Entities::GameEntityId& id, const Util::String uri)
		{
			Components::InstanceId cid = Components::Characters()->GetComponent(id);
			Components::Characters()->SetSkeletonUri(cid, uri);
		}
	);

	m.def("get_animation_uri",
		[](const Entities::GameEntityId& id) -> Util::String
		{
			Components::InstanceId cid = Components::Characters()->GetComponent(id);
			return Components::Characters()->GetAnimationUri(cid);
		}
	);

	m.def("set_animation_uri",
		[](const Entities::GameEntityId& id, const Util::String uri)
		{
			Components::InstanceId cid = Components::Characters()->GetComponent(id);
			Components::Characters()->SetAnimationUri(cid, uri);
		}
	);

	m.def("get_tag",
		[](const Entities::GameEntityId& id) -> Util::String
		{
			Components::InstanceId cid = Components::Characters()->GetComponent(id);
			return Components::Characters()->GetTag(cid).AsString();
		}
	);

	m.def("set_tag",
		[](const Entities::GameEntityId& id, const Util::String tag)
		{
			Components::InstanceId cid = Components::Characters()->GetComponent(id);
			Components::Characters()->SetTag(cid, Util::StringAtom(tag));
		}
	);

	m.def("setup",
		[](const Entities::GameEntityId id)
		{
			Components::InstanceId cid = Components::Characters()->GetComponent(id);
			Components::Characters()->Setup(cid);
		}
	);

	m.def("play",
		[](const Entities::GameEntityId id, IndexT clip, IndexT track)
		{
			Components::InstanceId cid = Components::Characters()->GetComponent(id);
			Components::Characters()->Play(cid, clip, track);
		}
	);

	m.def("queue",
		[](const Entities::GameEntityId id, IndexT clip, IndexT track)
		{
			Components::InstanceId cid = Components::Characters()->GetComponent(id);
			Components::Characters()->Queue(cid, clip, track);
		}
	);
}