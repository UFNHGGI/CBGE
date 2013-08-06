#include "PlayerControl.h"
#include "EnemyControl.h"
#include "Bullet.h"

COMPONENT_IMPL(CPlayerControl);

void CPlayerControl::hit( int val )
{
	health -= val;
	if(health < 1)
		owner()->destroy();
}

void CPlayerControl::onCreate()
{
	moveSpeed	= SVec2(4.5f);
	health		= 100;
}

void CPlayerControl::onUpdate()
{
	SVec2 pos = owner()->position;

	if(CInput::KeyDown(VK_RIGHT))
		pos.x += moveSpeed.x;
	else if(CInput::KeyDown(VK_LEFT))
		pos.x -= moveSpeed.x;

	if(CInput::KeyDown(VK_UP))
		pos.y -= moveSpeed.y;
	else if(CInput::KeyDown(VK_DOWN))
		pos.y += moveSpeed.y;

	SVec2 mousePos = SVec2(CInput::MouseX(), CInput::MouseY());
	SVec2 dirToMouse = mousePos - pos;
	dirToMouse.normalize();
	
	owner()->rotation = atan2(dirToMouse.y, dirToMouse.x) * RAD2DEG;

	if(CInput::MousePress(0))
		CBullet::Throw(pos + dirToMouse, dirToMouse);
	if(CInput::MousePress(1))
		CGame::AddObject("enemy", CInput::MouseX(), CInput::MouseY())->addComponent<CEnemyControl>();

	owner()->position = pos;
}