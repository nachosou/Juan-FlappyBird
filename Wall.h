#pragma once

#include "raylib.h"

struct Wall
{
	Vector2 position;
	Vector2 speed;
	Texture2D texture{};
	Rectangle source{};
	bool isAlive = false;

	Vector2 GetCenter()
	{
		return { position.x + (texture.width / 2), position.y + (texture.height / 2) };
	}
};

void LoadWalls(Wall* walls);
void UpdateWalls(Wall* walls);
void DrawWalls(Wall* walls);