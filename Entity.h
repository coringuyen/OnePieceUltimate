#pragma once
#include"AIE.h"
#include <vector>
#include <cmath>
#include <cstring>
#include "AssetManager.h"
#include "ScoreBuffer.h"


class Entity
{
protected:
	static std::vector<Entity*> s_entities; // can you tell me what this do again?

	
	double m_x, m_y;
	int m_w, m_h;
	int xmin, ymin;
	float speed;
	unsigned sprite;
	static int s_score;
	static char s_points[32];
	static Entity *m_bullets[10];
	static Entity *m_Enemies[49];
	static Entity *m_player;

	std::string m_name;
public:
	static float  m_time;

	Entity(const char *name, double a_x, double a_y, float sp, int a_xmin, int a_ymin, int a_w,  int a_h) // i'm still abit confuse on this. 
	{
		m_name = name;
		m_x = a_x;
		m_y = a_y; // m_x = m_x;
		speed = sp;
		xmin = a_xmin;
		ymin = a_ymin;
		m_w = a_w;
		m_h = a_h;
	}

	virtual bool IsActive() { return true; } // this is to over write it 
	void draw() { g_AssetManager.Draw(m_name.c_str(), m_x, m_y); } // this is to draw pass in name and position
	virtual void Update(float dt) = 0; // over write for update
	virtual void onCollide(const Entity *e) {} // switch goes here

	float Distance(const Entity *b) // check the distance between 2 object
	{
		return sqrt((m_x - b->m_x) * (m_x - b->m_x) + (m_y - b->m_y) * (m_y - b->m_y));
	}

	// credit: Eric. This is to check all the enemies and bullets if they exist delete all them and set them to Null also set both score to 0
	static void Reset()
	{
		for (int i = 0; i < 49; ++i)
		{
			if (m_Enemies[i])
			{
				delete m_Enemies[i];
				m_Enemies[i] = nullptr;
			}
		}

		for (int i = 0; i < 10; ++i)
		{
			if (m_bullets[i])
			{
				delete m_bullets[i];
				m_bullets[i] = nullptr;
			}
		}

		s_score = 0; 
		m_time = 0;
	}

	static void DrawScore(int a_x, int a_y) { DrawString(itoa (m_time, s_points, 10), a_x, a_y); } // draw the score while playing

	static bool IsOver() // credit: Eric 
	{
		for (int i = 0; i < 49; ++i) // check all the enemies
			if (m_Enemies[i]) // if the enemy exist
				if (m_Enemies[i]->m_y < 120) { return true; } // if any enemy go over 120, then return true
		return false; // if not then return false
	}

	static bool Won() // credit: Eric
	{
		return s_score == 420; // the exact score is 420, because i'm using time for score so i need this for Victory case
	}                           // which mean if player finish all the enemies it's true

	static void Drawall() // draw everything on the screen
	{
		if (m_player) // check if the player exist
			m_player->draw(); // draw it on the screen

		for (int i = 0; i < 10; ++i) // loop 10 times
			if (m_bullets[i]) // check if bullet exist
				m_bullets[i]->draw(); // draw the bullet on the screen

		for (int i = 0; i < 49; ++i) // loop 49 times
			if (m_Enemies[i] && m_Enemies[i]->IsActive()) // check if the enemies exist and if enemeis active
				m_Enemies[i]->draw(); // draw enemies on the screen

		SetFont("./fonts/invaders.fnt"); 
		DrawString("Your Best Time", iScreenWidth * 0.025f, iScreenHeight - 2);
		DrawString("HI-SCORE", iScreenWidth * 0.8f, iScreenHeight - 2);
		ScoreBuffer::HighScore(iScreenWidth * 0.85, iScreenHeight - 30);
		DrawLine(0, 40, iScreenWidth, 40, SColour(0xFF, 0xFF, 0x00, 0xFF));
		DrawScore(100, iScreenHeight - 30);
	}

	
	static void Updateall(float dt) // Update everything
	{
		m_time += dt; // the time add by DeltaT (score base by time)

		if (m_player) // if the player exist
			m_player->Update(dt); // update player

		for (int i = 0; i < 10; ++i) // loop 10 times
			if (m_bullets[i]) // if the bullets exist
				m_bullets[i]->Update(dt); // update bullets
		
		// Credit: Marco
		bool advance = false; // nothing happen so advance equal false
		for (int i = 0; i < 49; ++i) // loop through 49 enemies
			if (m_Enemies[i] && m_Enemies[i]->IsActive()) // check to see if enemies exist and enemies exist is active
			{
				m_Enemies[i]->Update(dt); //  Update them
				if (m_Enemies[i]->m_x < m_Enemies[i]->xmin && m_Enemies[i]->speed < 0 || m_Enemies[i]->m_x > m_Enemies[i]->m_w && m_Enemies[i]->speed > 0) // 0 and 800 are screen dimensions ,change accordingly
				{ // this is to check when they hit the wall 		
  					advance = true;  // if they do advane equal true
				}
			}

		if (advance)
			for (int i = 0; i < 49; ++i) // loop through all 49 enemies
				if (m_Enemies[i] && m_Enemies[i]->IsActive()) // if the enemes exist and its exist is active
				{
					m_Enemies[i]->speed *= -1; // enemies move to the opposite direction
					m_Enemies[i]->m_y -= 30;	
				}
		// Update collide
		for (int i = 0; i < 10; ++i) // loop through all bullets
			if (m_bullets[i] && m_bullets[i]->IsActive()) // check if its exist and active
				for (int j = 0; j < 49; ++j) // loop through all enemies
					if (m_Enemies[j] && m_Enemies[j]->IsActive()) // check if the enemies exist and active
						if (m_bullets[i]->Distance(m_Enemies[j]) < 30) // i dont get this part
						{
							m_bullets[i]->onCollide(m_Enemies[j]);
							m_Enemies[j]->onCollide(m_bullets[i]);
							s_score += 10;
						}
		
		for (int i = 0; i < 10; ++i) // credit: Eric. this is to add 1s whenever the bullets go over the screen
			if (m_bullets[i] && m_bullets[i]->m_y > (iScreenHeight) && m_bullets[i]->m_y < iScreenHeight + 100)
			{                                      // check if the bullets exist or the bullets go over the screenheight or bullets less than screenheight + 100
				m_bullets[i]->m_y += 1000; // set the bullet go out the screen
				++m_time; // add 1 to the score
			}


	}

	//Credit: Marco. Check all the enemies and set it to null
	static void init()
	{
		for (int i = 0; i < 49; ++i)
			m_Enemies[i] = nullptr;
	}
};
Entity *Entity::m_bullets[10];
Entity *Entity::m_Enemies[49];
int		Entity::s_score;
char	Entity::s_points[32];
Entity *Entity::m_player;
float     Entity::m_time;   // is this part mean to define them?