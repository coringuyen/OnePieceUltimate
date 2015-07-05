//////////////////////////////////////////////////////////////////////////
//\ Space Invaders Pt 1
//\  This code is the first step in creating a Space Invaders clone, in this tutorial we will be looking at 
//\  setting up some of the on screen elements for a space invaders game and getting our players cannon
//\  moving around the screen and responding to user input.
//\
/////////////////////////////////////////////////////////////////////////
#include "AIE.h"
#include <string>
#include <cmath>
#include <time.h>
#include <assert.h>
#if !defined(OSX)
	#include <crtdbg.h>
#endif
#include <iostream>
#include <list>
#include <string>

#include "AssetManager.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "GameState.h"
//The Original resolution of Space Invaders was 224 x 260 
//For comparison the Nintendo DS has a resolution of 292 x 192
//We're going to render this out at three times the original resolution (because we can)




int main(int argc, char* argv[])
{

	//\ Lets initialise the AIE Framework and give the window it creates an appropriate title
	Initialise(iScreenWidth, iScreenHeight, false, "One of Piece");
	SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF));
	AddFont("./fonts/invaders.fnt");

	g_AssetManager.Load("Player", "./images/invaders/luffyPlayer.png", 40, 64);
	g_AssetManager.Load("Bullet", "./images/invaders/chopperBullet.png", 24, 36);
	g_AssetManager.Load("Enemy", "./images/invaders/tumblrEnemy.png", 36, 42);
	g_AssetManager.Load("BG", "./images/invaders/OPbackground.png", iScreenWidth, iScreenHeight);
	g_AssetManager.Load("GameBG", "./images/invaders/Logo (2).png", iScreenWidth, iScreenHeight);
	g_AssetManager.Load("VicBG", "./images/invaders/Luffy_One_Piece_Chibi.png", 400, 500);

	new Player();
	Entity::init();
	GameState ecurrentState = gs_MENU;
	ScoreDB &ref = ScoreDB::getInstance();


	ref.Open();
	//ScoreData myScore = { 0, "Your Timer: " };


	do
	{
		ClearScreen();
		float fDeltaT = GetDeltaTime();

		SetFont("./fonts/invaders.fnt");
		Playgame(fDeltaT);
		
		std::string timeFrame = "DeltaTime: ";
		timeFrame.append(std::to_string(fDeltaT));
		SetFont(nullptr);

	} while (FrameworkUpdate() == false && running);

	ref.Close();
	g_AssetManager.FreeAll();
	Shutdown();

	return 0;
}
