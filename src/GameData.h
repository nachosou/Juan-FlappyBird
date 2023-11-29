#pragma once

#include "raylib.h"

enum class GameSceen
{
	MENU,
	SINGLE_PLAYER_GAME,
	TWO_PLAYER_GAME,
	GAMEMODE,
	RESULTS,
	PAUSE,
	INSTRUCTIONS,
	CREDITS,
	EXIT,
	LOSE
};

namespace Globals
{
	extern const int screenWidth;
	extern const int screenHeight;
	extern Vector2 screenCenter;

	extern float version;

	extern int totalWalls;
	extern double lastWall;

	extern Music menuMusic;
	extern Music gameLoopMusic;

	extern Font font;
	extern float fontSize;
	extern float spacing;
	extern float instrucrtionsSpacing;

	extern int highScore;
	extern bool loading;
}