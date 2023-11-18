#pragma once

#include "Player.h"
#include "Wall.h"
#include "ParallaxLayer.h"

void PlayGame(Player& player, Wall& topWall, Wall& bottomWall, ParallaxLayer layers[], GameSceen& currentSceen);

void DrawGame(Player& player, Wall& topWall, Wall& bottomWall, ParallaxLayer layers[]);

void resetStats(Player& player, Wall& topWall, Wall& bottomWall);