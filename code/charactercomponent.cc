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
		n_assert2(Components::HasComponent<GraphicsComponent>(owner), "Setup: Character component requires valid graphics component\n");
		const auto gfx_instance = Components::GetComponent<GraphicsComponent>(owner);
		const auto gfx_id = Graphics()->GetRenderId(gfx_instance);
		
		_data.gfx_id[instance] = gfx_id;
		Graphics::RegisterEntity<Characters::CharacterContext>(gfx_id);
		Characters::CharacterContext::Setup(gfx_id, GetSkeletonUri(instance), GetAnimationUri(instance), GetTag(instance));
		return gfx_id;
	}

	void CharacterComponent::OnLoad(const InstanceId instance)
	{
		Setup(instance);
		Play(instance, 0, 0);
	}

	void CharacterComponent::OnDeactivate(const InstanceId instance)
	{
		if (Characters::CharacterContext::IsEntityRegistered(_data.gfx_id[instance]))
		{
			n_printf("De-registering instance %i, gfx %i from characters\n", instance, _data.gfx_id[instance]);
			Characters::CharacterContext::StopAllTracks(_data.gfx_id[instance]);
			Characters::CharacterContext::DeregisterEntity(_data.gfx_id[instance]);
		}
	}

	void CharacterComponent::Play(InstanceId instance, IndexT clip, IndexT track)
	{
		auto id = _data.gfx_id[instance];
		Characters::CharacterContext::PlayClip(id, nullptr, clip, track, Characters::EnqueueMode::Replace);
	}

	void CharacterComponent::Queue(InstanceId instance, IndexT clip, IndexT track)
	{
		auto id = _data.gfx_id[instance];
		Characters::CharacterContext::PlayClip(id, nullptr, clip, track, Characters::EnqueueMode::Append);
	}

	Util::Variant::Type CharacterComponent::GetTypeByName(Util::String data)
	{
		if (data == "gfx_id")
			return Util::Variant::Type::Int;

		if (data == "skel_uri")
			return Util::Variant::Type::String;

		if (data == "anim_uri")
			return Util::Variant::Type::String;

		if (data == "tag")
			return Util::Variant::Type::String;

		return Util::Variant::Type::Void;
	}

	bool CharacterComponent::SetDataByName(InstanceId instance, Util::String data, Util::Variant value)
	{
		if (data == "gfx_id")
		{
			n_warning("Graphics ID should not be manually changed.");
			_data.gfx_id[instance] = value.GetInt();
			return true;
		}

		if (data == "skel_uri")
		{
			_data.skel_uri[instance] = value.GetString();
			return true;
		}

		if (data == "anim_uri")
		{
			_data.anim_uri[instance] = value.GetString();
			return true;
		}

		if (data == "tag")
		{
			_data.tag[instance] = value.GetString();
			return true;
		}

		return false;
	}
}
