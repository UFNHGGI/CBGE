#pragma once

#include <Engine.h>
#include "CP1Basic.h"

#define ENEMY_BULLETTHROW_DELAY		30
#define ENEMY_FINDTARGET_DELAY		30

class CP1DECL CEnemyControl : public CComponent
{
public:
	float			moveSpeed;
	float			attackRadius;
	float			viewRadius;
	short			health;
	short			bulletThrowElapsed;
	CGameObject*	target;
	bool			canThrowBullet;

	COMPONENT_REG_BEGIN(CEnemyControl, true)
	COMPONENT_REG_VAR(moveSpeed, true)
	COMPONENT_REG_VAR(attackRadius, true)
	COMPONENT_REG_VAR(viewRadius, true)
	COMPONENT_REG_VAR(health, true)
	COMPONENT_REG_VAR(bulletThrowElapsed, false)
	COMPONENT_REG_VAR(target, false)
	COMPONENT_REG_VAR(canThrowBullet, false)
	COMPONENT_REG_END()

	void onCreate();
	void onUpdate();

	void				attackToTarget();
	void				findTarget();
	void				hit(int val);
	CGameObject*		getNearEnemy();
};