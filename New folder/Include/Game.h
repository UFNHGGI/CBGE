#ifndef __GAME_H__
#define __GAME_H__

#include "GameObject.h"

class ENGINEDECL CGame
{
	friend class CComponent;
	friend class CGameObject;

private:
	static void				_ClearObjectsIfNeed();
	static void				_LoadGameIfNeed();
	static CGameObject*		_AddObjectRaw();
	static void				_InitVarAfterGameLoad(CGameObject** ppObj, int index);
	static void				_InitVarAfterGameLoad(CComponent** ppCom, int objIndex, int compIndex);
	static void				_DeleteAfterGameLoad(void* ptr);

public:
	static CGameObject* AddObject(cstr objName, float x, float y);

	static uint ObjectCount();
	static void Init(uint w, uint h, cstr caption);
	static void Run();
	static void Render();
	static void Update();

	static void Clear();
	static void Exit();
	static bool Save(cstr filename);
	static bool Load(cstr fileName);

	static CGameObject* GetObjByIndex(uint index);

	static const CComponentClassInfo* GetComponentClass(uint typeHash);
	static const CComponentClassInfo* GetComponentClass(cstr className);
	static const CComponentClassInfo* RegComponentClass(cstr className, uint classSize, SComponentVarInfo* vars
		, uint nVar, std::function<CComponent*()> funcNew);

	static void Dbg_PrinComponentClass();
};

#endif	//__GAME_H__

