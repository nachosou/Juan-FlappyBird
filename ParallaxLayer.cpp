#include "ParallaxLayer.h"

namespace Parallax
{
	int layersQnty = 2;
}

using namespace Parallax;

void LoadParallaxLayers(ParallaxLayer layers[])
{
	layers[0].texture = LoadTexture("Assets/Images/Menu/background.png");
}

void MoveLayers(ParallaxLayer layers[])
{
	for (int i = 0; i < layersQnty; i++)
	{
		layers[i].position.x -= layers[i].speed * GetFrameTime();
	}
}

void DrawLayers(ParallaxLayer layers[])
{
	for (int i = 0; i < layersQnty; i++)
	{
		DrawTextureV(layers[i].texture, layers[i].position, WHITE);
	}
}