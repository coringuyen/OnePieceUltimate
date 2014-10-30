#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
	
	static int s_maxEnemies;

	Enemy(int x, int y) : Entity("Enemy", x, y, 110, 50, 100, iScreenWidth - 50, iScreenHeight)
	{  // Marco provide this.
		for (int i = 0; i < s_maxEnemies; ++i) // check all the enemies if the enemy exist set it equal to this ( i dont know what 'this' point to)
		{
			if (!m_Enemies[i])
			{
				m_Enemies[i] = this;
				break;
			}
		}
	}

	bool IsActive() // this is to check if enemies on the screen
	{
		return m_y > 0 && m_y < m_h;
	}

	void onCollide(const Entity *e) // when its collide move it up  out the screen
	{
		m_y = m_h + 100;
	}

	void Update(float dt) // update enemies movement
	{
		m_x += speed * dt; 
	}
};
int Enemy::s_maxEnemies = 49;