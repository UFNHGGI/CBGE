#pragma once

#include <Engine.h>
#include "CP1Basic.h"

class CP1DECL CRotateAroundObject : public CComponent
{
public:
	CGameObject*	target;
	float			radius;
	float			rotationSpeed;
	float			curRotation;

	COMPONENT_REG_BEGIN(CRotateAroundObject, true)
	COMPONENT_REG_VAR(target, true)
	COMPONENT_REG_VAR(radius, true)
	COMPONENT_REG_VAR(rotationSpeed, true)
	COMPONENT_REG_VAR(curRotation, false)
	COMPONENT_REG_END()

	void onCreate()
	{
		target = nullptr;
		radius = 32.0f;
		rotationSpeed = 0.1f;
		curRotation = 0.0f;
	}
	void onUpdate()
	{
		if(target)
		{
			owner()->position = target->position + SVec2(cos(curRotation)*radius, sin(curRotation)*radius);
			curRotation += rotationSpeed;
		}
	}
};