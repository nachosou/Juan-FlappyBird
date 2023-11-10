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
};

void LoadParallaxLayers(ParallaxLayer layers[]);

void MoveLayers(ParallaxLayer layers[]);

void DrawLayers(ParallaxLayer layers[]);