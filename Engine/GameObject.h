#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Component.h"
#include <type_traits>

#define GAMEOBJECT_NAME_LENGTH	32

class ENGINEDECL CGameObject
{
	friend class CComponent;
	friend class CComponentClassInfo;
	friend class CGame;

public:
	CGameObject*		_next;
	CComponent*			_componentHead;
	bool				_alive;

	CGameObject(){};
	~CGameObject()
	{
		CComponent* c = _componentHead;
		while(c)
		{
			CComponent* tmp = c;
			c = c->_next;
			delete tmp;
		}
	};

	bool			_writeToFile(FILE* file);
	bool			_readFromFile(FILE* file);
	CComponent*		_addComponentRaw(const CComponentClassInfo* inf);
	void			_render() const;
	void			_update() const;
	bool			_aliveActive() { return (*(short*)(&_alive)) == 0x101; }

public:
	bool				active;
	SVec2				position;
	SVec2				size;
	SColor				color;
	float				rotation;
	cstr				name;

	//send message to components
	void			sendMessage(uint message, void* data) const;
	CGameObject*	getNext() const;
	void			destroy();
	void			destroyComponents();
	uint			componentCount();


	static bool Exist(const CGameObject* obj);


	CComponent*				addComponent(const CComponentClassInfo* inf);
	CComponent*				getComponent(const CComponentClassInfo* inf);
	CComponent*				addComponent(uint typeHash);
	CComponent*				getComponent(uint typeHash);
	CComponent*				addComponent(cstr classname);
	CComponent*				getComponent(cstr classname);

	CComponent*				getComponentByIndex(uint index) const;

	//-1 if destroyed
	int getIndex() const;


	template < class T> T*	addComponent() 
	{ 
		static_assert(std::is_base_of<CComponent, T>::value, "T Must Be Derived From CComponent");
		return (T*)addComponent(T::GetInfo());
	}
	template < class T> T*	getComponent() 
	{
		static_assert(std::is_base_of<CComponent, T>::value, "T Must Be Derived From CComponent");
		return (T*)addComponent(T::GetInfo());

	}
};


#endif	//__GAMEOBJECT_H__