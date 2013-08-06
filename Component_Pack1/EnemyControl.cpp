#include "EnemyControl.h"
#include "PlayerControl.h"
#include "Bullet.h"
#include <vector>

COMPONENT_IMPL(CEnemyControl);

void CEnemyControl::onCreate()
{
	moveSpeed = RandRange(3,5);
	attackRadius = RandRange(100,110);
	viewRadius = RandRange(190, 210);
	health = 100;

	target = nullptr;
	bulletThrowElapsed = 0;
	canThrowBullet = true;

	owner()->color = SColor(1,0,0);
}

void CEnemyControl::onUpdate()
{
	if(CGameObject::Exist(target))
		attackToTarget();
	else
		findTarget();

	if(!canThrowBullet)
	{
		bulletThrowElapsed++;
		if(bulletThrowElapsed > ENEMY_BULLETTHROW_DELAY)
		{
			bulletThrowElapsed = 0;
			canThrowBullet = true;
		}
	}
}



void CEnemyControl::findTarget()
{
	if(rand() % 3)
		return;
	
	CGameObject* objIter = CGame::GetObjByIndex(0);
	while(objIter)
	{
		if(objIter->getComponent<CPlayerControl>())
		{
			target = objIter;
			return;
		}
		objIter = objIter->getNext();
	}

	target = nullptr;
}

void CEnemyControl::attackToTarget()
{
	if(rand() % 21)
		findTarget();

	SVec2 dir = target->position - owner()->position;
	float dist = dir.normalize();
	owner()->rotation = atan2(dir.y, dir.x) * RAD2DEG;

	if(dist < viewRadius)
	{
		if(dist < attackRadius)
		{
			if(canThrowBullet)
			{
				CBullet::Throw(owner()->position + dir, dir);
				canThrowBullet = false;
				target->getComponent<CPlayerControl>()->hit(8);
			}
		}
		else
		{
			owner()->position += dir*(moveSpeed-dist*0.0001);
		}
	}
	else
		findTarget();
}

void CEnemyControl::hit( int val )
{
	health -= val;
	if(health < 1)
		owner()->destroy();
}