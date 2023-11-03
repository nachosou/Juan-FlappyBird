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



static void LoadGame(Player& player)
{
	gamePlayBacground = LoadTexture("Assets/Images/background.png");

	crash = LoadSound("Assets/Sounds/crash.wav");

	pauseButton = LoadTexture("Assets/Images/Menu/pauseBtn.png");
	pauseButtonAct = LoadTexture("Assets/Images/Menu/pauseBtnAct.png");

	pauseButtonPos.x = screenWidth - pauseButton.width - 15.0f;
	pauseButtonPos.y = 15.0f;

	LoadPlayer(player);
}

static void GetInput(Player& player, GameSceen& currentSceen)
{
	GetPlayerInput(player, currentSceen);
}

static void Update(Player& player)
{
	UpdatePlayer(player);
}

static void Draw(Player& player)
{
	DrawTextureEx(gamePlayBacground, { 0,0 }, 0, 1.0, WHITE);

	DrawPlayer(player);
}

static void Loop(Player& player, GameSceen& currentSceen)
{
	GetInput(player, currentSceen);

	Update(player);

	Draw(player);
}

void PlayGame(Player& player, GameSceen& currentSceen)
{
	if (player.isLoading)
	{
		LoadGame(player);

		player.isLoading = false;
	}

	Loop(player, currentSceen);
}