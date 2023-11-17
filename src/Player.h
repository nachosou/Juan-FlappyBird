#pragma once

#include "GameData.h"


struct Player
{
	Vector2 position{};
	Vector2 speed{};
	float maxSpeed = 150.0f;
	float gravity = 0.5f;
	float jumpForce = -200.0f;
	int availableLives{};
	int totalPoints{};
	bool isAlive{};
	bool isJumping = false;
	int frame = 0;
	float lastFrame = 0;
	bool isLoading = true;

	int thousandCounter{};
	Sound thousand{};

	Texture2D texture{};
	Texture2D jumpingTexture{};
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