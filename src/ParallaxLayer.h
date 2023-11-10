#pragma once

#include "raylib.h"

namespace Parallax
{
	extern int layersQnty;
}

struct ParallaxLayer
{
	Texture texture;
	Vector2 position;
	float speed;
	Rectangle dest;
	Rectangle source;
	Vector2 origin;

	Vector2 GetCenter()
	{
		return { position.x + (texture.width / 2), position.y + (texture.height / 2) };
	}
};

void LoadParallaxLayers(ParallaxLayer layers[]);

void MoveLayers(ParallaxLayer layers[]);

void DrawLayers(ParallaxLayer layers[]);