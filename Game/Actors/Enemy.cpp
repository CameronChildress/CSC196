#include "Enemy.h"
#include "Math/Math.h"
#include "Graphics/ParticleSystem.h"
#include "Object/Scene.h"
#include "../Game.h"
#include <fstream>

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
    nc::Vector2 enemyVelocity = direction.Normalized() * m_thrust;
    m_transform.position += (enemyVelocity * dt);
    m_transform.angle = std::atan2(direction.y, direction.x) + nc::DegreesToRadians(90.0f);

    m_transform.Update();
}

void Enemy::Draw(Core::Graphics& graphics)
{
    m_shape.Draw(graphics, m_transform);
}

void Enemy::OnCollision(Actor* actor)
{
    if (actor->GetType() == eType::PROJECTILE)
    {
        m_destroy = true;

        //set Game Score
        m_scene->GetGame()->AddPoints(100);

        nc::Color colors[] = { nc::Color::white, nc::Color::blue, nc::Color::yellow };
        nc::Color color = colors[rand() % 3]; //0, 1, 2

        g_particleSystem.Create(m_transform.position, 0, 180, 30, color, 1, 100, 200);
    }
}
