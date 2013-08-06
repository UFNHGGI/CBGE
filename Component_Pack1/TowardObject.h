#pragma once

#include <Engine.h>
#include "CP1Basic.h"

class CTowardObject : public CComponent
{
public:
	CGameObject*	target;
	float			speed;
	float			minDistance;

	COMPONENT_REG_BEGIN(CTowardObject, true)
	COMPONENT_REG_VAR(target, true)
	COMPONENT_REG_VAR(speed, true)
	COMPONENT_REG_VAR(minDistance, true)
	COMPONENT_REG_END()

	void onCreate()
	{
		target = nullptr;
		speed = 1.0f;
		minDistance = 16.0f;
	}
	void onUpdate()
	{
		if(target)
		{
			SVec2 dir = target->position - owner()->position;
			if(dir.normalize() > minDistance)
				owner()->position += dir * speed;
		}
	}
};