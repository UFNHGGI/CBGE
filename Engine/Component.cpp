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
		case EVT_UNKNOW:
		case EVT_BOOL:
		case EVT_CHAR:
		case EVT_UCHAR:
		case EVT_SHORT:
		case EVT_USHORT:
		case EVT_INT:
		case EVT_UINT:
		case EVT_FLOAT:
		case EVT_DOUBLE:
		case EVT_VEC2:
		case EVT_COLOR:
			fwrite(getVarAddress(i), var.typeSize, 1, file);
			break;

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
				if((*pObj) && (*pObj)->_alive)
					index = (*pObj)->getIndex();
				fwrite(&index, sizeof(index), 1, file);	//write index of object
			}
			break;

		case EVT_COMPONENTPTR:
			{
				int inds[2] = {-1, -1};
				CComponent** pCom = (CComponent**)getVarAddress(i);
				if((*pCom) && (*pCom)->_alive)
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
		case EVT_UNKNOW:
		case EVT_BOOL:
		case EVT_CHAR:
		case EVT_UCHAR:
		case EVT_SHORT:
		case EVT_USHORT:
		case EVT_INT:
		case EVT_UINT:
		case EVT_FLOAT:
		case EVT_DOUBLE:
		case EVT_VEC2:
		case EVT_COLOR:
			fread(getVarAddress(i), var.typeSize, 1, file);
			break;

		case EVT_CSTR:
			{
				short strLen = 0;
				fread(&strLen, sizeof(strLen), 1, file);
				if(strLen)
				{
					char* str = new char[strLen+1];
					CGame::_DeleteAfterGameLoad(str);
					fread(str, strLen, 1, file);
					str[strLen] = '\0';
					*((cstr*)getVarAddress(i)) = str;
				}
				else
					*((cstr*)getVarAddress(i)) = nullptr;
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
