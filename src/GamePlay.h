#pragma once

#include "Player.h"
#include "Wall.h"
#include "ParallaxLayer.h"

void singlePlayerGame(Player& player, Wall& topWall, Wall& bottomWall, ParallaxLayer layers[], GameSceen& currentSceen);

void twoPlayerGame(Player& firstPlayer, Player& secondPlayer, Wall& topWall, Wall& bottomWall, ParallaxLayer layers[], GameSceen& currentSceen);

void DrawGame(Player& player, Wall& topWall, Wall& bottomWall, ParallaxLayer layers[]);
void DrawGame(Player& player, Player& secondPlayer, Wall& topWall, Wall& bottomWall, ParallaxLayer layers[]);

void drawTwoPlayersGame(Player& player, Player& secondPlayer, Wall& topWall, Wall& bottomWall, ParallaxLayer layers[]);

void resetStats(Player& player, Wall& topWall, Wall& bottomWall);

void resetTwoPlayersStats(Player& firstPlayer, Player& secondPlayer, Wall& topWall, Wall& bottomWall);