#pragma once

#include <Engine.h>

class CPlayerControl : public CComponent
{
public:
	SVec2			moveSpeed;
	short			health;

	COMPONENT_REG_BEGIN(CPlayerControl, true)
	COMPONENT_REG_VAR(moveSpeed, true)
	COMPONENT_REG_VAR(health, true)
	COMPONENT_REG_END()

	void onCreate();
	void onUpdate();
	void hit(int val);
};

