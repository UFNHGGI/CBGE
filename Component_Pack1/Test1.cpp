#include <Engine.h>

class CTestVars : public CComponent
{
	bool			var_bool;
	char			var_char;
	uchar			var_uchar;
	short			var_short;
	ushort			var_ushort;
	int				var_int;
	uint			var_uint;
	long			var_long;
	ulong			var_ulong;
	int64			var_int64;
	uint64			var_uint64;
	float			var_float;
	double			var_double;
	SVec2			var_vec2;
	SColor			var_color;
	cstr			var_str;
	CGameObject*	var_gameobjectPtr;
	CComponent*		var_componentPtr;

	COMPONENT_REG_BEGIN(CTestVars)
		COMPONENT_REG_VAR(var_bool)
		COMPONENT_REG_VAR(var_char)
		COMPONENT_REG_VAR(var_uchar)
		COMPONENT_REG_VAR(var_short)
		COMPONENT_REG_VAR(var_ushort)
		COMPONENT_REG_VAR(var_int)
		COMPONENT_REG_VAR(var_uint)
		COMPONENT_REG_VAR(var_long)
		COMPONENT_REG_VAR(var_ulong)
		COMPONENT_REG_VAR(var_int64)
		COMPONENT_REG_VAR(var_uint64)
		COMPONENT_REG_VAR(var_float)
		COMPONENT_REG_VAR(var_double)
		COMPONENT_REG_VAR(var_vec2)
		COMPONENT_REG_VAR(var_color)
		COMPONENT_REG_VAR(var_str)
		COMPONENT_REG_VAR(var_gameobjectPtr)
		COMPONENT_REG_VAR(var_componentPtr)
	COMPONENT_REG_END()

	void onCreate()
	{
		memset(&var_bool, 0, sizeof(CTestVars) - offsetof(CTestVars, var_bool));
	}
};

COMPONENT_IMPL(CTestVars);
