#include "Projectile.h"
#include "Math/Math.h"
#include "Graphics/ParticleSystem.h"
#include <fstream>

bool Projectile::Load(const std::string& filename)
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

void Projectile::Update(float dt)
{
    m_lifetime -= dt;
    m_destroy = (m_lifetime <= 0);

    nc::Vector2 direction = nc::Vector2::Rotate(nc::Vector2::forward, m_transform.angle);
    nc::Vector2 enemyVelocity = direction * m_thrust;
    m_transform.position += (enemyVelocity * dt);

    g_particleSystem.Create(m_transform.position, m_transform.angle + nc::PI, 20, 1, nc::Color::white, 1, 100, 200);

    m_transform.Update();
}

void Projectile::Draw(Core::Graphics& graphics)
{
    m_shape.Draw(graphics, m_transform);
}

void Projectile::OnCollision(Actor* actor)
{
    if (actor->GetType() == eType::ENEMY)
    {
        m_destroy = true;
    }
}
