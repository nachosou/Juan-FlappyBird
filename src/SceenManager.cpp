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
	Music gamePlayMusic;
	Music menuMusic;

	srand(static_cast<unsigned>(time(NULL)));

	SetConfigFlags(FLAG_MSAA_4X_HINT);

	InitWindow(screenWidth, screenHeight, "Interstellar Incursion");

	InitAudioDevice();

	gamePlayMusic = LoadMusicStream("Assets/Sounds/gameMusic.wav");
	menuMusic = LoadMusicStream("Assets/Sounds/menuMusic.wav");

	SetMusicVolume(menuMusic, 0.3f);
	SetMusicVolume(gamePlayMusic, 0.3f);

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
			StopMusicStream(gamePlayMusic);

			PlayMusicStream(menuMusic);
			UpdateMusicStream(menuMusic);

			resetTwoPlayersStats(player, secondPlayer, topWall, bottomWall);
			ShowMenu(currentSceen, gameMode);
			break;
		}
		case GameSceen::SINGLE_PLAYER_GAME:
		{
			StopMusicStream(menuMusic);

			PlayMusicStream(gamePlayMusic);
			UpdateMusicStream(gamePlayMusic);

			singlePlayerGame(player, topWall, bottomWall, layers, currentSceen, MAROON);
			break;
		}
		case GameSceen::TWO_PLAYER_GAME:
		{
			StopMusicStream(menuMusic);

			PlayMusicStream(gamePlayMusic);
			UpdateMusicStream(gamePlayMusic);

			twoPlayerGame(player, secondPlayer, topWall, bottomWall, layers, currentSceen, MAROON);
			break;
		}
		case GameSceen::GAMEMODE:
		{
			UpdateMusicStream(menuMusic);
			showGameMode(currentSceen, gameMode);
			break;
		}
		case GameSceen::PAUSE:
		{
			StopMusicStream(gamePlayMusic);

			PlayMusicStream(menuMusic);
			UpdateMusicStream(menuMusic);

			PauseGame(player, secondPlayer, topWall, bottomWall, layers, currentSceen, gameMode, MAROON);
			break;
		}
		case GameSceen::INSTRUCTIONS:
		{
			UpdateMusicStream(menuMusic);
			ShowInstructions(currentSceen, gameMode);
			break;
		}
		case GameSceen::CREDITS:
		{
			UpdateMusicStream(menuMusic);
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
			StopMusicStream(gamePlayMusic);

			PlayMusicStream(menuMusic);
			UpdateMusicStream(menuMusic);

			resetStats(player, topWall, bottomWall);
			resetTwoPlayersStats(player, secondPlayer, topWall, bottomWall);
			loseScreen(player, currentSceen, gameMode);
			break;
		}
		}
		
		EndDrawing();
		
	}
}