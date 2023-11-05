#include "Player.h"

#include "raylib.h"
#include "raymath.h"

#include <iostream>


using namespace Globals;


void LoadPlayer(Player& player)
{
    player.texture = LoadTexture("Assets/Images/ship.png");
    player.position.x = screenCenter.x - player.texture.width / 2;
    player.position.y = screenCenter.y - player.texture.height / 2;
    player.source = { 0, 0, static_cast<float>(player.texture.width), static_cast<float>(player.texture.height) };
    player.totalPoints = 0;
    player.thousandCounter = 0;
    player.availableLives = 3;

    //player.shoot = LoadSound("Assets/Sounds/shoot.wav");
    player.thousand = LoadSound("Assets/Sounds/crash.wav");
}

static void MovePlayer(Player& player)
{
    player.position.x += player.speed.x * GetFrameTime();
    player.position.y += player.speed.y * GetFrameTime();

    if (player.position.x + (player.texture.width / 2.0f) > screenWidth)
    {
        player.position.x = screenWidth - (player.texture.width / 2.0f);
    }
    else if (player.position.x - (player.texture.width / 2.0f) < 0.0f)
    {
        player.position.x = (player.texture.width / 2.0f);
    }
    else if (player.position.y + (player.texture.height / 2.0f) > screenHeight)
    {
        player.position.y = screenHeight - (player.texture.height / 2.0f);
    }
    else if (player.position.y - (player.texture.height / 2.0f) < 0.0f)
    {
        player.position.y = (player.texture.height / 2.0f);
    }
}

void GetPlayerInput(Player& player, GameSceen& currentSceen)
{
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
    {
        player.speed.y = player.maxSpeed;
    }
    else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        player.speed.y = -player.maxSpeed;
    }
    else
    {
        player.speed.y = 0.0f;
    }

    if (IsKeyDown(KEY_ESCAPE))
    {
        currentSceen = GameSceen::EXIT;
    }
}

void UpdatePlayer(Player& player)
{
    if (player.totalPoints >= player.thousandCounter + 1000)
    {
        PlaySound(player.thousand);

        player.thousandCounter += 1000;
    }

    MovePlayer(player);
}

void DrawPlayer(Player& player)
{
    Rectangle dest = { player.GetCenter().x, player.GetCenter().y, static_cast<float>(player.texture.width), static_cast<float>(player.texture.height) };
    Vector2 origin = { static_cast<float>(player.texture.width / 2), static_cast<float>(player.texture.height / 2) };

    DrawTexturePro(player.texture, player.source, dest, origin, 0.0f, RAYWHITE);
}