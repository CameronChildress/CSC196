// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "core.h"
#include "Math/Math.h"
//#include "Math/Vector2.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include "Math/Transform.h"
#include "Graphics/Shape.h"
#include "Object/Actor.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include <iostream>
#include <string>

//float thrust{ 300 };

nc::Player player;
nc::Enemy enemy;

//nc::Vector2 velocity;

//nc::Transform transform{ {400, 300}, 4.0f, 0.0f };

float t{ 0 };

float frametime;
float roundTime{ 0 };
bool gameOver{ false };

DWORD prevTime;
DWORD deltaTime;

bool Update(float dt) //dt -> delta time (60 fps) (1 / 60 = 0.016)
{
    DWORD time = GetTickCount();
    deltaTime = time - prevTime; // current frame time - previous frame time
    prevTime = time;

    t += dt * 5.0f;

    frametime = dt;
    roundTime += dt;

    if (roundTime >= 5.0f) gameOver = true;

    if(gameOver) dt *= 0.25f;;

    bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

    int x, y;
    Core::Input::GetMousePos(x, y);

    player.Update(dt);
    enemy.Update(dt);

    //transform.position = nc::Clamp(transform.position, { 0,0 }, { 800,600 });

    

    //translate
    /*if (Core::Input::IsPressed('A')) { position += nc::Vector2::left * speed * dt; }
    if (Core::Input::IsPressed('D')) { position += nc::Vector2::right * speed * dt; }
    if (Core::Input::IsPressed('W')) { position += nc::Vector2::up * speed * dt; }
    if (Core::Input::IsPressed('S')) { position += nc::Vector2::down * speed * dt; }*/

    return quit; 
}


void Draw(Core::Graphics& graphics)
{
    graphics.DrawString(10, 10, std::to_string(frametime).c_str());
    graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str());
    graphics.DrawString(10, 30, std::to_string(deltaTime / 1000.0f).c_str());

    float v = (std::sin(t) + 1.0f) * 0.5f;

    nc::Color c = nc::Lerp(nc::Color{ 0, 1, 0 }, nc::Color{ 1, 0, 0 }, v);
    graphics.SetColor(c);

    nc::Vector2 p = nc::Lerp(nc::Vector2{ 400, 300 }, nc::Vector2{ 400, 100 }, v);
    graphics.DrawString(p.x, p.y, "Last Starfighter");

    if (gameOver) graphics.DrawString(400, 300, "Game Over");

    //ship.Draw(graphics, transform);

    player.Draw(graphics);
    enemy.Draw(graphics);
}

int main()
{
    DWORD ticks = GetTickCount(); //how many ticks in a second
    std::cout << ticks / 1000 / 60 / 60 << std::endl;
    prevTime = GetTickCount();

    //ship.Load("ship.txt");
    player.Load("player.txt");
    enemy.Load("enemy.txt");

    enemy.SetTarget(&player);
    //ship.SetColor(nc::Color{ 0, 1, 0 });

    char name[] = "ChildressC"; 
    Core::Init(name, 800, 600);
    Core::RegisterUpdateFn(Update);
    Core::RegisterDrawFn(Draw);

    Core::GameLoop(); 
    Core::Shutdown();
}
