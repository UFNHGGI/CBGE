#pragma once
#include <Engine.h>

#include "CP1Basic.h"
#include "RotateAround.h"

class CP1DECL CFreeMove : CComponent
{
	SVec2	moveSpeed;

	COMPONENT_REG_BEGIN(CFreeMove)
	COMPONENT_REG_VAR(moveSpeed)
	COMPONENT_REG_END()

	void onCreate();
	void onUpdate();
};
