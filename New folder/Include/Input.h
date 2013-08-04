#ifndef __INPUT_H__
#define __INPUT_H__

#include "Basic.h"

class ENGINEDECL Input
{
public:
	static bool KeyDown(int key);
	static bool KeyPress(int key);
	static bool KeyRelease(int key);
};

#endif	//__INPUT_H__