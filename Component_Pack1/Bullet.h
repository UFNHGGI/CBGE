#pragma once

#include <Engine.h>
#include "CP1Basic.h"

#define BULLET_DEFAULT_LIFETIME			40
#define BULLET_DEFAULT_SPEED			10
#define BULLET_DEFAULT_DAMAGE			10
#define BULLET_DEFAULT_SIZE				8

class CP1DECL CBullet : public CComponent
{
private:
	SVec2			dir;
	uint			elapsedFrame;
	CGameObject*	target;


	COMPONENT_REG_BEGIN(CBullet, false)
	COMPONENT_REG_VAR(dir, false)
	COMPONENT_REG_VAR(elapsedFrame, false)
	COMPONENT_REG_VAR(target, false)
	COMPONENT_REG_END()

	void onCreate();
	void onUpdate();

public:
	static CGameObject* Throw(const SVec2& startPos, const SVec2& direction);
};

