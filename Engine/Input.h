#ifndef __INPUT_H__
#define __INPUT_H__

#include "Basic.h"

class ENGINEDECL CInput
{
public:
	static bool KeyDown(int key);
	static bool KeyPress(int key);
	static bool KeyRelease(int key);
	static bool MouseDown(int btn);
	static bool MousePress(int btn);
	static bool MouseRelease(int btn);
	static int	MouseX();
	static int	MouseY();
};

#endif	//__INPUT_H__