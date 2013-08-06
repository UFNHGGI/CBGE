#include "Bullet.h"
#include "PlayerControl.h"
#include "EnemyControl.h"

COMPONENT_IMPL(CBullet);

void CBullet::onCreate()
{
	elapsedFrame = 0;
}

void CBullet::onUpdate()
{
	elapsedFrame++;
	if(elapsedFrame > BULLET_DEFAULT_LIFETIME)
		owner()->destroy();
	else
	{
		SVec2 pos = owner()->position += dir;
		owner()->position = pos;
		CGameObject* objIter = CGame::GetObjByIndex(0);
		while(objIter)
		{
			if((objIter->position - pos).lengthSq() < (BULLET_DEFAULT_SIZE*BULLET_DEFAULT_SIZE))
			{
				auto cEnemy = objIter->getComponent<CEnemyControl>();
				if(cEnemy)
				{
					cEnemy->hit(BULLET_DEFAULT_DAMAGE);
					owner()->destroy();
					return;
				}
				auto cPlayer = objIter->getComponent<CPlayerControl>();
				if(cPlayer)
				{
					cPlayer->hit(BULLET_DEFAULT_DAMAGE);
					owner()->destroy();
					return;
				}
			}

			objIter = objIter->getNext();
		}
	}
}


CGameObject* CBullet::Throw( const SVec2& startPos, const SVec2& direction )
{
	CGameObject* bullet = CGame::AddObject("bullet", startPos.x, startPos.y);
	bullet->size = SVec2(BULLET_DEFAULT_SIZE);
	CBullet* component = bullet->addComponent<CBullet>();
	component->dir = direction * BULLET_DEFAULT_SPEED;
	return bullet;
}

