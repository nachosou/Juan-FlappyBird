#include "SceenManager.h"

#include <iostream>

#include "GameData.h"
#include "Player.h"
#include "MenuManager.h"
#include "GamePlay.h"

using namespace Globals;


void RunGame()
{
	GameSceen currentSceen = GameSceen::GAME;

	Player player;

	srand(static_cast<unsigned>(time(NULL)));

	SetConfigFlags(FLAG_MSAA_4X_HINT);

	InitWindow(screenWidth, screenHeight, "Flappy-Birds");

	InitAudioDevice();

	InitMenu();

	//PlayMusicStream(menuMusic);

	while (currentSceen != GameSceen::EXIT)
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		switch (currentSceen)
		{
		case GameSceen::MENU:
		{
			//ShowMenu(currentSceen);
			break;
		}
		case GameSceen::GAME:
		{
			PlayGame(player, currentSceen);
			break;
		}
		case GameSceen::RESULTS:
		{
			//ShowResults(player, currentSceen);
			break;
		}
		case GameSceen::PAUSE:
		{
			//PauseGame(player, asteroids, halfAsteroids, quarterAsteroids, currentSceen);
			break;
		}
		case GameSceen::INSTRUCTIONS:
		{
			//ShowInstructions(currentSceen);
			break;
		}
		case GameSceen::CREDITS:
		{
			//ShowCredits(currentSceen);
			break;
		}
		case GameSceen::EXIT:
		{
			CloseWindow();

			break;
		}
		}

		EndDrawing();
	}
}