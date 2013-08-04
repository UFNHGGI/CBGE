#ifndef __BASIC_H__
#define __BASIC_H__

#include <iostream>
#include <math.h>

typedef const char* cstr;
typedef unsigned int uint;


inline uint StrHash(cstr str)
{
	uint hash = 0;
	while (*str)
	{
		hash = ((hash << 5) + hash) + *str;
		str++;
	}
	return hash;
}

inline float RandF01()
{
	return rand() / ((float)RAND_MAX);
}
inline int RandRange(int min, int max)
{
	return min + (rand() % (1 + max - min));
}

struct SVec2
{
	float x, y;

	SVec2()
		: x(0), y(0) {};
	SVec2(float xy)
		: x(xy), y(xy) {};
	SVec2(float xx, float yy)
		: x(xx), y(yy) {};

	SVec2 operator + (const SVec2& v) const { return SVec2(x+v.x, y+v.y);	}
	SVec2 operator - (const SVec2& v) const { return SVec2(x-v.x, y-v.y);	}
	SVec2 operator * (float f) const		{ return SVec2(x*f, y*f);		}

	float length() const	{ return sqrt(x*x + y*y); }

	static SVec2 Lerp(const SVec2& a, const SVec2& b, float f)
	{
		return a + (b - a) * f;
	}

};


struct SColor
{
	float r, g, b;
	SColor()
		: r(1), g(1), b(1) {};
	SColor(float rgb)
		: r(rgb), g(rgb), b(rgb) {};
	SColor(float rr, float gg, float bb)
		: r(rr), g(gg), b(bb) {};

	SColor operator + (const SColor& c) const	{ return SColor(r+c.r, g+c.g, b+c.b);	}
	SColor operator - (const SColor& c) const	{ return SColor(r-c.r, g-c.g, b-c.b);	}
	SColor operator * (float f) const			{ return SColor(r*f, g*f, b*f);			}

	static SColor Lerp(const SColor& a, const SColor& b,  float f)
	{
		return a + (b - a) * f;
	}
};


#ifdef ENGINE_BUILDDLL
#define ENGINEDECL	__declspec(dllexport)
#else
#define ENGINEDECL	__declspec(dllimport)
#endif

#define DLLEXPORT	__declspec(dllexport)
#define DLLIMPORT	__declspec(dllimport)

#endif	//__BASIC_H__