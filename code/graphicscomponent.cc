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
		n_printf("New graphics object id is %i, owner is %i\n", entity, GetOwner(instance));
		return entity;
	}

	void GraphicsComponent::AppendDefault()
	{
		_data.gfx_id.Append(0);
		_data.res_uri.Append(Util::String(""));
		_data.tag.Append(Util::StringAtom("Empty"));
		_data.visibility_type.Append(Visibility::VisibilityEntityType::Model);
	}

	void GraphicsComponent::EraseInstance(const InstanceId instance)
	{
		_data.gfx_id.EraseIndexSwap(instance);
		_data.tag.EraseIndexSwap(instance);
		_data.res_uri.EraseIndexSwap(instance);
		_data.visibility_type.EraseIndexSwap(instance);
	}

	void GraphicsComponent::OnLoad(InstanceId instance)
	{
		Setup(instance);
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

	Util::Variant::Type GraphicsComponent::GetTypeByName(Util::String data)
	{
		if (data == "res_uri")
			return Util::Variant::Type::String;

		if (data == "tag")
			return Util::Variant::Type::String;

		if (data == "gfx_id")
			return Util::Variant::Type::Int;

		if (data == "visibility_type")
			return Util::Variant::Type::Int;


		return Util::Variant::Type::Void;
	}

	bool GraphicsComponent::SetDataByName(InstanceId instance, Util::String data, Util::Variant value)
	{
		if (data == "res_uri")
		{
			_data.res_uri[instance] = value.GetString();
			return true;
		}

		if (data == "tag")
		{
			_data.tag[instance] = value.GetString();
			return true;
		}

		if (data == "gfx_id")
		{
			n_warning("Graphics ID should not be manually changed.");
			_data.gfx_id[instance] = value.GetInt();
			return true;
		}

		if (data == "visibility_type")
		{
			_data.visibility_type[instance] = static_cast<Visibility::VisibilityEntityType>(value.GetInt());
			return true;
		}

		return false;
	}
}
