#pragma once

#include <Engine.h>
#include "CP1Basic.h"

class CP1DECL CAnimateSize : public CComponent
{
public:
	SVec2	size1;
	SVec2	size2;
	float	lerpValue;
	float	lerpSpeed;

	COMPONENT_REG_BEGIN(CAnimateSize, true)
	COMPONENT_REG_VAR(size1, true)
	COMPONENT_REG_VAR(size2, true)
	COMPONENT_REG_VAR(lerpValue, true)
	COMPONENT_REG_VAR(lerpSpeed, true)
	COMPONENT_REG_END()

	void onCreate()
	{
		size1 = RandRange(16, 40);
		size2 = RandRange(40, 200);
		lerpValue = 0.0f;
		lerpSpeed = 0.01f;
	}
	void onUpdate()
	{
		lerpValue += lerpSpeed;
		if(lerpValue >= 2.0f)
			lerpValue = 0.0f;

		owner()->size = SVec2::Lerp(size1, size2, lerpValue > 1.0f ? 2.0f - lerpValue : lerpValue);
	}
};

