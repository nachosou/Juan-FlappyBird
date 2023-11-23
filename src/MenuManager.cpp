#include "MenuManager.h"

#include <iostream>

#include "GamePlay.h"

namespace Assets
{
	extern Texture2D background{};
	extern Texture2D smallContainer{};
	extern Texture2D mediumContainer{};
	extern Texture2D largeContainer{};
	extern Texture2D play{};
	extern Texture2D playSelect{};
	extern Texture2D instructions{};
	extern Texture2D credits{};
	extern Texture2D exit{};

	extern Texture2D bigWindow{};
	extern Texture2D smallWindow{};
	extern Texture2D backButton{};
	extern Texture2D backButtonAct{};
	extern Texture2D menuButton{};
	extern Texture2D menuButtonAct{};
	extern Texture2D exitButton{};
	extern Texture2D exitButtonAct{};
	extern Texture2D resumeButton{};
	extern Texture2D resumeButtonAct{};

	extern Sound click{};
	extern Sound clickPressed{};

	extern Vector2 playPos{};
	extern Vector2 playPosContainer{};
	extern Vector2 instructionsPos{};
	extern Vector2 instructionsPosContainer{};
	extern Vector2 creditsPos{};
	extern Vector2 creditsPosContainer{};
	extern Vector2 exitPos{};
	extern Vector2 exitPosContainer{};
	extern Vector2 bigWindowPos{};
	extern Vector2 smallWindowPos{};
	extern Vector2 backButtonPos{};
	extern Vector2 menuButtonPos{};
	extern Vector2 exitButtonPos{};
	extern Vector2 versionPos{};
	extern Vector2 singlePlayerPosition{};
	extern Vector2 twoPlayersPosition{};
	
	extern Vector2 gitHubPos{};
	extern Vector2 gitHubSize{};
	extern Vector2 itchioPos{};
	extern Vector2 itchioSize{};

	extern bool isClicking = false;
}

using namespace Assets;
using namespace Globals;

void InitMenu()
{
	background = LoadTexture("Assets/Images/Menu/background.png");
	smallContainer = LoadTexture("Assets/Images/Menu/smallContainer.png");
	mediumContainer = LoadTexture("Assets/Images/Menu/mediumContainer.png");
	largeContainer = LoadTexture("Assets/Images/Menu/largeContainer.png");

	bigWindow = LoadTexture("Assets/Images/Menu/bigWindow.png");
	smallWindow = LoadTexture("Assets/Images/Menu/smallWindow.png");
	backButton = LoadTexture("Assets/Images/Menu/backBtn.png");
	backButtonAct = LoadTexture("Assets/Images/Menu/backBtnAct.png");
	menuButton = LoadTexture("Assets/Images/Menu/menuBtn.png");
	menuButtonAct = LoadTexture("Assets/Images/Menu/menuBtnAct.png");
	exitButton = LoadTexture("Assets/Images/Menu/exitBtn.png");
	exitButtonAct = LoadTexture("Assets/Images/Menu/exitBtnAct.png");
	resumeButton = LoadTexture("Assets/Images/Menu/resumeBtn.png");
	resumeButtonAct = LoadTexture("Assets/Images/Menu/resumeBtnAct.png");

	menuMusic = LoadMusicStream("Assets/Sounds/menu.wav");
	menuMusic.looping = true;

	gameLoopMusic = LoadMusicStream("Assets/Sounds/gameLoop.wav");
	gameLoopMusic.looping = true;
	SetMusicVolume(gameLoopMusic, 0.1f);

	click = LoadSound("Assets/Sounds/click.wav");
	clickPressed = LoadSound("Assets/Sounds/clickPressed.wav");

	font = LoadFont("Assets/Fonts/04B_30__.TTF");
	fontSize = font.baseSize * 2.0f;

	playPosContainer.x = (screenWidth / 2.0f) - (smallContainer.width / 2.0f);
	playPosContainer.y = ((screenHeight / 5.0f)) - (smallContainer.height / 2.0f);
	playPos.x = (screenWidth / 2.0f) - MeasureTextEx(font, "Play", fontSize, spacing).x / 2.0f + 8.0f;
	playPos.y = (screenHeight / 5.0f) - (fontSize / 2.0f);

	instructionsPosContainer.x = (screenWidth / 2.0f) - (largeContainer.width / 2.0f);
	instructionsPosContainer.y = ((screenHeight / 5.0f) * 2.0f) - (largeContainer.height / 2.0f);
	instructionsPos.x = (screenWidth / 2.0f) - MeasureTextEx(font, "Instructions", fontSize, instrucrtionsSpacing).x / 2.0f + 8.0f;
	instructionsPos.y = ((screenHeight / 5.0f) * 2.0f) - (fontSize / 2.0f);

	creditsPosContainer.x = (screenWidth / 2.0f) - (mediumContainer.width / 2.0f);
	creditsPosContainer.y = ((screenHeight / 5.0f) * 3.0f) - (mediumContainer.height / 2.0f);
	creditsPos.x = (screenWidth / 2.0f) - MeasureTextEx(font, "Credits", fontSize, spacing).x / 2.0f + 20.0f;
	creditsPos.y = ((screenHeight / 5.0f) * 3.0f) - (fontSize / 2.0f);

	exitPosContainer.x = (screenWidth / 2.0f) - (smallContainer.width / 2.0f);
	exitPosContainer.y = (screenHeight / 5.0f) * 4.0f - (smallContainer.height / 2.0f);
	exitPos.x = (screenWidth / 2.0f) - MeasureTextEx(font, "Exit", fontSize, spacing).x / 2.0f + 8.0f;
	exitPos.y = (screenHeight / 5.0f) * 4.0f -(fontSize / 2.0f);

	singlePlayerPosition.x = (screenWidth / 2 - (MeasureTextEx(font, "1 Player", fontSize, spacing).x) / 2);
	singlePlayerPosition.y = ((300) + 15);
	twoPlayersPosition.x = (screenWidth / 2 - (MeasureTextEx(font, "2 Players", fontSize, spacing).x) / 2);
	twoPlayersPosition.y = ((500) + 15);

	versionPos.y = (0 + 35.0f);
	versionPos.x = 35.0f;

	backButtonPos.x = 15.0f;
	backButtonPos.y = 15.0f;

	exitButtonPos.x = screenWidth - exitButton.width - 15.0f;
	exitButtonPos.y = 15.0f;

	menuButtonPos.x = exitButtonPos.x - (menuButton.width + 15.0f);
	menuButtonPos.y = 15.0f;
}

static void GetInput(GameSceen& currentSceen, GameSceen& gameMode)
{
	int mouseX = GetMouseX();
	int mouseY = GetMouseY();

	if (currentSceen == GameSceen::MENU)
	{
		if ((mouseX > playPosContainer.x && mouseX < playPosContainer.x + smallContainer.width) && (mouseY > playPosContainer.y && mouseY < playPosContainer.y + smallContainer.height))
		{
			DrawTextEx(font, "Play", playPos, fontSize, spacing, ORANGE);

			if (!isClicking)
			{
				isClicking = true;

				PlaySound(click);
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				PlaySound(clickPressed);
				StopMusicStream(menuMusic);
				PlayMusicStream(gameLoopMusic);
				currentSceen = GameSceen::GAMEMODE;
			}
		}
		else if ((mouseX > instructionsPosContainer.x && mouseX < instructionsPosContainer.x + largeContainer.width) && (mouseY > instructionsPosContainer.y && mouseY < instructionsPosContainer.y + largeContainer.height))
		{
			DrawTextEx(font, "Instructions", instructionsPos, fontSize, instrucrtionsSpacing, ORANGE);

			if (!isClicking)
			{
				isClicking = true;

				PlaySound(click);
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				PlaySound(clickPressed);
				currentSceen = GameSceen::INSTRUCTIONS;
			}
		}
		else if ((mouseX > creditsPosContainer.x && mouseX < creditsPosContainer.x + mediumContainer.width) && (mouseY > creditsPosContainer.y && mouseY < creditsPosContainer.y + mediumContainer.height))
		{
			DrawTextEx(font, "Credits", creditsPos, fontSize, 3, ORANGE);

			if (!isClicking)
			{
				isClicking = true;

				PlaySound(click);
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				PlaySound(clickPressed);
				currentSceen = GameSceen::CREDITS;
			}
		}
		else if ((mouseX > exitPosContainer.x && mouseX < exitPosContainer.x + smallContainer.width) && (mouseY > exitPosContainer.y && mouseY < exitPosContainer.y + smallContainer.height))
		{
			DrawTextEx(font, "Exit", exitPos, fontSize, spacing, ORANGE);

			if (!isClicking)
			{
				isClicking = true;

				PlaySound(click);
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				PlaySound(clickPressed);
				currentSceen = GameSceen::EXIT;
			}
		}
		else
		{
			isClicking = false;
		}
	}
	else if (currentSceen == GameSceen::GAMEMODE)
	{
		if (IsKeyPressed(KEY_ESCAPE))
		{
			currentSceen = GameSceen::MENU;
		}
		else if ((mouseX > backButtonPos.x && mouseX < backButtonPos.x + backButton.width) && (mouseY > backButtonPos.y && mouseY < backButtonPos.y + backButton.height))
		{
			DrawTextureV(backButtonAct, backButtonPos, WHITE);

			if (!isClicking)
			{
				isClicking = true;

				PlaySound(click);
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				PlaySound(clickPressed);
				currentSceen = GameSceen::MENU;
			}
		}
		else if ((mouseX > singlePlayerPosition.x && mouseX < singlePlayerPosition.x + largeContainer.width) && (mouseY > singlePlayerPosition.y && mouseY < singlePlayerPosition.y + largeContainer.height))
		{
			DrawTextEx(font, "1 Player", singlePlayerPosition, fontSize, 3.0f, ORANGE);

			if (!isClicking)
			{
				isClicking = true;

				PlaySound(click);
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				PlaySound(clickPressed);
				currentSceen = GameSceen::SINGLE_PLAYER_GAME;
				gameMode = GameSceen::SINGLE_PLAYER_GAME;
			}
		}
		else if ((mouseX > twoPlayersPosition.x && mouseX < twoPlayersPosition.x + largeContainer.width) && (mouseY > twoPlayersPosition.y && mouseY < twoPlayersPosition.y + largeContainer.height))
		{
			DrawTextEx(font, "2 Players", twoPlayersPosition, fontSize, 3.0f, ORANGE);

			if (!isClicking)
			{
				isClicking = true;

				PlaySound(click);
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				PlaySound(clickPressed);
				currentSceen = GameSceen::TWO_PLAYER_GAME;
				gameMode = GameSceen::TWO_PLAYER_GAME;
			}
		}
	}
	else
	{
		if (IsKeyPressed(KEY_ESCAPE))
		{
			currentSceen = GameSceen::MENU;
		}
		else if ((mouseX > backButtonPos.x && mouseX < backButtonPos.x + backButton.width) && (mouseY > backButtonPos.y && mouseY < backButtonPos.y + backButton.height))
		{
			DrawTextureV(backButtonAct, backButtonPos, WHITE);

			if (!isClicking)
			{
				isClicking = true;

				PlaySound(click);
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				PlaySound(clickPressed);
				currentSceen = GameSceen::MENU;
			}
		}
		else if (currentSceen == GameSceen::CREDITS && ((mouseX > gitHubPos.x && mouseX < gitHubPos.x + gitHubSize.x) && (mouseY > gitHubPos.y && mouseY < gitHubPos.y + gitHubSize.y)))
		{		
			DrawTextEx(font, "https://nachosou.itch.io", gitHubPos, fontSize * 0.2f, spacing / 8.0f, GREEN);

			if (!isClicking)
			{
				isClicking = true;

				PlaySound(click);
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				PlaySound(clickPressed);
				OpenURL("https://nachosou.itch.io");
			}	
		}
		else if (currentSceen == GameSceen::CREDITS && ((mouseX > itchioPos.x && mouseX < itchioPos.x + itchioSize.x) && (mouseY > itchioPos.y && mouseY < itchioPos.y + itchioSize.y)))
		{
			DrawTextEx(font, "https://juandigilio.itch.io", itchioPos, fontSize * 0.2f, spacing / 8.0f, GREEN);

			if (!isClicking)
			{
				isClicking = true;

				PlaySound(click);
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				PlaySound(clickPressed);
				OpenURL("https://juandigilio.itch.io");
			}
		}
		else
		{
			isClicking = false;
		}
	}	
}

static void DrawMain()
{
	DrawTexture(background, 0, 0, WHITE);
	DrawTextureEx(smallContainer, playPosContainer, 0, 1.0, WHITE);
	DrawTextureEx(largeContainer, instructionsPosContainer, 0, 1.0, WHITE);
	DrawTextureEx(mediumContainer, creditsPosContainer, 0, 1.0, WHITE);
	DrawTextureEx(smallContainer, exitPosContainer, 0, 1.0, WHITE);

	DrawTextEx(font, "Play", playPos, fontSize, spacing, RAYWHITE);
	DrawTextEx(font, "Instructions", instructionsPos, fontSize, instrucrtionsSpacing, RAYWHITE);
	DrawTextEx(font, "Credits", creditsPos, fontSize, 3, RAYWHITE);
	DrawTextEx(font, "Exit", exitPos, fontSize, spacing, RAYWHITE);
	DrawTextEx(font, "Version 0.3", versionPos, fontSize / 4.0f, spacing, RAYWHITE);
}

void drawGameMode()
{
	DrawTexture(background, 0, 0, WHITE);
	DrawTextureV(backButton, backButtonPos, WHITE);
	DrawTextureEx(largeContainer, { static_cast<float>(screenWidth / 2 - largeContainer.width / 2),  static_cast<float>(300) }, 0, 1.0, WHITE);
	DrawTextureEx(largeContainer, { static_cast<float>(screenWidth / 2 - largeContainer.width / 2),  static_cast<float>(500) }, 0, 1.0, WHITE);
	DrawTextEx(font, "1 Player", singlePlayerPosition, fontSize, 3, RAYWHITE);
	DrawTextEx(font, "2 Players", twoPlayersPosition, fontSize, 3, RAYWHITE);
}

void showGameMode(GameSceen& currentSceen, GameSceen& gameMode)
{
	drawGameMode();

	UpdateMusicStream(menuMusic);

	GetInput(currentSceen, gameMode);
}

void ShowMenu(GameSceen& currentSceen, GameSceen& gameMode)
{
	DrawMain();

	UpdateMusicStream(menuMusic);

	GetInput(currentSceen, gameMode);
}

static void DrawInstrucions()
{
	bigWindowPos.x = (screenWidth / 2.0f) - (bigWindow.width / 2.0f);
	bigWindowPos.y = (screenHeight / 2.0f) - (bigWindow.height / 2.0f);

	Vector2 textPos;

	DrawTexture(background, 0, 0, WHITE);
	DrawTextureV(bigWindow, bigWindowPos, WHITE);
	DrawTextureV(backButton, backButtonPos, WHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "INSTRUCTIONS", fontSize * 0.85f, spacing / 2.0f).x / 2.0f;
	textPos.y = (screenHeight / 6) - fontSize + 10;
	DrawTextEx(font, "INSTRUCTIONS", textPos, fontSize * 0.85f, spacing / 2.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Player 1: Press SPACEBAR once to jump", fontSize / 4.0f, spacing / 4.0f).x / 2.0f;
	textPos.y = (screenHeight / 5) + (fontSize) - 20;
	DrawTextEx(font, "Player 1: Press SPACEBAR once to jump", textPos, fontSize / 4.0f, spacing / 4.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Player 2: Up arrow to jump", fontSize / 4.0f, spacing / 4.0f).x / 2.0f;
	textPos.y += 40;
	DrawTextEx(font, "Player 2: Up arrow to jump", textPos, fontSize / 4.0f, spacing / 4.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Dodge the pippes to get as many points you can", fontSize / 4.0f, spacing / 4.0f).x / 2.0f;
	textPos.y += 40;
	DrawTextEx(font, "Dodge the pippes to get as many points you can", textPos, fontSize / 4.0f, spacing / 4.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "and set the new record! Game will restart when you", fontSize / 4.0f, spacing / 4.0f).x / 2.0f;
	textPos.y += 40;
	DrawTextEx(font, "and set the new record! Game will restart when you", textPos, fontSize / 4.0f, spacing / 4.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "crash with a pippe", fontSize / 4.0f, spacing / 4.0f).x / 2.0f;
	textPos.y += 40;
	DrawTextEx(font, "crash with a pippe", textPos, fontSize / 4.0f, spacing / 4.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "(Press ESC to pause)", fontSize / 3.0f, spacing / 3.0f).x / 2.0f;
	textPos.y += 160;
	DrawTextEx(font, "(Press ESC to pause)", textPos, fontSize / 3.0f, spacing / 3.0f, RAYWHITE);
}

void ShowInstructions(GameSceen& currentSceen, GameSceen& gameMode)
{
	DrawInstrucions();

	UpdateMusicStream(menuMusic);

	GetInput(currentSceen, gameMode);
}

static void DrawCredits()
{
	Vector2 textPos;

	smallWindowPos.x = (screenWidth / 2.0f) - (smallWindow.width / 2.0f);
	smallWindowPos.y = (screenHeight / 2.0f) - (smallWindow.height / 2.0f) + 10.0f;

	DrawTexture(background, 0, 0, WHITE);
	DrawTextureV(smallWindow, smallWindowPos, WHITE);
	DrawTextureV(backButton, backButtonPos, WHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Created by Juan Digilio And Ignacio Gonzalez Souza", fontSize * 0.3f, spacing / 4.0f).x / 2.0f;
	textPos.y = smallWindowPos.y - 130;
	DrawTextEx(font, "Created by Juan Digilio And Ignacio Gonzalez Souza", textPos, fontSize * 0.3f, spacing / 4.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Assets creator: Ignacio Gonzalez Souza", fontSize * 0.3f, spacing / 8.0f).x / 2.0f;
	textPos.y += 55;
	DrawTextEx(font, "Assets creator: Ignacio Gonzalez Souza", textPos, fontSize * 0.3f, spacing / 8.0f, RAYWHITE);
	
	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "This is a remake of", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
	textPos.y += 90;
	DrawTextEx(font, "This is a remake of", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Flappy Bird made in raylib for my", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
	textPos.y += 20;
	DrawTextEx(font, "Flappy Bird made in raylib for my", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "coursing at Image-Campus in my first", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
	textPos.y += 20;
	DrawTextEx(font, "coursing at Image-Campus in my first", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "year of video games development.", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
	textPos.y += 20;
	DrawTextEx(font, "year of video games development.", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "The code is open source and you", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
	textPos.y += 40;
	DrawTextEx(font, "The code is open source and you", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "can find it in my GitHub", fontSize * 0.2f, spacing / 8.0f).x / 2.0f;
	textPos.y += 20;
	DrawTextEx(font, "can find it in my GitHub", textPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

	gitHubSize = MeasureTextEx(font, "https://nachosou.itch.io", fontSize * 0.2f, spacing / 8.0f);
	itchioSize = MeasureTextEx(font, "https://juandigilio.itch.io/", fontSize * 0.2f, spacing / 8.0f);

	gitHubPos.x = (screenWidth / 2) - gitHubSize.x / 2.0f;
	gitHubPos.y = textPos.y + 30;
	DrawTextEx(font, "https://nachosou.itch.io", gitHubPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);

	itchioPos.x = (screenWidth / 2) - itchioSize.x / 2.0f;
	itchioPos.y = gitHubPos.y + 20;
	DrawTextEx(font, "https://juandigilio.itch.io", itchioPos, fontSize * 0.2f, spacing / 8.0f, RAYWHITE);
}

void ShowCredits(GameSceen& currentSceen, GameSceen& gameMode)
{
	DrawCredits();

	UpdateMusicStream(menuMusic);

	GetInput(currentSceen, gameMode);
}

static void GetPausedInput(GameSceen& currentSceen, GameSceen gameMode)
{
	int mouseX = GetMouseX();
	int mouseY = GetMouseY();

	if ((mouseX > backButtonPos.x && mouseX < backButtonPos.x + backButton.width) && (mouseY > backButtonPos.y && mouseY < backButtonPos.y + backButton.height))
	{
		DrawTextureV(resumeButtonAct, backButtonPos, WHITE);

		if (!isClicking)
		{
			isClicking = true;

			PlaySound(click);
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			PlaySound(clickPressed);
			currentSceen = gameMode;
		}
	}
	else if ((mouseX > menuButtonPos.x && mouseX < menuButtonPos.x + menuButton.width) && (mouseY > menuButtonPos.y && mouseY < menuButtonPos.y + menuButton.height))
	{
		DrawTextureV(menuButtonAct, menuButtonPos, WHITE);

		if (!isClicking)
		{
			isClicking = true;

			PlaySound(click);
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			PlaySound(clickPressed);
			currentSceen = GameSceen::MENU;
			loading = true;
			StopMusicStream(gameLoopMusic);
			PlayMusicStream(menuMusic);
		}
	}
	else if ((mouseX > exitButtonPos.x && mouseX < exitButtonPos.x + exitButton.width) && (mouseY > exitButtonPos.y && mouseY < exitButtonPos.y + exitButton.height))
	{
		DrawTextureV(exitButtonAct, exitButtonPos, WHITE);

		if (!isClicking)
		{
			isClicking = true;

			PlaySound(click);
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			PlaySound(clickPressed);
			currentSceen = GameSceen::EXIT;
		}
	}
	else
	{
		isClicking = false;
	}

	if (IsKeyPressed(MOUSE_BUTTON_LEFT))
	{
		PlaySound(clickPressed);
		currentSceen = gameMode;
	}
}

void PauseGame(Player player, Player secondPlayer, Wall& topWall, Wall& bottomWall, ParallaxLayer layers[], GameSceen& currentSceen, GameSceen gameMode)
{
	if (gameMode == GameSceen::SINGLE_PLAYER_GAME)
	{
		DrawGame(player, topWall, bottomWall, layers);
	}
	else
	{
		DrawGame(player, secondPlayer, topWall, bottomWall, layers);
	}
	

	smallWindowPos.x = (screenWidth / 2.0f) - (smallWindow.width / 2.0f);
	smallWindowPos.y = (screenHeight / 2.0f) - (smallWindow.height / 2.0f);

	DrawTextureV(smallWindow, smallWindowPos, WHITE);
	DrawTextureV(resumeButton, backButtonPos, WHITE);
	DrawTextureV(menuButton, menuButtonPos, WHITE);
	DrawTextureV(exitButton, exitButtonPos, WHITE);

	Vector2 textPos;

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "PAUSED GAME", fontSize * 0.45f, spacing).x / 2.0f;
	textPos.y = smallWindowPos.y + 45.0f;
	DrawTextEx(font, "PAUSED GAME", textPos, fontSize * 0.45f, spacing, RAYWHITE);

	GetPausedInput(currentSceen, gameMode);
}

static void DrawResults(Player player)
{
	Vector2 textPos;

	smallWindowPos.x = (screenWidth / 2.0f) - (smallWindow.width / 2.0f);
	smallWindowPos.y = (screenHeight / 2.0f) - (smallWindow.height / 2.0f);

	DrawTexture(background, 0, 0, WHITE);
	DrawTextureV(smallWindow, smallWindowPos, WHITE);
	DrawTextureV(backButton, backButtonPos, WHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "RESULTS", fontSize * 0.6f, spacing / 4.0f).x / 2.0f;
	textPos.y = smallWindowPos.y + 30;
	DrawTextEx(font, "RESULTS", textPos, fontSize * 0.6f, spacing / 4.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "Your score:     ", fontSize * 0.4f, spacing / 8.0f).x / 2.0f;
	textPos.y += 75;
	DrawTextEx(font, "Your score: ", textPos, fontSize * 0.4f, spacing / 8.0f, RAYWHITE);

	textPos.x += MeasureTextEx(font, "Your score: ", fontSize * 0.4f, spacing / 8.0f).x;
	DrawTextEx(font, TextFormat("%01i", player.totalPoints), textPos, fontSize * 0.4f, spacing / 8.0f, RAYWHITE);

	textPos.x = (screenWidth / 2) - MeasureTextEx(font, "High score:     ", fontSize * 0.4f, spacing / 8.0f).x / 2.0f;
	textPos.y += 40;
	DrawTextEx(font, "High score: ", textPos, fontSize * 0.4f, spacing / 8.0f, RAYWHITE);

	textPos.x += MeasureTextEx(font, "High score: ", fontSize * 0.4f, spacing / 8.0f).x;
	DrawTextEx(font, TextFormat("%01i", highScore), textPos, fontSize * 0.4f, spacing / 8.0f, RAYWHITE);
}

void ShowResults(Player& player, GameSceen& currentSceen, GameSceen& gameMode)
{
	DrawResults(player);

	GetInput(currentSceen, gameMode);
}

