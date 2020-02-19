#include "foundation/stdneb.h"
#include "charactercomponent.h"
#include "graphicscomponent.h"

namespace Components
{
	__ImplementClass(Components::CharacterComponent, 'CHRC', Components::ComponentBase)
	__ImplementSingleton(Components::CharacterComponent)

	void CharacterComponent::InitializeDefault()
	{
		_data.skel_uri.Append(Util::String(""));
		_data.anim_uri.Append(Util::String(""));
		_data.tag.Append(Util::StringAtom("Empty"));
		_data.graphics_id.Append(0);
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
		if (Components::HasComponent<GraphicsComponent>(owner))
			_data.graphics_id[instance] = Components::GetComponent<GraphicsComponent>(owner);
		else n_warning("OnActivate [%u]: Character component requires valid graphics component\n", instance);
	}

}
