#include "Wall.h"

#include "GameData.h"


using namespace Globals;

void LoadWalls(Wall* walls)
{
    for (int i = 0; i < totalWalls; i++)
    {
        walls[i].texture = LoadTexture("Assets/Images/wall.png");
        walls[i].position.x = static_cast<float>(screenWidth);
        walls[i].position.y = static_cast<float>(GetRandomValue(0, screenHeight - walls[i].texture.height));
        walls[i].source = { 0, 0, static_cast<float>(walls[i].texture.width), static_cast<float>(walls[i].texture.height) };
        walls[i].speed.x = 50.0f;
    }
}

static void MoveWalls(Wall* walls)
{
    for (int i = 0; i < totalWalls; i++)
    {
        if (walls[i].isAlive)
        {
            walls[i].position.x -= walls[i].speed.x * GetFrameTime();

            if (walls[i].position.x + (walls[i].texture.width / 2.0f) < 0.0f)
            {
                walls[i].position.x = static_cast<float>(screenWidth);
            }
            else if (walls[i].position.y + (walls[i].texture.height / 2.0f) > screenHeight)
            {
                walls[i].position.y = screenHeight - (walls[i].texture.height / 2.0f);
            }
            else if (walls[i].position.y - (walls[i].texture.height / 2.0f) < 0.0f)
            {
                walls[i].position.y = (walls[i].texture.height / 2.0f);
            }
        }
    }  
}

static void GenerateWalls(Wall* walls)
{
    double elapsedTime = GetTime();

    if (elapsedTime > lastWall + 4.0f)
    {
        for (int i = 0; i < totalWalls; i++)
        {
            if (!walls[i].isAlive)
            {
                walls[i].isAlive = true;
                lastWall = GetTime();

                if (i == 0)
                {
                    if (walls[totalWalls - 1].GetCenter().y < screenHeight / 2.0f)
                    {
                        walls[i].position.y = static_cast<float>(GetRandomValue(static_cast<int>(walls[totalWalls - 1].GetCenter().y), static_cast<int>(walls[totalWalls - 1].position.y + walls[totalWalls - 1].texture.height)));
                    }
                    else
                    {
                        walls[i].position.y = static_cast<float>(GetRandomValue(static_cast<int>(walls[totalWalls - 1].GetCenter().y), static_cast<int>(walls[totalWalls - 1].position.y - walls[totalWalls - 1].texture.height)));
                    }
                }
                else
                {
                    if (walls[i - 1].GetCenter().y < screenHeight / 2.0f)
                    {
                        walls[i].position.y = static_cast<float>(GetRandomValue(static_cast<int>(walls[i - 1].GetCenter().y), static_cast<int>(walls[i - 1].position.y + walls[i - 1].texture.height)));
                    }
                    else
                    {
                        walls[i].position.y = static_cast<float>(GetRandomValue(static_cast<int>(walls[i - 1].GetCenter().y), static_cast<int>(walls[i - 1].position.y - walls[i - 1].texture.height)));
                    }
                }

                break;
            }
        }
    }
}

void UpdateWalls(Wall* walls)
{
    GenerateWalls(walls);
    
    MoveWalls(walls);
}

void DrawWalls(Wall* walls)
{
    for (int i = 0; i < totalWalls; i++)
    {
        if (walls[i].isAlive)
        {
            Rectangle dest = { walls[i].GetCenter().x, walls[i].GetCenter().y, static_cast<float>(walls[i].texture.width), static_cast<float>(walls[i].texture.height) };
            Vector2 origin = { static_cast<float>(walls[i].texture.width / 2), static_cast<float>(walls[i].texture.height / 2) };

            DrawTexturePro(walls[i].texture, walls[i].source, dest, origin, 0.0f, RAYWHITE);
        }
    }
}