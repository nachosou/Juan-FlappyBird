#pragma once

#include "raylib.h"

#include "GameData.h"
#include "ParallaxLayer.h"
#include "Player.h"
#include "Wall.h"

namespace Assets
{
	extern Texture2D background;
	extern Texture2D smallContainer;
	extern Texture2D mediumContainer;
	extern Texture2D largeContainer;
	extern Texture2D play;
	extern Texture2D instructions;
	extern Texture2D credits;
	extern Texture2D exit;

	extern Texture2D bigWindow;
	extern Texture2D smallWindow;
	extern Texture2D backButton;
	extern Texture2D backButtonAct;
	extern Texture2D menuButton;
	extern Texture2D menuButtonAct;
	extern Texture2D exitButton;
	extern Texture2D exitButtonAct;

	extern Sound click;
	extern Sound clickPressed;

	extern Vector2 playPos;
	extern Vector2 instructionsPos;
	extern Vector2 creditsPos;
	extern Vector2 exitPos;
	extern Vector2 versionPos;
	extern Vector2 singlePlayerPosition;
	extern Vector2 twoPlayersPosition;

	extern Vector2 bigWindowPos;
	extern Vector2 smallWindowPos;
	extern Vector2 backButtonPos;
	extern Vector2 menuButtonPos;
	extern Vector2 exitButtonPos;
	extern Vector2 gitHubPos;
	extern Vector2 gitHubSize;

	extern bool isClicking;
}


void InitMenu();
void ShowMenu(GameSceen& currentSceen, GameSceen& gameMode);
void ShowInstructions(GameSceen& currentSceen, GameSceen& gameMode);
void ShowCredits(GameSceen& currentSceen, GameSceen& gameMode);
void PauseGame(Player player, Wall& topWall, Wall& bottomWall, ParallaxLayer layers[], GameSceen& currentSceen, GameSceen gameMode);
void ShowResults(Player& player, GameSceen& currentSceen, GameSceen& gameMode);
void showGameMode(GameSceen& currentSceen, GameSceen& gameMode);

