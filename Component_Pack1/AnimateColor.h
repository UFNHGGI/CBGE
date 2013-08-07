#pragma once

#include <Engine.h>
#include "CP1Basic.h"

class CP1DECL CAnimateColor : public CComponent
{
public:
	SColor	color1;
	SColor	color2;
	float	lerpSpeed;
	float	lerpValue;

	COMPONENT_REG_BEGIN(CAnimateColor, true)
	COMPONENT_REG_VAR(color1, true)
	COMPONENT_REG_VAR(color2, true)
	COMPONENT_REG_VAR(lerpSpeed, true)
	COMPONENT_REG_VAR(lerpValue, true)
	COMPONENT_REG_END()

	void onCreate()
	{
		color1 = SColor(RandF01(), RandF01(), RandF01());
		color2 = SColor(1) - color1; 
		lerpSpeed = 0.01f;
		lerpValue = 0.0f;

	}
	void onUpdate()
	{
		lerpValue += lerpSpeed;
		if(lerpValue >= 2.0f)
			lerpValue = 0.0f;

		owner()->color = SColor::Lerp(color1, color2, lerpValue > 1.0f ? 2.0f - lerpValue : lerpValue);
	}
};