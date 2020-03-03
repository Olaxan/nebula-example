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
		Visibility::ObservableContext::Setup(entity, GetVisibilityType(instance));
		_data.gfx_id[instance] = entity;
		n_printf("New graphics object id is %i\n", entity);
		return entity;
	}

	void GraphicsComponent::AppendDefault()
	{
		_data.gfx_id.Append(0);
		_data.uri.Append(Util::String(""));
		_data.tag.Append(Util::StringAtom("Empty"));
		_data.visibility_type.Append(Visibility::VisibilityEntityType::Model);
	}

	void GraphicsComponent::EraseInstance(const InstanceId instance)
	{
		_data.gfx_id.EraseIndexSwap(instance);
		_data.tag.EraseIndexSwap(instance);
		_data.uri.EraseIndexSwap(instance);
		_data.visibility_type.EraseIndexSwap(instance);
	}

	void GraphicsComponent::OnDeactivate(InstanceId instance)
	{
		n_printf("De-registering instance %i, gfx %i from model, observable\n", instance, _data.gfx_id[instance]);
		Graphics::DeregisterEntity<Models::ModelContext, Visibility::ObservableContext>(_data.gfx_id[instance]);
	}

	void GraphicsComponent::OnBeginFrame()
	{
		for (int i = 0; i < Count(); i++)
		{
			const Entities::GameEntityId owner = GetOwner(i);
			n_assert2(Components::HasComponent<TransformComponent>(owner), "OnBeginFrame: Graphics component requires valid transform component\n");
			const auto trf_id = Components::GetComponent<TransformComponent>(owner);
			const auto gfx_id = _data.gfx_id[i];
			
			auto trans = Transforms()->GetWorldTransform(trf_id);
			Models::ModelContext::SetTransform(gfx_id, trans);
		}
	}
}
