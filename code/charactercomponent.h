#pragma once

#include "componentbase.h"
#include "componentmanager.h"
#include "core/refcounted.h"
#include "core/singleton.h"
#include "util/stringatom.h"
#include "graphics/graphicsentity.h"
#include "visibility/visibility.h"
#include "graphicscomponent.h"

namespace Components
{
	class CharacterComponent : public ComponentBase
	{
		__DeclareClass(CharacterComponent)
		__DeclareSingleton(CharacterComponent)

	public:
		CharacterComponent() { __ConstructSingleton; }
		~CharacterComponent() { __DestructSingleton; }

		void InitializeDefault() override;

		Graphics::GraphicsEntityId Setup(InstanceId instance);

		void OnActivate(InstanceId instance) override;

		[[nodiscard]] Util::String GetSkeletonUri(const InstanceId idx) const { return _data.skel_uri[idx]; }
		void SetSkeletonUri(const InstanceId idx, const Util::String& uri) { _data.skel_uri[idx] = uri; }

		[[nodiscard]] Util::String GetAnimationUri(const InstanceId idx) const { return _data.anim_uri[idx]; }
		void SetAnimationUri(const InstanceId idx, const Util::String& uri) { _data.anim_uri[idx] = uri; }

		[[nodiscard]] Util::StringAtom GetTag(const InstanceId idx) const { return _data.tag[idx]; }
		void SetTag(const InstanceId idx, const Util::StringAtom tag) { _data.tag[idx] = tag; }

	private:
		struct GraphicsData
		{
			Util::Array<Util::String> skel_uri;
			Util::Array<Util::String> anim_uri;
			Util::Array<Util::StringAtom> tag;
			Util::Array<InstanceId> graphics_id;
		} _data;
	};

	inline CharacterComponent* Characters()
	{
		return CharacterComponent::Instance();
	}
}
