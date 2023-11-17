#include "SceenManager.h"

#include <iostream>

#include "GameData.h"
#include "ParallaxLayer.h"
#include "Player.h"
#include "Wall.h"
#include "MenuManager.h"
#include "GamePlay.h"

using namespace Globals;
using namespace Parallax;


void RunGame()
{
	GameSceen currentSceen = GameSceen::MENU;
	ParallaxLayer* layers = new ParallaxLayer[layersQnty];

	Player player;
	Wall* walls = new Wall[totalWalls];

	srand(static_cast<unsigned>(time(NULL)));

	SetConfigFlags(FLAG_MSAA_4X_HINT);

	InitWindow(screenWidth, screenHeight, "Flappy-Birds");

	InitAudioDevice();

	InitMenu();

	while (currentSceen != GameSceen::EXIT)
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		switch (currentSceen)
		{
		case GameSceen::MENU:
		{
			ShowMenu(currentSceen);
			break;
		}
		case GameSceen::GAME:
		{
			PlayGame(player, walls, layers, currentSceen);
			break;
		}
		case GameSceen::RESULTS:
		{
			ShowResults(player, currentSceen);
			break;
		}
		case GameSceen::PAUSE:
		{
			PauseGame(player, walls, layers, currentSceen);
			break;
		}
		case GameSceen::INSTRUCTIONS:
		{
			ShowInstructions(currentSceen);
			break;
		}
		case GameSceen::CREDITS:
		{
			ShowCredits(currentSceen);
			break;
		}
		case GameSceen::EXIT:
		{
			CloseWindow();

			delete[] walls;
			delete[] layers;

			break;
		}
		}

		EndDrawing();
	}
}