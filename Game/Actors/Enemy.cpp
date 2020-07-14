#include "Enemy.h"
#include "Math/Math.h"
#include <fstream>

namespace nc
{
    bool Enemy::Load(const std::string& filename)
    {
        bool success = false;

        std::ifstream stream(filename);

        if (stream.is_open())
        {
            success = true;

            // load the base actor members           
            Actor::Load(stream);

            stream >> m_thrust;

            stream.close();
        }

        return success;
    }

    void Enemy::Update(float dt)
    {
        nc::Vector2 direction = m_target->GetTransform().position - m_transform.position;
        nc::Vector2 enemyVelocity = direction.Normalized() * 100.0f;
        m_transform.position += (enemyVelocity * dt);
        m_transform.angle = std::atan2(direction.y, direction.x) + nc::DegreesToRadians(90.0f);
    }

    void Enemy::Draw(Core::Graphics& graphics)
    {
        m_shape.Draw(graphics, m_transform);
    }

}