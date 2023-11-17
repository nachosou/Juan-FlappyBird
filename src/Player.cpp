#include "Player.h"

#include "raylib.h"
#include "raymath.h"

#include <iostream>

using namespace Globals;

void LoadPlayer(Player& player)
{
    player.texture = LoadTexture("Assets/Images/ship.png");
    player.position.x = 100;
    player.position.y = screenCenter.y - player.texture.height / 2;
    player.totalPoints = 0;
    player.thousandCounter = 0;
    player.availableLives = 3;
    player.width = 60;
    player.height = 60;

    player.thousand = LoadSound("Assets/Sounds/crash.wav");
}

static void MovePlayer(Player& player)
{
    if (IsKeyPressed(KEY_SPACE) && player.position.y > 0)
    {
        player.speed.y = player.jumpForce;
        player.isJumping = true;
    }

    player.speed.y += player.gravity * GetFrameTime();
    player.position.y += player.speed.y * GetFrameTime();

    if (player.isJumping && player.speed.y > 0)
    {
        player.isJumping = false;
    }
}

void GetPlayerInput(GameSceen& currentSceen)
{
    if (IsKeyDown(KEY_ESCAPE))
    {
        currentSceen = GameSceen::PAUSE;
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
    
    player.source = { 0, 0, static_cast<float>(player.texture.width), static_cast<float>(player.texture.height) };
    DrawTexturePro(player.texture, player.source, dest, origin, 0.0f, RAYWHITE);
}