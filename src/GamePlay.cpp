#include "GamePlay.h"

#include <iostream>

#include "raylib.h"
#include "raymath.h"

#include "GameData.h"

namespace Assets
{
	extern Sound crash{};

	extern Texture2D gamePlayBacground{};
	extern Texture2D pauseButton{};
	extern Texture2D pauseButtonAct{};

	extern Vector2 pauseButtonPos{};
}

using namespace Assets;
using namespace Globals;

static void LoadGame(ParallaxLayer layers[], Wall& topWall, Wall& bottomWall)
{
	gamePlayBacground = LoadTexture("Assets/Images/background.png");

	crash = LoadSound("Assets/Sounds/crash.wav");

	pauseButton = LoadTexture("Assets/Images/Menu/pauseBtn.png");
	pauseButtonAct = LoadTexture("Assets/Images/Menu/pauseBtnAct.png");

	pauseButtonPos.x = screenWidth - pauseButton.width - 15.0f;
	pauseButtonPos.y = 15.0f;

	initWalls(topWall, bottomWall);
	LoadParallaxLayers(layers);
}

static void loadTwoPlayersGame(ParallaxLayer layers[], Wall& topWall, Wall& bottomWall)
{
	gamePlayBacground = LoadTexture("Assets/Images/background.png");

	crash = LoadSound("Assets/Sounds/crash.wav");

	pauseButton = LoadTexture("Assets/Images/Menu/pauseBtn.png");
	pauseButtonAct = LoadTexture("Assets/Images/Menu/pauseBtnAct.png");

	pauseButtonPos.x = screenWidth - pauseButton.width - 15.0f;
	pauseButtonPos.y = 15.0f;

	initWalls(topWall, bottomWall);
	LoadParallaxLayers(layers);
}

static bool CheckCollisions(Player player, Wall walls)
{
	if (player.position.x + player.texture.width >= walls.position.x &&
		player.position.x <= walls.position.x + walls.width &&
		player.position.y + player.texture.height >= walls.position.y &&
		player.position.y <= walls.position.y + walls.height)
	{
		return true;
	}
	return false;
}

void resetStats(Player& player, Wall& topWall, Wall& bottomWall)
{
	player.position.x = 100;
	player.position.y = screenCenter.y - player.texture.height / 2;
	player.speed = { 0, 0 };
	player.totalPoints = 0;

	topWall.position.x = static_cast<float>(screenWidth);
	topWall.position.y = 0;
	topWall.speed = 600;
	topWall.width = 40;
	topWall.height = static_cast<int>(GetRandomValue(100, 500));
	topWall.coolDown = 0;

	bottomWall.position.x = static_cast<float>(screenWidth);
	bottomWall.height = screenHeight - topWall.height - topWall.sepparation;
	bottomWall.position.y = static_cast<float>(screenHeight - bottomWall.height);
	bottomWall.speed = 600;
	bottomWall.width = 40;
	bottomWall.coolDown = 0;
}

void resetTwoPlayersStats(Player& firstPlayer, Player& secondPlayer, Wall& topWall, Wall& bottomWall)
{
	firstPlayer.position.x = 100;
	firstPlayer.position.y = screenCenter.y - firstPlayer.texture.height / 2;
	firstPlayer.speed = { 0, 0 };
	firstPlayer.totalPoints = 0;

	secondPlayer.position.x = 100;
	secondPlayer.position.y = screenCenter.y - 100;
	secondPlayer.speed = { 0, 0 };

	topWall.position.x = static_cast<float>(screenWidth);
	topWall.position.y = 0;
	topWall.speed = 600;
	topWall.width = 40;
	topWall.height = static_cast<int>(GetRandomValue(100, 500));
	topWall.coolDown = 0;

	bottomWall.position.x = static_cast<float>(screenWidth);
	bottomWall.height = screenHeight - topWall.height - topWall.sepparation;
	bottomWall.position.y = static_cast<float>(screenHeight - bottomWall.height);
	bottomWall.speed = 600;
	bottomWall.width = 40;
	bottomWall.coolDown = 0;
}

static void playerCollitionWithWalls(Player& player, Wall& topWall, Wall& bottomWall)
{
	if (CheckCollisions(player, topWall) || CheckCollisions(player, bottomWall))
	{
		resetStats(player, topWall, bottomWall);
	}
}

static void twoPlayersCollitionWithWalls(Player& firstPlayer, Player& secondPlayer, Wall& topWall, Wall& bottomWall)
{
	if (CheckCollisions(firstPlayer, topWall) || CheckCollisions(firstPlayer, bottomWall))
	{
		resetStats(firstPlayer, topWall, bottomWall);
		resetStats(secondPlayer, topWall, bottomWall);
	}

	if (CheckCollisions(secondPlayer, topWall) || CheckCollisions(secondPlayer, bottomWall))
	{
		resetStats(firstPlayer, topWall, bottomWall);
		resetStats(secondPlayer, topWall, bottomWall);
	}
}

static void checkWindowCollition(Player& player, Wall& topWall, Wall& bottomWall)
{
	if (player.position.y <= 0)
	{
		player.jumpForce = 0.0f;
		player.position.y = 0;
	}
	else
	{
		player.jumpForce = -400.0f;
	}

	if (player.position.y >= screenHeight + player.height)
	{
		resetStats(player, topWall, bottomWall);
	}
}

static void checkTwoPlayersWindowCollition(Player& firstPlayer, Player& secondPlayer, Wall& topWall, Wall& bottomWall)
{
	if (firstPlayer.position.y <= 0)
	{
		firstPlayer.jumpForce = 0.0f;
		firstPlayer.position.y = 0;
	}
	else
	{
		firstPlayer.jumpForce = -400.0f;
	}

	if (firstPlayer.position.y >= screenHeight + firstPlayer.height)
	{
		resetStats(firstPlayer, topWall, bottomWall);
		resetStats(secondPlayer, topWall, bottomWall);
	}

	if (secondPlayer.position.y <= 0)
	{
		secondPlayer.jumpForce = 0.0f;
		secondPlayer.position.y = 0;
	}
	else
	{
		secondPlayer.jumpForce = -400.0f;
	}

	if (secondPlayer.position.y >= screenHeight + secondPlayer.height)
	{
		resetStats(firstPlayer, topWall, bottomWall);
		resetStats(secondPlayer, topWall, bottomWall);
	}
}

static void GetInput(GameSceen& currentSceen)
{
	GetPlayerInput(currentSceen);
}

static void Update(Player& player, Wall& topWall, Wall& bottomWall, ParallaxLayer layers[])
{
	UpdatePlayer(player);

	UpdateWalls(topWall, bottomWall, player);

	playerCollitionWithWalls(player, topWall, bottomWall);

	checkWindowCollition(player, topWall, bottomWall);

	MoveLayers(layers);
}

static void twoPlayersUpdate(Player& firstPlayer, Player& secondPlayer, Wall& topWall, Wall& bottomWall, ParallaxLayer layers[])
{
	UpdatePlayer(firstPlayer);

	UpdateTwoPlayers(secondPlayer);

	UpdateWalls(topWall, bottomWall, firstPlayer);

	twoPlayersCollitionWithWalls(firstPlayer, secondPlayer, topWall, bottomWall);

	checkTwoPlayersWindowCollition(firstPlayer, secondPlayer, topWall, bottomWall);

	MoveLayers(layers);
}

void DrawGame(Player& player, Wall& topWall, Wall& bottomWall, ParallaxLayer layers[])
{
	DrawLayers(layers);

	DrawPlayer(player);

	DrawWalls(topWall, bottomWall);

	DrawText(TextFormat("%01i", player.totalPoints), 20, 20, 40, WHITE);
}

void drawTwoPlayersGame(Player& player, Player& secondPlayer,  Wall& topWall, Wall& bottomWall, ParallaxLayer layers[])
{
	DrawLayers(layers);

	DrawPlayer(player);

	DrawTwoPlayer(secondPlayer);

	DrawWalls(topWall, bottomWall);

	DrawText(TextFormat("%01i", player.totalPoints), 20, 20, 40, WHITE);
}

static void Loop(Player& player, Wall& topWall, Wall& bottomWall, ParallaxLayer layers[], GameSceen& currentSceen)
{
	GetInput(currentSceen);

	Update(player, topWall, bottomWall, layers);

	DrawGame(player, topWall, bottomWall, layers);
}

static void twoPlayersLoop(Player& firstPlayer, Player& secondPlayer, Wall& topWall, Wall& bottomWall, ParallaxLayer layers[], GameSceen& currentSceen)
{
	GetInput(currentSceen);

	twoPlayersUpdate(firstPlayer, secondPlayer, topWall, bottomWall, layers);

	drawTwoPlayersGame(firstPlayer, secondPlayer, topWall, bottomWall, layers);
}

void singlePlayerGame(Player& player, Wall& topWall, Wall& bottomWall, ParallaxLayer layers[], GameSceen& currentSceen)
{
	if (player.isLoading)
	{
		LoadGame(layers, topWall, bottomWall);

		player.isLoading = false;
	}

	Loop(player, topWall, bottomWall, layers, currentSceen);
}

void twoPlayerGame(Player& firstPlayer, Player& secondPlayer, Wall& topWall, Wall& bottomWall, ParallaxLayer layers[], GameSceen& currentSceen)
{
	if (firstPlayer.isLoading)
	{
		loadTwoPlayersGame(layers, topWall, bottomWall);

		firstPlayer.isLoading = false;
	}

	twoPlayersLoop(firstPlayer, secondPlayer, topWall, bottomWall, layers, currentSceen);
}