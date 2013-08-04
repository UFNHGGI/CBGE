#include "Input.h"

extern bool		Game_KeysCur[256];
extern bool		Game_KeysPre[256];
extern bool		Game_MouseBtnCur[3];
extern bool		Game_MouseBtnPre[3];
extern int		Game_MouseX;
extern int		Game_MouseY;

bool CInput::KeyDown( int key )
{
	return Game_KeysCur[key];
}

bool CInput::KeyPress( int key )
{
	return Game_KeysCur[key] && !Game_KeysPre[key];
}

bool CInput::KeyRelease( int key )
{
	return !Game_KeysCur[key] && Game_KeysPre[key];
}

bool CInput::MouseDown( int btn )
{
	return Game_MouseBtnCur[btn];
}

bool CInput::MousePress( int btn )
{
	return Game_MouseBtnCur[btn] && !Game_MouseBtnPre[btn];
}

bool CInput::MouseRelease( int btn )
{
	return !Game_MouseBtnCur[btn] && Game_MouseBtnPre[btn];
}

int CInput::MouseX()
{
	return Game_MouseX;
}

int CInput::MouseY()
{
	return Game_MouseY;
}
