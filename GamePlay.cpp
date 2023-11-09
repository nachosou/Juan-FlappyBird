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

static bool PlayerCollidesWall(Player& player, Wall* walls)
{
	int pointsQnty = 100;
	float dxP1 = 0;
	float dyP1 = 0; 
	float x;
	float y;
	float hick1;
	float hick2;
	float hypotenuse;


	for (int i = 0; i < totalWalls; i++)
	{
		int distance = abs(static_cast<int>(walls[i].position.x - player.position.x));

		if (distance < player.texture.width + walls[i].texture.width)
		{
			dyP1 = walls[i].texture.height / static_cast<float>(pointsQnty);
			//std::cout << "entra" << std::endl;

			for (int j = 0; j <= pointsQnty; ++j)
			{
				x = walls[i].position.x + j * dxP1;
				y = walls[i].position.y + j * dyP1;

				hick1 = static_cast<float>(fabs(x - player.position.x - player.texture.width / 2));
				hick2 = static_cast<float>(fabs(y - player.position.y - player.texture.height / 2));

				hypotenuse = static_cast<float>(sqrt((hick1 * hick1) + (hick2 * hick2)));

				if (hypotenuse <= player.texture.width / 2.0f)
				{
					std::cout << "true" << std::endl;
					return true;
				}
			}
		}
	}

	return false;
}

static void CheckCollisions(Player& player, Wall* walls)
{
	if (PlayerCollidesWall(player, walls))
	{
		for (int i = 0; i < totalWalls; i++)
		{
			walls[i].speed.x = 5;
		}
	}
}

static void GetInput(Player& player, GameSceen& currentSceen)
{
	GetPlayerInput(player, currentSceen);
}

static void Update(Player& player, Wall* walls)
{
	UpdatePlayer(player);

	UpdateWalls(walls);

	CheckCollisions(player, walls);
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