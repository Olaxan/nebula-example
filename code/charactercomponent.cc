#include "foundation/stdneb.h"
#include "charactercomponent.h"
#include "graphicscomponent.h"

namespace Components
{
	__ImplementClass(Components::CharacterComponent, 'CHRC', Components::ComponentBase)
	__ImplementSingleton(Components::CharacterComponent)

	void CharacterComponent::AppendDefault()
	{
		_data.skel_uri.Append(Util::String(""));
		_data.anim_uri.Append(Util::String(""));
		_data.tag.Append(Util::StringAtom("Empty"));
		_data.graphics_id.Append(0);
	}

	void CharacterComponent::RemovePack(InstanceId rm, InstanceId last)
	{
		_data.skel_uri[rm] = _data.skel_uri[last];
		_data.anim_uri[rm] = _data.anim_uri[last];
		_data.tag[rm] = _data.tag[last];
		_data.graphics_id[rm] = _data.graphics_id[last];
	}

	Graphics::GraphicsEntityId CharacterComponent::Setup(InstanceId instance)
	{
		const auto gfx_instance = _data.graphics_id[instance];
		const auto gfx_id = Components::Graphics()->GetRenderId(gfx_instance);
		Graphics::RegisterEntity<Characters::CharacterContext>(gfx_id);
		Characters::CharacterContext::Setup(gfx_id, GetSkeletonUri(instance), GetAnimationUri(instance), GetTag(instance));
		return gfx_id;
	}

	void CharacterComponent::OnActivate(InstanceId instance)
	{
		const Entities::GameEntityId owner = GetOwner(instance);
		//n_assert(Components::HasComponent<GraphicsComponent>(owner), "OnActivate: Character component requires valid graphics component\n");
		_data.graphics_id[instance] = Components::GetComponent<GraphicsComponent>(owner);
	}

	void CharacterComponent::OnDeactivate(InstanceId instance)
	{
		Graphics::DeregisterEntity<Characters::CharacterContext>(Components::Graphics()->GetRenderId(_data.graphics_id[instance]));
	}
}
