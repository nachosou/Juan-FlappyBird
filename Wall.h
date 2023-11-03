#pragma once

#include "raylib.h"

struct Wall
{
	Vector2 position;
	Vector2 speed;
	Texture2D texture{};
	Rectangle source{};
};