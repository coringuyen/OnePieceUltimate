#pragma once
#include "Entity.h"
#include "Bullet.h"

class Player : public Entity
{
private:
	
public: // credt : eric. i need an explain on this part
	Player() : Entity("Player", iScreenWidth / 2, 71, 600, 32, 0, iScreenWidth - 32, 80), m_fire(true) { m_player = this; }// idk what "m_player = this" do 
	
	bool m_fire; 


	void Update(float dt) // Update player movement moving left or right and fire bullet
	{
		if (IsKeyDown('A')) // moving to left
			m_x -= speed * dt;
		if (m_x < xmin)
			m_x = xmin;

		if (IsKeyDown('D')) // moving to right
			m_x += speed * dt;
		if (m_x > m_w)
			m_x = m_w;

		if (!IsKeyDown(KEY_SPACE)) // credit: Eric
			m_fire = true;         // so if the key space not down then its ok to fire the bullet 
		if (IsKeyDown(KEY_SPACE) && m_fire) // if the key already down then its fire only once
		{
			Bullet::SpawnBullet(m_x, m_y);
			m_fire = false;
		}
	}
};