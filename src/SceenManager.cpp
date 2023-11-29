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
	GameSceen gameMode = GameSceen::SINGLE_PLAYER_GAME;
	ParallaxLayer* layers = new ParallaxLayer[layersQnty];

	Player player;
	Player secondPlayer;
	Wall topWall;
	Wall bottomWall;

	srand(static_cast<unsigned>(time(NULL)));

	SetConfigFlags(FLAG_MSAA_4X_HINT);

	InitWindow(screenWidth, screenHeight, "Flappy-Birds");

	InitAudioDevice();

	InitMenu(player);

	LoadPlayer(player);
	LoadTwoPlayer(secondPlayer);

	while (currentSceen != GameSceen::EXIT)
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		switch (currentSceen)
		{
		case GameSceen::MENU:
		{
			resetTwoPlayersStats(player, secondPlayer, topWall, bottomWall);
			ShowMenu(currentSceen, gameMode);
			break;
		}
		case GameSceen::SINGLE_PLAYER_GAME:
		{
			singlePlayerGame(player, topWall, bottomWall, layers, currentSceen);
			break;
		}
		case GameSceen::TWO_PLAYER_GAME:
		{
			twoPlayerGame(player, secondPlayer, topWall, bottomWall, layers, currentSceen);
			break;
		}
		case GameSceen::GAMEMODE:
		{
			showGameMode(currentSceen, gameMode);
			break;
		}
		case GameSceen::RESULTS:
		{
			ShowResults(player, currentSceen, gameMode);
			break;
		}
		case GameSceen::PAUSE:
		{
			PauseGame(player, secondPlayer, topWall, bottomWall, layers, currentSceen, gameMode);
			break;
		}
		case GameSceen::INSTRUCTIONS:
		{
			ShowInstructions(currentSceen, gameMode);
			break;
		}
		case GameSceen::CREDITS:
		{
			ShowCredits(currentSceen, gameMode);
			break;
		}
		case GameSceen::EXIT:
		{
			CloseWindow();

			break;
		}
		case GameSceen::LOSE:
		{
			resetTwoPlayersStats(player, secondPlayer, topWall, bottomWall);
			loseScreen(player, currentSceen, gameMode);
			break;
		}
		}
		
		EndDrawing();
		
	}
}