#pragma once
#include <Engine.h>

#include "CP1Basic.h"

class CP1DECL CRotateAround : public CComponent
{
public:
	SVec2 pivot;
	float radius;
	float curRotation;
	float rotationSpeed;

	COMPONENT_REG_BEGIN(CRotateAround)
	COMPONENT_REG_VAR(pivot)
	COMPONENT_REG_VAR(radius)
	COMPONENT_REG_VAR(curRotation)
	COMPONENT_REG_VAR(rotationSpeed)
	COMPONENT_REG_END()

	void onCreate();
	void onUpdate();
};

