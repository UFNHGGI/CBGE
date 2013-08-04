#include "FreeMove.h"

COMPONENT_IMPL(CFreeMove);


void CFreeMove::onCreate()
{
	moveSpeed = SVec2(RandRange(1, 5));
}

void CFreeMove::onUpdate()
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
