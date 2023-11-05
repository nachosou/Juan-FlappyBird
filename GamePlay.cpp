#include "GamePlay.h"

#include "raylib.h"

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



static void LoadGame(Player& player, Wall* walls)
{
	gamePlayBacground = LoadTexture("Assets/Images/background.png");

	crash = LoadSound("Assets/Sounds/crash.wav");

	pauseButton = LoadTexture("Assets/Images/Menu/pauseBtn.png");
	pauseButtonAct = LoadTexture("Assets/Images/Menu/pauseBtnAct.png");

	pauseButtonPos.x = screenWidth - pauseButton.width - 15.0f;
	pauseButtonPos.y = 15.0f;

	LoadPlayer(player);
	LoadWalls(walls);
}

static void GetInput(Player& player, GameSceen& currentSceen)
{
	GetPlayerInput(player, currentSceen);
}

static void Update(Player& player, Wall* walls)
{
	UpdatePlayer(player);

	UpdateWalls(walls);
}

static void Draw(Player& player, Wall* walls)
{
	DrawTextureEx(gamePlayBacground, { 0,0 }, 0, 1.0, WHITE);

	DrawPlayer(player);

	DrawWalls(walls);
}

static void Loop(Player& player, Wall* walls, GameSceen& currentSceen)
{
	GetInput(player, currentSceen);

	Update(player, walls);

	Draw(player, walls);
}

void PlayGame(Player& player, Wall* walls, GameSceen& currentSceen)
{
	if (player.isLoading)
	{
		LoadGame(player, walls);

		player.isLoading = false;
	}

	Loop(player, walls, currentSceen);
}