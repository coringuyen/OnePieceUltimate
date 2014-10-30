#pragma once
#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet(double x, double y) : Entity("Bullet", x, y, 400, 10, 0, 10, iScreenHeight) {}

	static int s_maxBullet;

	void Update(float dt) // Update bullets movement
	{
		m_y += speed * dt;

	}

	void onCollide(const Entity *e) // collide move out the screen
	{
		m_y = m_h + 100;
	}

	bool IsActive() // check to see if the bullet is on the screen
	{
		return m_y > 0 && m_y < m_h;
	}

	static void SpawnBullet(float a_x, float a_y) // function to create bullet
	{
		for (int i = 0; i < s_maxBullet; ++i) // loop through all the bullets
		{
			if (m_bullets[i] && !m_bullets[i]->IsActive()) // if the bullet exist and any bullet that active
			{
				delete m_bullets[i]; // delete it
				m_bullets[i] = nullptr; // set it to Null
			}
			if (!m_bullets[i]) // if there no bullet exist
			{
				m_bullets[i] = new Bullet(a_x, a_y); // create new bullet
				break;
			}
		}
	}
};
int Bullet::s_maxBullet = 10;
