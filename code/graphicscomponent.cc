#include "foundation/stdneb.h"
#include "graphicscomponent.h"
#include "transformcomponent.h"

namespace Components
{
	__ImplementClass(Components::GraphicsComponent, 'GFXC', Components::ComponentBase)
	__ImplementSingleton(Components::GraphicsComponent)

	Graphics::GraphicsEntityId GraphicsComponent::Setup(InstanceId instance)
	{
		const auto entity = Graphics::CreateEntity();
		Graphics::RegisterEntity<Models::ModelContext, Visibility::ObservableContext>(entity);
		Models::ModelContext::Setup(entity, GetResourceUri(instance), GetTag(instance));
		const auto trans = Transforms()->GetWorldTransform(_data.transform_id[instance]);
		Models::ModelContext::SetTransform(entity, trans);
		Visibility::ObservableContext::Setup(entity, GetVisibilityType(instance));
		_data.gfx_id[instance] = entity;
		return entity;
	}

	void GraphicsComponent::AppendDefault()
	{
		_data.uri.Append(Util::String(""));
		_data.tag.Append(Util::StringAtom("Empty"));
		_data.transform_id.Append(0);
		_data.gfx_id.Append(0);
		_data.visibility_type.Append(Visibility::VisibilityEntityType::Model);
	}

	void GraphicsComponent::RemovePack(InstanceId rm, InstanceId last)
	{
		_data.gfx_id[rm] = _data.gfx_id[last];
		_data.tag[rm] = _data.tag[last];
		_data.transform_id[rm] = _data.transform_id[last];
		_data.uri[rm] = _data.uri[last];
		_data.visibility_type[rm] = _data.visibility_type[last];
	}

	void GraphicsComponent::OnActivate(InstanceId instance)
	{
		const Entities::GameEntityId owner = GetOwner(instance);
		//n_assert(Components::HasComponent<TransformComponent>(owner), "OnActivate: Graphics component requires valid transform component\n");
		_data.transform_id[instance] = Components::GetComponent<TransformComponent>(owner);
	}

	void GraphicsComponent::OnDeactivate(InstanceId instance)
	{
		Graphics::DeregisterEntity<Models::ModelContext, Visibility::ObservableContext>(_data.gfx_id[instance]);
	}

	void GraphicsComponent::OnBeginFrame()
	{
		for (int i = 0; i < Count(); i++)
		{
			const auto gfx_id = _data.gfx_id[i];
			const auto trf_id = _data.transform_id[i];
			auto trans = Transforms()->GetWorldTransform(trf_id);
			Models::ModelContext::SetTransform(gfx_id, trans);
		}
	}
}
