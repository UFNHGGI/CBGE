#pragma once
#include <Engine.h>

#include "CP1Basic.h"

class CP1DECL CRotateAroundPoint : public CComponent
{
public:
	SVec2 point;
	float radius;
	float rotationSpeed;
	float curRotation;

	COMPONENT_REG_BEGIN(CRotateAroundPoint, true)
	COMPONENT_REG_VAR(point, true)
	COMPONENT_REG_VAR(radius, true)
	COMPONENT_REG_VAR(rotationSpeed, true)
	COMPONENT_REG_VAR(curRotation, false)
	COMPONENT_REG_END()

	void onCreate()
	{
		point = owner()->position;
		radius = 64.0f;
		curRotation = 0.0f;
		rotationSpeed = 0.08f;
	}
	void onUpdate()
	{
		owner()->position = point + SVec2(cos(curRotation)* radius, sin(curRotation) * radius);
		curRotation += rotationSpeed;
	}
};

