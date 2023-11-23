#include "Player.h"

#include "raylib.h"
#include "raymath.h"

#include <iostream>

using namespace Globals;

void LoadPlayer(Player& player)
{
    player.texture = LoadTexture("Assets/Images/ship.png");
    player.jumpingTexture = LoadTexture("Assets/Images/jumpingShip.png");
    player.position.x = 100;
    player.position.y = screenCenter.y - player.texture.height / 2;
    player.totalPoints = 0;
    player.thousandCounter = 0;
    player.availableLives = 3;
    player.width = 60;
    player.height = 60;
    player.totalPoints = 0;

    player.thousand = LoadSound("Assets/Sounds/crash.wav");
}

void LoadTwoPlayer(Player& secondPlayer)
{
    secondPlayer.texture = LoadTexture("Assets/Images/playerTwoShip.png");
    secondPlayer.jumpingTexture = LoadTexture("Assets/Images/playerTwoJumpingShip.png");
    secondPlayer.position.x = 100;
    secondPlayer.position.y = screenCenter.y - 100;
    secondPlayer.totalPoints = 0;
    secondPlayer.thousandCounter = 0;
    secondPlayer.availableLives = 3;
    secondPlayer.width = 60;
    secondPlayer.height = 60;
    secondPlayer.totalPoints = 0;

    secondPlayer.thousand = LoadSound("Assets/Sounds/crash.wav");
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

static void MoveTwoPlayers(Player& secondPlayer)
{
    if (IsKeyPressed(KEY_UP) && secondPlayer.position.y > 0)
    {
        secondPlayer.speed.y = secondPlayer.jumpForce;
        secondPlayer.isJumping = true;
    }

    secondPlayer.speed.y += secondPlayer.gravity * GetFrameTime();
    secondPlayer.position.y += secondPlayer.speed.y * GetFrameTime();

    if (secondPlayer.isJumping && secondPlayer.speed.y > 0)
    {
        secondPlayer.isJumping = false;
    }
}

static Texture2D changeTexture(Player& player)
{
    if (player.isJumping == true)
    {
        return player.jumpingTexture;
    }
    else
    {
        return player.texture;
    }
}

static Texture2D changeSecondPlayerTexture(Player& secondPlayer)
{
    if (secondPlayer.isJumping == true)
    {
        return secondPlayer.jumpingTexture;
    }
    else
    {
        return secondPlayer.texture;
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

void UpdateTwoPlayers(Player& secondPlayer)
{
    if (secondPlayer.totalPoints >= secondPlayer.thousandCounter + 1000)
    {
        PlaySound(secondPlayer.thousand);

        secondPlayer.thousandCounter += 1000;
    }

    MoveTwoPlayers(secondPlayer);
}

void DrawPlayer(Player& player)
{
    Rectangle dest = { player.GetCenter().x, player.GetCenter().y, static_cast<float>(player.texture.width), static_cast<float>(player.texture.height) };
    Vector2 origin = { static_cast<float>(player.texture.width / 2), static_cast<float>(player.texture.height / 2) };
    
    player.source = { 0, 0, static_cast<float>(player.texture.width), static_cast<float>(player.texture.height) };
    DrawTexturePro(changeTexture(player), player.source, dest, origin, 0.0f, RAYWHITE);
}

void DrawTwoPlayer(Player& secondPlayer)
{
    Rectangle dest2 = { secondPlayer.GetCenter().x, secondPlayer.GetCenter().y, static_cast<float>(secondPlayer.texture.width), static_cast<float>(secondPlayer.texture.height) };
    Vector2 origin2 = { static_cast<float>(secondPlayer.texture.width / 2), static_cast<float>(secondPlayer.texture.height / 2) };

    secondPlayer.source = { 0, 0, static_cast<float>(secondPlayer.texture.width), static_cast<float>(secondPlayer.texture.height) };
    DrawTexturePro(changeSecondPlayerTexture(secondPlayer), secondPlayer.source, dest2, origin2, 0.0f, RAYWHITE);
}