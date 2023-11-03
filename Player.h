#pragma once

#include "GameData.h"


struct Player
{
	Vector2 position{};
	Vector2 speed{};
	int availableLives{};
	int totalPoints{};
	bool isAlive{};
	bool isLoading = true;

	int thousandCounter;
	Sound thousand;

	Texture2D texture{};
	Rectangle source{};

	Vector2 GetCenter()
	{
		return { position.x + (texture.width / 2), position.y + (texture.height / 2) };
	}
};

void LoadPlayer(Player& player);

void GetPlayerInput(Player& player, GameSceen& currentSceen);

void UpdatePlayer(Player& player);

void DrawPlayer(Player& player);