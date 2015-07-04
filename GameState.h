#pragma once
#include "Entity.h"
#include <stdlib.h>
#include <cstring>
#include "DataBase.h"

enum GameState {gs_MENU, gs_PLAY, gs_VICTORY, gs_OVER, gs_SCORE, gs_PAUSE, gs_EXIT};
GameState ecurrentState;
bool running = true;
char name[6];

void Playgame(float dt)
{
	//ScoreData temp;
	//temp.score = Entity::m_time;

	switch (ecurrentState) // is this mean the ecurrentState will be switching?
	{
	case gs_MENU:
		g_AssetManager.Draw("gamebackground", iScreenWidth / 2.2, iScreenHeight / 1.6);
		DrawString("Start (Press G)", iScreenWidth * 0.35f, iScreenHeight * 0.15f);
		if (IsKeyDown('G')) // if G button is down game start
		{
			ecurrentState = gs_PLAY;
			Entity::Reset(); // reset everything on the screen

			for (int i = 0; i < 49; ++i) // create new enemies
				new Enemy(62 * (i % 7) + 51, 504 + 48 * (i / 7));
		}
		DrawString("Score (Press H)", iScreenWidth * 0.35f, iScreenHeight * 0.11f);
		if (IsKeyDown('H')) // if H button is down go to Score case
			ecurrentState = gs_SCORE;
		DrawString("Exit (Press E)", iScreenWidth * 0.37f, iScreenHeight * 0.07f);
		if (IsKeyDown('E')) // if E button is down Exit out the game
			ecurrentState = gs_EXIT;
		break;

	case gs_PLAY:
		if (Entity::IsOver() == false && Entity::Won() == false) // if game havent over and the enemies havent kill all
		{
			g_AssetManager.Draw("background", iScreenWidth / 2, iScreenHeight / 2);
			Entity::Drawall();         // Update and draw everything, this is where the game start
			Entity::Updateall(dt);
		}

		else if (Entity::IsOver()) // if its over which mean one of the enemies reach the point they cross over the line "Game Over" go to case Over
		{
			ecurrentState = gs_OVER;
			ScoreDB::AddScore(Entity::m_time, "Player");
		}
		else // else the player kill all the enemies "Victory" which mean they won go to case Victory
		{
			//std::cin.getline(name, 6);
			ecurrentState = gs_VICTORY;
			ScoreDB::AddScore(Entity::m_time, "Player");
		}

		if (IsKeyDown('P')) // if P button is down the game pause go to Pause case
			ecurrentState = gs_PAUSE;
		break;

	case gs_PAUSE:
		DrawString("Main menu", iScreenWidth * 0.39f, iScreenHeight * 0.63f);
		DrawString("Resume", iScreenWidth * 0.42f, iScreenHeight * 0.59f);
		DrawString("Exit", iScreenWidth * 0.45f, iScreenHeight * 0.55f);

		if (IsKeyDown('M')) // if M button is down go to Menu case
			ecurrentState = gs_MENU;
		if (IsKeyDown('R')) // if R button is down resume the game
			ecurrentState = gs_PLAY;
		if (IsKeyDown('E')) // if E button is down exit game
			ecurrentState = gs_EXIT;
		break;

	case gs_OVER:
		DrawString("Game Over", iScreenWidth * 0.39f, iScreenHeight * 0.63f);
		DrawString("Play Again? (Press G)", iScreenWidth * 0.3f, iScreenHeight * 0.58f);
		DrawString("Your Best Time: ", iScreenWidth * 0.33f, iScreenHeight * 0.53f);
		Entity::DrawScore(iScreenWidth * 0.64f, iScreenHeight * 0.53f);
		DrawString("Back to (M)enu....", iScreenWidth * 0.1, iScreenHeight * 0.1);

		if (IsKeyDown('G')) // if G buttons is down game start
		{
			ecurrentState = gs_PLAY;
			Entity::Reset();
			for (int i = 0; i < 49; ++i)
				new Enemy(62 * (i % 7) + 51, 504 + 48 * (i / 7));
		}

		if (IsKeyDown('M')) // if M button is down go to Menu
		{ ecurrentState = gs_MENU; }
		break;

	case gs_VICTORY:
		g_AssetManager.Draw("vicbackground", iScreenWidth / 2, iScreenHeight / 2.3);
		DrawString("Victory!!", iScreenWidth * 0.38, iScreenHeight * 0.92);
		DrawString("Back to (M)enu....", iScreenWidth * 0.1, iScreenHeight * 0.1);
		DrawString("Your Best Time: ", iScreenWidth * 0.29f, iScreenHeight * 0.87f);
		Entity::DrawScore(iScreenWidth * 0.61f, iScreenHeight * 0.87f);
		DrawString("Exit", iScreenWidth * 0.43f, iScreenHeight * 0.82f);
		std::cin >> name;
		if (IsKeyDown('M')) // if M button is down go to Menu
		{ ecurrentState = gs_MENU; }
		
		if (IsKeyDown('E')) // if E button is down exit game
		{ ecurrentState = gs_EXIT; }
		break;

	case gs_SCORE:
		ScoreBuffer::sort();
		if (IsKeyDown('M')) ecurrentState = gs_MENU; // if M button is down go to Menu
		DrawString("(M)enu", 0, iScreenHeight);
		DrawString("Best Time Ever:", iScreenWidth * 0.36, iScreenHeight - 100);
		ScoreDB::DrawScores();
		break;

	case gs_EXIT: running = false;  break;
	}
}