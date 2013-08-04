#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "Basic.h"
#include <functional>
#include <type_traits>
#include <map>

#define COMPONENT_REG_BEGIN(Class)										\
	public:																\
	static const CComponentClassInfo* RegClass() {						\
		typedef Class _Class_;											\
		static const char* _ClassName = #Class;							\
		static const size_t _ClassHash = StrHash( #Class );				\
		static const Class * _ClassIns = nullptr;						\
		static SComponentVarInfo _Vars[] = {



#define COMPONENT_REG_VAR(Var)	{ #Var, offsetof(_Class_, Var ), sizeof(_ClassIns->##Var)				\
	, typeid(decltype(_ClassIns->##Var)).name()	, StrHash(typeid(decltype(_ClassIns->##Var)).name())	\
	, _DetectType(typeid(decltype(_ClassIns->##Var)).hash_code()) }, 



#define COMPONENT_REG_END()																				\
		{ nullptr, 0, 0, nullptr, 0, EComponentVarType::EVT_UNKNOW }};									\
		return CGame::RegComponentClass(_ClassName, sizeof(_Class_), _Vars								\
		, sizeof(_Vars)/sizeof(SComponentVarInfo)-1, [](){ return (CComponent*)(new _Class_); });	}	\
		private :																						\
		static const CComponentClassInfo* INFO;															\
		public :																						\
		static const CComponentClassInfo* GetInfo(){ return INFO; } 


#define COMPONENT_IMPL(Class) const CComponentClassInfo* Class##::INFO = Class##::RegClass();


//////////////////////////////////////////////////////////////////////////fwd decl
class CGameObject;
class CGame;

class CComponent;


enum EComponentVarType
{
	EVT_UNKNOW, EVT_BOOL, EVT_CHAR, EVT_UCHAR, EVT_SHORT, EVT_USHORT, EVT_INT, EVT_UINT,
	EVT_FLOAT, EVT_DOUBLE, EVT_VEC2, EVT_COLOR, EVT_CSTR, EVT_COMPONENTPTR, EVT_GAMEOBJECTPTR
};

inline size_t GetSizeOfComponentVar(EComponentVarType cvt)
{
	const size_t sizes[] = 
	{
		0, sizeof(bool), sizeof(char), sizeof(unsigned char), sizeof(short), sizeof(unsigned short),
		sizeof(int), sizeof(unsigned int), sizeof(float), sizeof(double), sizeof(SVec2), sizeof(SColor),
		sizeof(cstr), sizeof(CComponent*), sizeof(CGameObject*)
	};

	return sizes[cvt];
}

inline EComponentVarType _DetectType(size_t typehash)
{
	static const size_t _bool = typeid(bool).hash_code();
	static const size_t _char = typeid(char).hash_code();
	static const size_t _uchar = typeid(unsigned char).hash_code();
	static const size_t _short = typeid(short).hash_code();
	static const size_t _ushort = typeid(unsigned short).hash_code();
	static const size_t _int = typeid(int).hash_code();
	static const size_t _uint = typeid(unsigned int).hash_code();
	static const size_t _float = typeid(float).hash_code();
	static const size_t _double = typeid(double).hash_code();
	static const size_t _vec2 = typeid(SVec2).hash_code();
	static const size_t _color = typeid(SColor).hash_code();
	static const size_t _cstr = typeid(cstr).hash_code();
	static const size_t _componentPtr = typeid(CComponent*).hash_code();
	static const size_t _gameObjPtr = typeid(CGameObject*).hash_code();

	if(typehash == _bool) { return EComponentVarType::EVT_BOOL; }
	if(typehash == _char) { return EComponentVarType::EVT_CHAR; }
	if(typehash == _uchar) { return EComponentVarType::EVT_UCHAR; }
	if(typehash == _short) { return EComponentVarType::EVT_SHORT; }
	if(typehash == _ushort) { return EComponentVarType::EVT_USHORT; }
	if(typehash == _int) { return EComponentVarType::EVT_INT; }
	if(typehash == _uint) { return EComponentVarType::EVT_UINT; }
	if(typehash == _float) { return EComponentVarType::EVT_FLOAT; }
	if(typehash == _double) { return EComponentVarType::EVT_DOUBLE; }
	if(typehash == _vec2) { return EComponentVarType::EVT_VEC2; }
	if(typehash == _color) { return EComponentVarType::EVT_COLOR; }
	if(typehash == _cstr) { return EComponentVarType::EVT_CSTR; }
	if(typehash == _componentPtr) { return EComponentVarType::EVT_COMPONENTPTR; }
	if(typehash == _gameObjPtr) { return EComponentVarType::EVT_GAMEOBJECTPTR; }

	return EComponentVarType::EVT_UNKNOW;
}

struct SComponentVarInfo
{
	cstr			varName;
	uint			varOffset;
	uint			typeSize;
	cstr			typeName;
	uint			typeNameHash;
	EComponentVarType		type;
};




class CComponentClassInfo
{
	friend class CComponent;
	friend class CGame;
	friend class CGameObject;

private:
	CComponentClassInfo*				_next;
	cstr								_className;
	cstr								_packName;
	uint								_classNameHash;
	uint								_classSize;
	SComponentVarInfo*					_vars;
	uint								_varCount;
	std::function<CComponent*(void)>	_getIns;

	CComponentClassInfo(){};
	~CComponentClassInfo(){};

public:
	const CComponentClassInfo*	next() const					{ return _next;				}
	cstr						className() const				{ return _className;		}
	cstr						packName() const				{ return _packName;			}
	uint						classNameHash() const			{ return _classNameHash;	}
	uint						classSize() const				{ return _classSize;		}
	uint						varCount() const				{ return _varCount;			}
	const SComponentVarInfo&	getVarInfo(uint index) const	{ return _vars[index];		}
	CComponent*					getNewInstance() const			{ return _getIns();			}
};


class ENGINEDECL CComponent
{
	friend class CGame;
	friend class CGameObject;

private:
	CComponent*					_next;
	CGameObject*				_owner;
	const CComponentClassInfo*	_info;
	bool						_alive;

	bool _aliveActive() { return (*(short*)(&_alive)) == 0x101; }

	bool _writeToFile(FILE* file);
	bool _readFromFile(FILE* file);

public:
	bool				active;


	

	CGameObject*				owner() const					{ return _owner;											}
	const CComponentClassInfo*	info() const					{ return _info;												}
	void*						getVarAddress(uint varIndex)	{ return ((char*)this)+_info->_vars[varIndex].varOffset;	}
	void						destroy()						{ if(_alive) { _alive = false; onDestroy();	}				}
	
	//-1 if destroyed
	int						getIndex() const;
	CComponent*				getNext() const;

protected:

	CComponent(){};
	~CComponent(){};

	virtual void onCreate()									{};
	virtual void onUpdate()									{};
	virtual void onDestroy() 								{};
	virtual void onMessage(uint message, void* data)		{};
};



#endif	//__COMPONENT_H__