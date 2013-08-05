#include "Component.h"
#include "Game.h"


bool CComponent::_writeToFile( FILE* file )
{
	fwrite(&active, sizeof(active), 1, file);
	for(uint i = 0; i < _info->_varCount; i++)
	{
		const SComponentVarInfo& var = _info->getVarInfo(i);
		switch(var.type)
		{
		case EVT_CSTR:
			{
				short strLen = 0;
				cstr* pStr = (cstr*)getVarAddress(i);
				if(*pStr)
				{
					strLen = strlen(*pStr);
					fwrite(&strLen, sizeof(strLen), 1, file);
					fwrite(*pStr, strLen, 1, file);
				}
				else
				{
					fwrite(&strLen, sizeof(strLen), 1, file);
				}
			}
			break;

		case EVT_GAMEOBJECTPTR:
			{
				int index = -1;
				CGameObject** pObj = (CGameObject**)getVarAddress(i);
				if(CGameObject::Exist(*pObj))
					index = (*pObj)->getIndex();
				fwrite(&index, sizeof(index), 1, file);	//write index of object
			}
			break;

		case EVT_COMPONENTPTR:
			{
				int inds[2] = {-1, -1};
				CComponent** pCom = (CComponent**)getVarAddress(i);
				if(CComponent::Exist(*pCom))
				{
					inds[0] = (*pCom)->owner()->getIndex();
					inds[1] = (*pCom)->getIndex();
					fwrite(inds, sizeof(inds), 1, file);
				}
				else
				{
					fwrite(inds, sizeof(inds), 1, file);
				}
				break;
			}

		default:
			fwrite(getVarAddress(i), var.typeSize, 1, file);
			break;
		}
		
	}
	return true;
}

bool CComponent::_readFromFile( FILE* file )
{
	fread(&active, sizeof(active), 1, file);
	for(uint i = 0; i < _info->_varCount; i++)
	{
		const SComponentVarInfo& var = _info->getVarInfo(i);
		switch(var.type)
		{
		case EVT_CSTR:
			{
				short strLen = 0;
				fread(&strLen, sizeof(strLen), 1, file);
				if(strLen)
				{
					char* str = new char[strLen+1];
					CGame::_DeletePreGameLoad(str);
					fread(str, strLen, 1, file);
					str[strLen] = '\0';
					*((cstr*)getVarAddress(i)) = str;
				}
				else
					*((cstr*)getVarAddress(i)) = "";
			}
			break;

		case EVT_GAMEOBJECTPTR:
			{
				int objIndex = -1;
				fread(&objIndex, sizeof(objIndex), 1, file);
				CGame::_InitVarAfterGameLoad((CGameObject**)getVarAddress(i), objIndex);
			}
			break;

		case EVT_COMPONENTPTR:
			{
				int inds[2];
				fread(inds, sizeof(inds), 1, file);
				CGame::_InitVarAfterGameLoad((CComponent**)getVarAddress(i), inds[0], inds[1]);
			}
			break;

		default:
			fread(getVarAddress(i), var.typeSize, 1, file);
			break;
		}
	}
	return true;
}

int CComponent::getIndex() const
{
	int index = 0;
	CComponent* c = _owner->_componentHead;
	while(c)
	{
		if(c->_alive )
		{
			if(c == this)
				return index;
			index++;
		}

		c = c->_next;
	}
	return -1;
}

CComponent* CComponent::getNext() const
{
	CComponent* c = _next;
	while(c)
	{
		if(c->_alive)
			return c;

		c = c->_next;
	}
	return nullptr;
}

bool CComponent::Exist( const CComponent* c )
{
	if(c)
	{
		if(CGameObject::Exist(c->_owner))
		{
			auto iter = c->_owner->_componentHead;
			while(iter)
			{
				if(iter == c)
					return c->_alive;
				iter = iter->_next;
			}
		}
	}
	return false;
}

EComponentVarType _DetectType( uint typehash )
{
	static const uint _bool				= StrHash(typeid(bool).name());
	static const uint _char				= StrHash(typeid(char).name());
	static const uint _uchar			= StrHash(typeid(unsigned char).name());
	static const uint _short			= StrHash(typeid(short).name());
	static const uint _ushort			= StrHash(typeid(unsigned short).name());
	static const uint _int				= StrHash(typeid(int).name());
	static const uint _uint				= StrHash(typeid(unsigned int).name());
	static const uint _long				= StrHash(typeid(long).name());
	static const uint _ulong			= StrHash(typeid(unsigned long).name());
	static const uint _int64_			= StrHash(typeid(long long).name());
	static const uint _uint64_			= StrHash(typeid(unsigned long long).name());
	static const uint _float			= StrHash(typeid(float).name());
	static const uint _double			= StrHash(typeid(double).name());
	static const uint _vec2				= StrHash(typeid(SVec2).name());
	static const uint _color			= StrHash(typeid(SColor).name());
	static const uint _cstr				= StrHash(typeid(cstr).name());
	static const uint _componentPtr		= StrHash(typeid(CComponent*).name());
	static const uint _gameObjPtr		= StrHash(typeid(CGameObject*).name());


	if(typehash == _bool)			{ return EComponentVarType::EVT_BOOL;			}
	if(typehash == _char)			{ return EComponentVarType::EVT_CHAR;			}
	if(typehash == _uchar)			{ return EComponentVarType::EVT_UCHAR;			}
	if(typehash == _short)			{ return EComponentVarType::EVT_SHORT;			}
	if(typehash == _ushort)			{ return EComponentVarType::EVT_USHORT;			}
	if(typehash == _int)			{ return EComponentVarType::EVT_INT;			}
	if(typehash == _uint)			{ return EComponentVarType::EVT_UINT;			}
	if(typehash == _long)			{ return EComponentVarType::EVT_LONG;			}
	if(typehash == _ulong)			{ return EComponentVarType::EVT_ULONG;			}
	if(typehash == _int64_)			{ return EComponentVarType::EVT_INT64;			}
	if(typehash == _uint64_)		{ return EComponentVarType::EVT_UINT64;			}
	if(typehash == _float)			{ return EComponentVarType::EVT_FLOAT;			}
	if(typehash == _double)			{ return EComponentVarType::EVT_DOUBLE;			}
	if(typehash == _vec2)			{ return EComponentVarType::EVT_VEC2;			}
	if(typehash == _color)			{ return EComponentVarType::EVT_COLOR;			}
	if(typehash == _cstr)			{ return EComponentVarType::EVT_CSTR;			}
	if(typehash == _componentPtr)	{ return EComponentVarType::EVT_COMPONENTPTR;	}
	if(typehash == _gameObjPtr)		{ return EComponentVarType::EVT_GAMEOBJECTPTR;	}

	return EComponentVarType::EVT_UNKNOW;
}
