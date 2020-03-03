#include "foundation/stdneb.h"
#include "charactercomponent.h"
#include "graphicscomponent.h"

namespace Components
{
	__ImplementClass(Components::CharacterComponent, 'CHRC', Components::ComponentBase)
	__ImplementSingleton(Components::CharacterComponent)

	void CharacterComponent::AppendDefault()
	{
		_data.gfx_id.Append(0);
		_data.skel_uri.Append(Util::String(""));
		_data.anim_uri.Append(Util::String(""));
		_data.tag.Append(Util::StringAtom("Empty"));
	}

	void CharacterComponent::EraseInstance(const InstanceId instance)
	{
		_data.gfx_id.EraseIndexSwap(instance);
		_data.skel_uri.EraseIndexSwap(instance);
		_data.anim_uri.EraseIndexSwap(instance);
		_data.tag.EraseIndexSwap(instance);
	}

	Graphics::GraphicsEntityId CharacterComponent::Setup(const InstanceId instance)
	{
		const Entities::GameEntityId owner = GetOwner(instance);
		n_assert2(Components::HasComponent<GraphicsComponent>(owner), "OnActivate: Character component requires valid graphics component\n");
		const auto gfx_instance = Components::GetComponent<GraphicsComponent>(owner);
		const auto gfx_id = Graphics()->GetRenderId(gfx_instance);
		
		_data.gfx_id[instance] = gfx_id;
		Graphics::RegisterEntity<Characters::CharacterContext>(gfx_id);
		Characters::CharacterContext::Setup(gfx_id, GetSkeletonUri(instance), GetAnimationUri(instance), GetTag(instance));
		return gfx_id;
	}

	void CharacterComponent::OnDeactivate(const InstanceId instance)
	{
		Characters::CharacterContext::DeregisterEntity(_data.gfx_id[instance]);
	}
}
