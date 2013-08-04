#include "RotateAround.h"

COMPONENT_IMPL(CRotateAround);

void CRotateAround::onCreate()
{
	pivot = owner()->position;
	radius = 64.0f;
	curRotation = 0.0f;
	rotationSpeed = 0.08f;
}

void CRotateAround::onUpdate()
{
	owner()->position = pivot + SVec2(cos(curRotation)* radius, sin(curRotation) * radius);
	curRotation += rotationSpeed;
}
