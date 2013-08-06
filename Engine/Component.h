#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "Basic.h"
#include <functional>
#include <type_traits>
#include <map>


#define COMPONENT_REG_BEGIN(Class, ShowInEd)							\
	public:																\
	static const CComponentClassInfo* RegClass() {						\
		typedef Class _Class_;											\
		static const char* _ClassName = #Class;							\
		static const size_t _ClassHash = StrHash( #Class );				\
		static const bool _ShowInEd = ShowInEd;							\
		static const Class * _ClassIns = nullptr;						\
		static SComponentVarInfo _Vars[] = {




#define COMPONENT_REG_VAR(Var, ShowInEd)	{ #Var, offsetof(_Class_, Var ), sizeof(_ClassIns->##Var)	\
	, typeid(decltype(_ClassIns->##Var)).name()	, StrHash(typeid(decltype(_ClassIns->##Var)).name())	\
	, _DetectType(StrHash(typeid(decltype(_ClassIns->##Var)).name())), ShowInEd }, 



#define COMPONENT_REG_END()																				\
		{ nullptr, 0, 0, nullptr, 0, EComponentVarType::EVT_UNKNOW, false }};							\
		return CGame::RegComponentClass(_ClassName, sizeof(_Class_), _Vars								\
			, sizeof(_Vars)/sizeof(SComponentVarInfo)-1, [](){ return (CComponent*)(new _Class_); }		\
			, _ShowInEd);	}																			\
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
	EVT_LONG, EVT_ULONG, EVT_INT64, EVT_UINT64 ,EVT_FLOAT, EVT_DOUBLE, EVT_VEC2, EVT_COLOR,
	EVT_CSTR, EVT_COMPONENTPTR, EVT_GAMEOBJECTPTR
};



ENGINEDECL EComponentVarType _DetectType(uint typehash);

struct SComponentVarInfo
{
	cstr					varName;
	uint					varOffset;
	uint					typeSize;
	cstr					typeName;
	uint					typeNameHash;
	EComponentVarType		type;
	bool					showInEd;
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
	bool								_showInEd;

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
	bool						showInEd() const				{ return _showInEd;			}
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


	
	static bool Exist(const CComponent* c);

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