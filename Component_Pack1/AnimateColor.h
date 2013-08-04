#include <Engine.h>
#include "CP1Basic.h"

class CP1DECL CAnimateColor : public CComponent
{
public:
	SColor	color1;
	SColor	color2;
	float	lerpValue;
	float	lerpSpeed;

	COMPONENT_REG_BEGIN(CAnimateColor)
	COMPONENT_REG_VAR(color1)
	COMPONENT_REG_VAR(color2)
	COMPONENT_REG_VAR(lerpValue)
	COMPONENT_REG_VAR(lerpSpeed)
	COMPONENT_REG_END()

	void onCreate();
	void onUpdate();
};