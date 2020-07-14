#pragma once

#include "Object/Actor.h"

namespace nc
{
	class Enemy : public nc::Actor
	{
	public:
		virtual bool Load(const std::string& filename) override;
		virtual void Update(float dt) override;
		virtual void Draw(Core::Graphics& graphics) override;

		void SetTarget(Actor* actor) { m_target = actor; }

	protected:
		float m_thrust{ 0.0f };
		Actor* m_target{ nullptr };
	};
}