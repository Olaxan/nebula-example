#include "foundation/stdneb.h"
#include "graphicscomponent.h"
#include "transformcomponent.h"

namespace Components
{
	__ImplementClass(Components::GraphicsComponent, 'GFXC', Components::ComponentBase)
	__ImplementSingleton(Components::GraphicsComponent)

	void GraphicsComponent::InitializeDefault()
	{
		_data.uri.Append(Util::String(""));
		_data.tag.Append(Util::StringAtom("Empty"));
		_data.transform_id.Append(0);
		_data.gfx_id.Append(0);
		_data.visibility_type.Append(Visibility::VisibilityEntityType::Model);
	}

	Graphics::GraphicsEntityId GraphicsComponent::Setup(InstanceId instance)
	{
		auto entity = Graphics::CreateEntity();
		Graphics::RegisterEntity<Models::ModelContext, Visibility::ObservableContext>(entity);
		Models::ModelContext::Setup(entity, GetResourceUri(instance), GetTag(instance));
		const auto trans = Transforms()->GetWorldTransform(_data.transform_id[instance]);
		Models::ModelContext::SetTransform(entity, trans);
		Visibility::ObservableContext::Setup(entity, GetVisibilityType(instance));
		_data.gfx_id[instance] = entity;
		return entity;
	}

	void GraphicsComponent::OnActivate(InstanceId instance)
	{
		const Entities::GameEntityId owner = GetOwner(instance);
		if (Components::HasComponent<TransformComponent>(owner))
			_data.transform_id[instance] = Components::GetComponent<TransformComponent>(owner);
		else n_warning("OnActivate [%u]: Graphics component requires valid transform component\n", instance);
	}

}