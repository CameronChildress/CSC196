#include "Player.h"
#include "Math/Math.h"
#include <fstream>

namespace nc
{
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
		nc::Vector2 force;
		if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * m_thrust; }
		force = nc::Vector2::Rotate(force, m_transform.angle);
		force += nc::Vector2{ 0, 100 };

		m_velocity += (force * dt);
		m_velocity *= 0.99f;

		m_transform.position = m_transform.position + (m_velocity * dt);

		//rotate
		if (Core::Input::IsPressed('A')) { m_transform.angle -= (nc::DegreesToRadians(m_rotationRate) * dt); }
		if (Core::Input::IsPressed('D')) { m_transform.angle += (nc::DegreesToRadians(m_rotationRate) * dt); }

		if (m_transform.position.x > 800) m_transform.position.x = 0;
		if (m_transform.position.x < 0) m_transform.position.x = 800;
		if (m_transform.position.y > 600) m_transform.position.y = 0;
		if (m_transform.position.y < 0) m_transform.position.y = 600;

	}

	void Player::Draw(Core::Graphics& graphics)
	{
		m_shape.Draw(graphics, m_transform);
	}

}