#include "ParallaxLayer.h"

#include "GameData.h"

namespace Parallax
{
	extern int layersQnty = 5;
}

using namespace Parallax;
using namespace Globals;

void LoadParallaxLayers(ParallaxLayer layers[])
{
	layers[0].texture = LoadTexture("Assets/Images/Parallax/layer1.png");
	layers[1].texture = LoadTexture("Assets/Images/Parallax/layer2.png");
	layers[2].texture = LoadTexture("Assets/Images/Parallax/layer3.png");
	layers[3].texture = LoadTexture("Assets/Images/Parallax/layer4.png");
	layers[4].texture = LoadTexture("Assets/Images/Parallax/layer5.png");

	layers[0].speed = 5.0f;
	layers[1].speed = 15.0f;
	layers[2].speed = 25.0f;
	layers[3].speed = 40.0f;
	layers[4].speed = 50.0f;

	layers[0].position = {0, 0};
	layers[1].position = {0, static_cast<float>(screenHeight - (layers[1].texture.height)) };
	layers[2].position = { 0, static_cast<float>(screenHeight - (layers[2].texture.height)) };
	layers[3].position = { 0, static_cast<float>(screenHeight - (layers[3].texture.height)) };
	layers[4].position = { 0, static_cast<float>(screenHeight - (layers[4].texture.height))};
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