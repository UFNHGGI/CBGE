#ifndef __BASIC_H__
#define __BASIC_H__

#include <iostream>
#include <math.h>

#define RAD2DEG		57.2957795f
#define DEG2RAD		0.01745329f

#ifdef ENGINE_BUILDDLL
#define ENGINEDECL	__declspec(dllexport)
#else
#define ENGINEDECL	__declspec(dllimport)
#endif


typedef const char* cstr;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef long long int64;
typedef unsigned long long uint64;

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

	SVec2& operator += (const SVec2& v) { x += v.x;		y += v.y;	return *this; }
	SVec2& operator -= (const SVec2& v) { x -= v.x;		y -= v.y;	return *this; }

	float length() const	{ return sqrt(x*x + y*y);	}
	float lengthSq() const  { return x*x + y*y;			}
	float normalize()
	{
		float len = x*x + y*y;
		if(len > 0.00001f)
		{
			len = sqrt(len);
			x /= len;
			y /= len;
			return len;
		}
		else
		{
			x = y = 0.0f;
			return 0.0f;
		}
	}
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

#endif	//__BASIC_H__