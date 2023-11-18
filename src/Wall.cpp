#include "Wall.h"
#include "GameData.h"

using namespace Globals;

void initWalls(Wall& topWall, Wall& bottomWall)
{
	topWall.position.x = static_cast<float>(screenWidth);
	topWall.position.y = 0;
	topWall.speed = 600;
	topWall.width = 40;
	topWall.height = static_cast<int>(GetRandomValue(100, 500));
	topWall.coolDown = 0;

	bottomWall.position.x = static_cast<float>(screenWidth);
	bottomWall.height = screenHeight - topWall.height - bottomWall.sepparation;
	bottomWall.position.y = static_cast<float>(screenHeight - bottomWall.height);
	bottomWall.speed = 600;
	bottomWall.width = 40;
	bottomWall.coolDown = 0;
}

static void MoveWalls(Wall& topWall, Wall& bottomWall, Player& player)
{
	topWall.coolDown += GetFrameTime();

	if (topWall.coolDown > 1)
	{
		topWall.position.x -= topWall.speed * GetFrameTime();
		bottomWall.position.x -= bottomWall.speed * GetFrameTime();
	}

	if (topWall.position.x < 0 - topWall.width)
	{
		topWall.position.x = static_cast<float>(screenWidth);
		topWall.coolDown = 0;
		topWall.height = static_cast<int>(GetRandomValue(100, 500));
		bottomWall.position.x = static_cast<float>(screenWidth);
		bottomWall.height = static_cast<int>(screenHeight - topWall.height - bottomWall.sepparation);
		bottomWall.position.y = static_cast<float>(screenHeight - bottomWall.height);
		player.totalPoints += 10;
	}
}

void UpdateWalls(Wall& topWall, Wall& bottomWall, Player& player)
{
	MoveWalls(topWall, bottomWall, player);
}

void DrawWalls(Wall topWall, Wall bottomWall)
{
	DrawRectangle(static_cast<int>(topWall.position.x), static_cast<int>(topWall.position.y), topWall.width, topWall.height, GREEN);
	DrawRectangle(static_cast<int>(bottomWall.position.x), static_cast<int>(bottomWall.position.y), bottomWall.width, bottomWall.height, GREEN);
}