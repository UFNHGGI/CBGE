#include "AnimateColor.h"

COMPONENT_IMPL(CAnimateColor);


void CAnimateColor::onCreate()
{
	color1 = SColor(RandF01(), RandF01(), RandF01());
	color2 = SColor(1) - color1; 
	lerpValue = 0.0f;
	lerpSpeed = 0.01f;
}

void CAnimateColor::onUpdate()
{
	lerpValue += lerpSpeed;
	if(lerpValue >= 2.0f)
		lerpValue = 0.0f;

	owner()->color = SColor::Lerp(color1, color2, lerpValue > 1.0f ? 2.0f - lerpValue : lerpValue);
}
