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

static void LoadGame(Player& player, Wall* walls, ParallaxLayer layers[])
{
	gamePlayBacground = LoadTexture("Assets/Images/background.png");

	crash = LoadSound("Assets/Sounds/crash.wav");

	pauseButton = LoadTexture("Assets/Images/Menu/pauseBtn.png");
	pauseButtonAct = LoadTexture("Assets/Images/Menu/pauseBtnAct.png");

	pauseButtonPos.x = screenWidth - pauseButton.width - 15.0f;
	pauseButtonPos.y = 15.0f;

	LoadPlayer(player);
	LoadWalls(walls);
	LoadParallaxLayers(layers);
}

static bool PlayerCollidesWall(Player& player, Wall* walls)
{
	int pointsQnty = 100;
	float dxP1 = 0;
	float dyP1 = 0; 
	float xLeft;
	float yLeft;
	float xRight;
	float yRight;
	float hick1Left;
	float hick2Left;
	float hick1Right;
	float hick2Right;
	float hypotenuseLeft;
	float hypotenuseRight;

	float xUp;
	float yUp;
	float xDown;
	float yDown;
	float hick1Up;
	float hick2Up;
	float hick1Down;
	float hick2Down;
	float hypotenuseUp;
	float hypotenuseDown;


	for (int i = 0; i < totalWalls; i++)
	{
		int distance = abs(static_cast<int>(walls[i].position.x - player.position.x));

		if (distance < player.texture.width + walls[i].texture.width)
		{
			dyP1 = walls[i].texture.height / static_cast<float>(pointsQnty);

			for (int j = 0; j <= pointsQnty; ++j)
			{
				xLeft = walls[i].position.x + j * dxP1;
				yLeft = walls[i].position.y + j * dyP1;

				xRight = walls[i].position.x + walls[i].texture.width + j * dxP1;
				yRight = walls[i].position.y + j * dyP1;

				hick1Left = static_cast<float>(fabs(xLeft - player.position.x - player.texture.width / 2));
				hick2Left = static_cast<float>(fabs(yLeft - player.position.y - player.texture.height / 2));

				hick1Right = static_cast<float>(fabs(xRight - player.position.x - player.texture.width / 2));
				hick2Right = static_cast<float>(fabs(yRight - player.position.y - player.texture.height / 2));

				hypotenuseLeft = static_cast<float>(sqrt((hick1Left * hick1Left) + (hick2Left * hick2Left)));
				hypotenuseRight = static_cast<float>(sqrt((hick1Right * hick1Right) + (hick2Right * hick2Right)));

				if (hypotenuseLeft <= player.texture.width / 2.0f || hypotenuseRight <= player.texture.width / 2.0f)
				{
					std::cout << "true" << std::endl;
					return true;
				}
			
			}

			dyP1 = 0;
			dxP1 = walls[i].texture.width / static_cast<float>(pointsQnty);

			for (int j = 0; j <= pointsQnty; ++j)
			{
				xUp = walls[i].position.x + j * dxP1;
				yUp = walls[i].position.y + j * dyP1;

				xDown = walls[i].position.x + j * dxP1;
				yDown = walls[i].position.y + walls[i].texture.height + j * dyP1;

				hick1Up = static_cast<float>(fabs(xUp - player.position.x - player.texture.width / 2));
				hick2Up = static_cast<float>(fabs(yUp - player.position.y - player.texture.height / 2));

				hick1Down = static_cast<float>(fabs(xDown - player.position.x - player.texture.width / 2));
				hick2Down = static_cast<float>(fabs(yDown - player.position.y - player.texture.height / 2));

				hypotenuseUp = static_cast<float>(sqrt((hick1Up * hick1Up) + (hick2Up * hick2Up)));
				hypotenuseDown = static_cast<float>(sqrt((hick1Down * hick1Down) + (hick2Down * hick2Down)));

				if (hypotenuseUp <= player.texture.width / 2.0f || hypotenuseDown <= player.texture.width / 2.0f)
				{
					std::cout << "arriba/abajo" << std::endl;
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
			//walls[i].speed.x = 5;
		}
	}
}

static void GetInput(Player& player, GameSceen& currentSceen)
{
	GetPlayerInput(player, currentSceen);
}

static void Update(Player& player, Wall* walls, ParallaxLayer layers[])
{
	UpdatePlayer(player);

	UpdateWalls(walls);

	CheckCollisions(player, walls);

	MoveLayers(layers);
}

void DrawGame(Player& player, Wall* walls, ParallaxLayer layers[])
{
	DrawLayers(layers);

	DrawPlayer(player);

	DrawWalls(walls);
}

static void Loop(Player& player, Wall* walls, ParallaxLayer layers[], GameSceen& currentSceen)
{
	GetInput(player, currentSceen);

	Update(player, walls, layers);

	DrawGame(player, walls, layers);
}

void PlayGame(Player& player, Wall* walls, ParallaxLayer layers[], GameSceen& currentSceen)
{
	if (player.isLoading)
	{
		LoadGame(player, walls, layers);

		player.isLoading = false;
	}

	Loop(player, walls, layers, currentSceen);
}