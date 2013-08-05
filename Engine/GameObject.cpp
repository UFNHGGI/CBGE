#include "Game.h"

#include <Windows.h>
#include <gl\GLU.h>


void CGameObject::sendMessage( uint message, void* data ) const
{
	CComponent* c = _componentHead;
	while(c)
	{
		if(c->_aliveActive())
			c->onMessage(message, data);
		c = c->_next;
	}
}

void CGameObject::destroy()
{
	if(_alive)
	{
		_alive = false;
		destroyComponents();
	}
}

void CGameObject::destroyComponents()
{
	CComponent* c = _componentHead;
	while(c)
	{
		c->destroy();
		c = c->_next;
	}
}

CComponent* CGameObject::_addComponentRaw( const CComponentClassInfo* inf )
{
	CComponent* newCom = inf->getNewInstance();
	newCom->_next = nullptr;
	newCom->_owner = this;
	newCom->_info = inf;
	newCom->active = true;
	newCom->_alive = true;

	if(_componentHead)
	{
		CComponent* lastCom = _componentHead;
		for(;;)
		{
			if(lastCom->_next)
				lastCom = lastCom->_next;
			else
				break;
		}
		lastCom->_next = newCom;
	}
	else
	{
		_componentHead = newCom;
	}

	return newCom;
}


CComponent* CGameObject::addComponent( const CComponentClassInfo* inf )
{
	if(inf == nullptr)
		return nullptr;
	
	CComponent* c = getComponent(inf);
	if(c)	return c;

	c = _addComponentRaw(inf);
 	c->onCreate();
	return c;
}

CComponent* CGameObject::getComponent( const CComponentClassInfo* inf )
{
	CComponent* c = _componentHead;
	while(c)
	{
		if(c->_info == inf && c->_aliveActive())
			return c;
		c = c->_next;
	}
	return nullptr;
}

CComponent* CGameObject::getComponent( uint typeHash )
{
	return getComponent(CGame::GetComponentClass(typeHash));
}

CComponent* CGameObject::getComponent( cstr classname )
{
	return getComponent(CGame::GetComponentClass(classname));
}

CComponent* CGameObject::addComponent( uint typeHash )
{
	return addComponent(CGame::GetComponentClass(typeHash));
}

CComponent* CGameObject::addComponent( cstr classname )
{
	return addComponent(CGame::GetComponentClass(classname));
}

void CGameObject::_update() const
{
	CComponent* c =  _componentHead;
	while(c)
	{
		if(c->_aliveActive())
			c->onUpdate();
		c = c->_next;
	}
}

void CGameObject::_render() const
{
	glPushMatrix();
	glTranslatef(position.x, position.y, 0.0f);
 	glRotatef(rotation, 0, 0, 1);


	glColor3fv((float*)&color);

	glBegin(GL_QUADS);

	float sinRotation = sin(rotation);
	float cosRotation = cos(rotation);
	float sizeHalfX = size.x * 0.5f;
	float sizeHalfY = size.y * 0.5f;

	glVertex2f(-sizeHalfX,-sizeHalfY);
	glVertex2f(sizeHalfX, -sizeHalfY);
	glVertex2f(sizeHalfX, sizeHalfY);
	glVertex2f(-sizeHalfX, sizeHalfY);

	glEnd();

	glPopMatrix();
}



bool CGameObject::_writeToFile( FILE* file )
{
	fwrite(&active, sizeof(active), 1, file);
	fwrite(&position, sizeof(position), 1, file);
	fwrite(&size, sizeof(size), 1, file);
	fwrite(&color, sizeof(color), 1, file);
	fwrite(&rotation, sizeof(rotation), 1, file);

	short nameLen = 0;
	if(name)
	{
		nameLen = strlen(name);
		fwrite(&nameLen, sizeof(nameLen), 1, file);
		fwrite(name, nameLen, 1, file);
	}
	else
	{
		fwrite(&nameLen, sizeof(nameLen), 1, file);
	}

	uint nCom = componentCount();
	fwrite(&nCom, sizeof(nCom), 1, file);	//write ComponentCount
	CComponent* com = _componentHead;
	while(com)
	{
		if(com->_alive)
		{
			fwrite(&(com->_info->_classNameHash), sizeof(uint), 1, file);	//write component class hash
			com->_writeToFile(file);
		}
		com = com->_next;
	}
	return true;
}

bool CGameObject::_readFromFile( FILE* file )
{
	fread(&active, sizeof(active), 1, file);
	fread(&position, sizeof(position), 1, file);
	fread(&size, sizeof(size), 1, file);
	fread(&color, sizeof(color), 1, file);
	fread(&rotation, sizeof(rotation), 1, file);
	
	short nameLen = 0;
	fread(&nameLen, sizeof(nameLen), 1, file);
	if(nameLen == 0)
	{
		name = "";
	}
	else
	{
		char* str = new char[nameLen+1];
// 		CGame::_DeleteAfterGameLoad(str);
		fread(str, nameLen, 1, file);
		str[nameLen] = '\0';
		name = str;
	}

	uint nCom = 0;
	fread(&nCom, sizeof(nCom), 1, file);	//read componentCount
	uint cClassHash =  0;
	for(uint i = 0; i < nCom; i++)
	{
		fread(&cClassHash, sizeof(cClassHash), 1, file );
		CComponent* com = _addComponentRaw(CGame::GetComponentClass(cClassHash));
		if(com) 
			com->_readFromFile(file);
		else
			return false;
	}
	return true;
}

uint CGameObject::componentCount()
{
	uint n = 0;
	CComponent* c = _componentHead;
	while(c)
	{
		if(c->_alive)
			n++;
		c = c->_next;
		
	}
	return n;
	
}

CComponent* CGameObject::getComponentByIndex( uint index ) const
{
	CComponent* c = _componentHead;
	while(c)
	{
		if(c->_alive)
		{
			if(index == 0)
				return c;
			index--;
		}
		c = c->_next;
	}

	return nullptr;
}

int CGameObject::getIndex() const
{
	//game.cpp
	extern CGameObject*	Game_FirstObj;

	CGameObject* obj = Game_FirstObj;
	int index = 0;
	while(obj)
	{
		if(obj->_alive)
		{
			if(obj == this)
				return index;
			index++;
		}

		obj = obj->_next;
	}
	return -1;
}

CGameObject* CGameObject::getNext() const
{
	CGameObject* obj = _next;
	while(obj)
	{
		if(obj->_alive)
			return obj;

		obj = obj->_next;
	}
	return nullptr;
}

bool CGameObject::Exist( const CGameObject* obj )
{
	//Game.cpp
	extern CGameObject* Game_FirstObj;

	if(obj)
	{
		auto iter = Game_FirstObj;
		while(iter)
		{
			if(iter == obj)
				return obj->_alive;
			iter = iter->_next;
		}
	}
	return false;
}




