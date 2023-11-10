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

	layers[0].dest = { layers[0].GetCenter().x, layers[0].GetCenter().y, static_cast<float>(layers[0].texture.width), static_cast<float>(layers[0].texture.height) };
	layers[0].origin = { static_cast<float>(layers[0].texture.width / 2), static_cast<float>(layers[0].texture.height / 2) };
	layers[0].source = { 0, 0, static_cast<float>(layers[0].texture.width), static_cast<float>(layers[0].texture.height) };
	layers[1].dest = { layers[1].GetCenter().x, layers[1].GetCenter().y, static_cast<float>(layers[1].texture.width), static_cast<float>(layers[1].texture.height) };
	layers[1].origin = { static_cast<float>(layers[1].texture.width / 2), static_cast<float>(layers[1].texture.height / 2) };
	layers[1].source = { 0, 0, static_cast<float>(layers[1].texture.width), static_cast<float>(layers[1].texture.height) };
	layers[2].dest = { layers[2].GetCenter().x, layers[2].GetCenter().y, static_cast<float>(layers[2].texture.width), static_cast<float>(layers[2].texture.height) };
	layers[2].origin = { static_cast<float>(layers[2].texture.width / 2), static_cast<float>(layers[2].texture.height / 2) };
	layers[2].source = { 0, 0, static_cast<float>(layers[2].texture.width), static_cast<float>(layers[2].texture.height) };
	layers[3].dest = { layers[3].GetCenter().x, layers[3].GetCenter().y, static_cast<float>(layers[3].texture.width), static_cast<float>(layers[3].texture.height) };
	layers[3].origin = { static_cast<float>(layers[3].texture.width / 2), static_cast<float>(layers[3].texture.height / 2) };
	layers[3].source = { 0, 0, static_cast<float>(layers[3].texture.width), static_cast<float>(layers[3].texture.height) };
	layers[4].dest = { layers[4].GetCenter().x, layers[4].GetCenter().y, static_cast<float>(layers[4].texture.width), static_cast<float>(layers[4].texture.height) };
	layers[4].origin = { static_cast<float>(layers[4].texture.width / 2), static_cast<float>(layers[4].texture.height / 2) };
	layers[4].source = { 0, 0, static_cast<float>(layers[4].texture.width), static_cast<float>(layers[4].texture.height) };


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
		layers[i].dest = { layers[i].GetCenter().x, layers[i].GetCenter().y, static_cast<float>(layers[i].texture.width), static_cast<float>(layers[i].texture.height) };
		layers[i].origin = { static_cast<float>(layers[i].texture.width / 2), static_cast<float>(layers[i].texture.height / 2) };

		DrawTexturePro(layers[i].texture, layers[i].source, layers[i].dest, layers[i].origin, 0.0f, RAYWHITE);
	}
}