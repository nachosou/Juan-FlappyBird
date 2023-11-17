#pragma once

#include "raylib.h"

struct Wall
{
	Vector2 position = { 0, 0 };
	int speed = 0;
	int height = 0;
	int width = 0;
	float coolDown = 0;
	int sepparation = 120;
};

void initWalls(Wall& topWall, Wall& bottomWall);
void UpdateWalls(Wall& topWall, Wall& bottomWall);
void DrawWalls(Wall topWall, Wall bottomWall);