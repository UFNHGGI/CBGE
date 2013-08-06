#pragma once

#include <Engine.h>

#include "CP1Basic.h"

class CP1DECL CFreeMove : CComponent
{
	SVec2	moveSpeed;

	COMPONENT_REG_BEGIN(CFreeMove,  true)
	COMPONENT_REG_VAR(moveSpeed, true)
	COMPONENT_REG_END()

	void onCreate()
	{
		moveSpeed = SVec2(RandRange(1, 5));
	}
	void onUpdate()
	{
		if(CInput::KeyDown('D'))
			owner()->position.x += moveSpeed.x;
		else if(CInput::KeyDown('A'))
			owner()->position.x -= moveSpeed.x;

		if(CInput::KeyDown('W'))
			owner()->position.y -= moveSpeed.y;
		else if(CInput::KeyDown('S'))
			owner()->position.y += moveSpeed.y;
	}
};
