#include "Bullet.h"



Bullet::Bullet(char ic, int xx, int yy, Player* p, std::vector<bool>* m, std::vector<GameEntity*>* e, int mx, int my)
	: GameEntity(ic, xx, yy, p, m, e, mx, my)
{
	
}


Bullet::~Bullet()
{
}


void Bullet::update()
{
	x += vel.x;
	y += vel.y;

	if (physmap->at((int)x + (int)y * mapsizex) == true)
	{
		alive = false;
	}
	else
	{
		for (int i = 0; i < entities->size(); ++i)
		{
			if (entities->at(i)->icon == '&' && (int)entities->at(i)->x == (int)x && (int)entities->at(i)->y == (int)y)
			{
				entities->at(i)->alive = false;
				alive = false;
				break;
			}
		}
	}
}