#include "Player.h"
#include "Projectile.h"
#include "Object/Scene.h"
#include "Math/Math.h"
#include "Graphics/ParticleSystem.h"
#include "Object/Scene.h"
#include "../Game.h"
#include <fstream>

bool Player::Load(const std::string& filename)
{
	bool success = false;
	std::ifstream stream(filename);

	if (stream.is_open())
	{
		success = true;

		// load the base actor members            
		Actor::Load(stream);

		stream >> m_thrust;
		stream >> m_rotationRate;

		stream.close();
	}

	return success;
}

void Player::Update(float dt)
{
	m_fireTimer += dt;

	if (Core::Input::IsPressed(VK_SPACE) && m_fireTimer >= m_fireRate)
	{
		m_fireTimer = 0.0f;
		Projectile* projectile = new Projectile;
		projectile->Load("projectile.txt");
		projectile->GetTransform().position = m_transform.position;
		projectile->GetTransform().angle = m_transform.angle;
		m_scene->AddActor(projectile);
	}

	nc::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * m_thrust; }
	force = nc::Vector2::Rotate(force, m_transform.angle);

	m_velocity += (force * dt);
	m_velocity *= 0.99f;

	m_transform.position = m_transform.position + (m_velocity * dt);

	//rotate
	if (Core::Input::IsPressed('A')) { m_transform.angle -= (nc::DegreesToRadians(m_rotationRate) * dt); }
	if (Core::Input::IsPressed('D')) { m_transform.angle += (nc::DegreesToRadians(m_rotationRate) * dt); }

	/*if (m_transform.position.x > 800) m_transform.position.x = 0;
	if (m_transform.position.x < 0) m_transform.position.x = 800;
	if (m_transform.position.y > 600) m_transform.position.y = 0;
	if (m_transform.position.y < 0) m_transform.position.y = 600;*/

	m_transform.position = nc::Clamp(m_transform.position, {0, 0}, {800, 600});

	if (force.LengthSqr() > 0)
	{
		g_particleSystem.Create(m_transform.position, m_transform.angle + nc::PI, 20, 1, nc::Color::yellow, 1, 100, 200);
	}

	m_transform.Update();

}

void Player::Draw(Core::Graphics& graphics)
{
	m_shape.Draw(graphics, m_transform);
}

void Player::OnCollision(Actor* actor)
{
	if (actor->GetType() == eType::ENEMY)
	{
		m_scene->GetGame()->SetState(Game::eState::GAME_OVER);
	}
}
