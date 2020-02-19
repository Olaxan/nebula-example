#pragma once

#include "componentbase.h"
#include "componentmanager.h"
#include "core/refcounted.h"
#include "core/singleton.h"

namespace Components
{
	class GraphicsComponent : public ComponentBase
	{
		__DeclareClass(GraphicsComponent)
		__DeclareSingleton(GraphicsComponent)
		
	public:
		GraphicsComponent() { __ConstructSingleton; }
		~GraphicsComponent() { __DestructSingleton; }

		void InitializeDefault() override;

		Graphics::GraphicsEntityId Setup(InstanceId instance);
		
		void OnActivate(InstanceId instance) override;

		[[nodiscard]] Util::String GetResourceUri(const InstanceId idx) const { return _data.uri[idx]; }
		void SetResourceUri(const InstanceId idx, const Util::String& uri) { _data.uri[idx] = uri; }

		[[nodiscard]] Util::StringAtom GetTag(const InstanceId idx) const { return _data.tag[idx]; }
		void SetTag(const InstanceId idx, const Util::StringAtom tag) { _data.tag[idx] = tag; }

		[[nodiscard]] Visibility::VisibilityEntityType GetVisibilityType(const InstanceId idx) const { return _data.visibility_type[idx]; }
		void SetVisibilityType(const InstanceId idx, const Visibility::VisibilityEntityType type) { _data.visibility_type[idx] = type; }

		[[nodiscard]] Graphics::GraphicsEntityId GetRenderId(const InstanceId idx) const { return _data.gfx_id[idx]; }

	private:
		struct GraphicsData
		{
			Util::ArrayStack<Util::String, 128> uri;
			Util::ArrayStack<Util::StringAtom, 128> tag;
			Util::ArrayStack<InstanceId, 128> transform_id;
			Util::ArrayStack<Graphics::GraphicsEntityId, 128> gfx_id;
			Util::ArrayStack<Visibility::VisibilityEntityType, 128> visibility_type;
		} _data;
	};

	inline GraphicsComponent* Graphics()
	{
		return GraphicsComponent::Instance();
	}
}