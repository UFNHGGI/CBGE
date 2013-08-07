#include "Game.h"

#include <list>
#include <WindowsX.h>
#include <gl\GLU.h>

HWND					Game_HWND	= nullptr;
HDC						Game_HDC	= nullptr;
HGLRC					Game_HGLRC	= nullptr;
uint					Game_WndW	= 800;
uint					Game_WndH	= 600;


CGameObject*			Game_FirstObj					= nullptr;
CGameObject*			Game_LastObj					= nullptr;
CComponentClassInfo*	Game_ComponentInfoHead			= nullptr;
bool					Game_Run						= false;
bool					Game_UpdateEngine				= true;
bool					Game_DoUpdateObj				= true;
bool					Game_DoClear					= false;
bool					Game_DoLoad						= false;
cstr					Game_LoadFileName				= nullptr;	
bool					Game_KeysCur[256]				= {false};
bool					Game_KeysPre[256]				= {false};
bool					Game_MouseBtnCur[3]				= {false};
bool					Game_MouseBtnPre[3]				= {false};
bool					Game_IsEditor					= false;
cstr					Game_CurLoadingDLLName			= "";
int						Game_MouseX						= 0;
int						Game_MouseY						= 0;

std::list<HMODULE>		Game_DllList;


struct _SInitObjAL
{
	CGameObject**	dst;
	int				index;
};
struct _SInitComponentAL
{
	CComponent**	dst;
	int				ObjIndex;
	int				ComponentIndex;
};

std::list<_SInitObjAL>			Game_initObjAL;
std::list<_SInitComponentAL>	Game_initComponentAL;

std::list<void*>				Game_DeleleQueue;




LRESULT WINAPI GameWNDProc(HWND wnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch(message)
	{
	case WM_KEYDOWN:
		Game_KeysCur[wparam] = true;
		break;

	case WM_KEYUP:
		Game_KeysCur[wparam] = false;
		break;

	case WM_SIZE :
		Game_WndH = HIWORD(lparam);
		Game_WndW = LOWORD(lparam);
		glViewport(0, 0, Game_WndW, Game_WndH);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,Game_WndW, Game_WndH, 0, 0, 100);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		break;

	case WM_MOUSEMOVE:
		Game_MouseX = GET_X_LPARAM(lparam);
		Game_MouseY = GET_Y_LPARAM(lparam);
		break;

	case WM_LBUTTONDOWN:
		Game_MouseBtnCur[0] = true;
		break;
	case WM_LBUTTONUP:
		Game_MouseBtnCur[0] = false;
		break;

	case WM_RBUTTONDOWN:
		Game_MouseBtnCur[1] = true;
		break;
	case WM_RBUTTONUP:
		Game_MouseBtnCur[1] = false;
		break;

	case WM_MBUTTONDOWN:
		Game_MouseBtnCur[2] = true;
		break;
	case WM_MBUTTONUP:
		Game_MouseBtnCur[2] = false;
		break;

	case WM_DESTROY :
	case WM_CLOSE :
	case WM_QUIT :
		CGame::Exit();
	}
	return DefWindowProc(wnd, message, wparam, lparam);
}

int GameCreateWnd(uint w, uint h, cstr caption)
{
	Game_WndW = w;
	Game_WndH = h;

	WNDCLASSEX wndc;
	wndc.cbSize					= sizeof(WNDCLASSEX);
	wndc.cbClsExtra				= 0;
	wndc.cbWndExtra				= 0;
	wndc.hbrBackground			= 0;
	wndc.hCursor				= LoadCursor(NULL, IDC_ARROW);
	wndc.hIcon					= LoadIcon(NULL, IDI_APPLICATION);
	wndc.hIconSm				= LoadIcon(NULL, IDI_APPLICATION);
	wndc.hInstance				= GetModuleHandle(NULL);
	wndc.lpfnWndProc			= GameWNDProc;
	wndc.lpszClassName			= caption;
	wndc.lpszMenuName			= NULL;
	wndc.style					= CS_HREDRAW | CS_VREDRAW;

	if(!RegisterClassEx(&wndc))
	{
		MessageBox(NULL, "RegisterClassEx Failed", "Error", MB_OK);
		return -1;
	}

	Game_HWND = CreateWindowEx(NULL, caption, caption,  WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, 0
		, w, h, NULL, NULL, NULL, NULL);

	if(!Game_HWND)
	{
		MessageBox(NULL, "CreateWindowEx Failed", "Error", MB_OK);
		return -2;
	}

	Game_HDC = GetDC(Game_HWND);
	if(!Game_HDC)
	{	
		MessageBox(NULL, "GetDC Failed", "Error", MB_OK);
		return -3;
	}


	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize		= sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion	= 1;
	pfd.dwFlags		= PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType	= PFD_TYPE_RGBA;
	pfd.cColorBits	= 24;
	pfd.cDepthBits	= 24;
	pfd.iLayerType	= PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(Game_HDC, &pfd);

	if (nPixelFormat == 0) 
		return -4;

	BOOL bResult = SetPixelFormat (Game_HDC, nPixelFormat, &pfd);
	if (!bResult) 
		return -5;

	Game_HGLRC = wglCreateContext(Game_HDC);
	if(wglMakeCurrent(Game_HDC, Game_HGLRC) == FALSE)
		return -6;

	glClearColor(0,0,0,0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, Game_WndW, Game_WndH, 0, 0, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();



	return 0;
}
void GameDestroyWND()
{
	wglMakeCurrent(Game_HDC, 0);
	wglDeleteContext(Game_HGLRC);
	ReleaseDC(Game_HWND, Game_HDC);
	DestroyWindow(Game_HWND);
}


void CGame::Init( uint w, uint h, cstr caption )
{
	Game_IsEditor = false;
 	GameCreateWnd(w, h, caption);
	LoadDlls();
	std::cout << "Game Init.\n";
}



void CGame::Run()
{
	std::cout << "Game Run.\n";
	ShowWindow(Game_HWND, SW_SHOW);
	SetFocus(Game_HWND);
	Game_Run = true;

	while(Game_UpdateEngine)
	{
		memcpy(Game_KeysPre, Game_KeysCur, sizeof(Game_KeysCur));
		memcpy(Game_MouseBtnPre, Game_MouseBtnCur, sizeof(Game_MouseBtnCur));

		MSG msg;
		while(PeekMessage(&msg, Game_HWND, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		
		_ClearObjectsIfNeed();

		UpdateObjects();

		_ClearObjectsIfNeed();
		_LoadGameIfNeed();

		RenderObjects();

		SwapBuffers(Game_HDC);
		glClear(GL_COLOR_BUFFER_BIT);
	}


	_Release();
}



CGameObject* CGame::_AddObjectRaw()
{
	CGameObject* newObj		= new CGameObject;
	newObj->_next			= nullptr;
	newObj->_componentHead	= nullptr;
	newObj->_alive			= true;

	if(Game_LastObj)
	{
		Game_LastObj->_next = newObj;
		Game_LastObj = newObj;
	}
	else
		Game_LastObj = Game_FirstObj = newObj;

	return newObj;
}


CGameObject* CGame::AddObject( cstr objName , float x, float y)
{
	CGameObject* newObj = _AddObjectRaw();
	newObj->active = true;
	newObj->name = objName ? objName : "Object";
	newObj->position = SVec2(x,y);
	newObj->size = SVec2(10, 10);
	newObj->color = SColor(1,1,1);
	newObj->rotation = 0.0f;
	return newObj;
}

void CGame::Exit()
{
	if(!Game_UpdateEngine)
		return;
	Clear();
	Game_UpdateEngine = false;
}

/*
//////////////////Game File Structure////////////////
Segments:
	COMPONENT = { uint ComponentClassHash } {bool active} {uint varCount} { varData[varCount] }
	OBJECT = { ObjData } { uint ComponentCount } { COMPONENT[ComponentCount] }
	
File:
	{uint objectCount} { OBJCECT[objectCount] }
*/

bool CGame::Save( cstr filename )
{
	if(!filename)
		return false;
	FILE* file = fopen(filename, "wb");
	if(!file)
		return false;
	uint nObj = CGame::ObjectCount();
	fwrite(&nObj, sizeof(nObj), 1, file);	//write objectCount
	CGameObject* obj = Game_FirstObj;
	while(obj)
	{
		if(obj->_alive)
		{
			if(!obj->_writeToFile(file))
			{
				fclose(file);
				return false;
			}
		}
		obj = obj->_next;
	}

	fclose(file);
	std::cout << "Game Saved.\t" << filename << '\n';
	return true;
}

bool CGame::Load( cstr fileName )
{
	if(Game_DoLoad)
		return false;
	CGame::Clear();
	Game_DoLoad = true;
	Game_LoadFileName = fileName;
	return true;
}

void CGame::_LoadGameIfNeed()
{
	if(!Game_DoLoad)
		return;

	//delete pre load-----------
	auto iterDel = Game_DeleleQueue.cbegin();
	for(;iterDel != Game_DeleleQueue.cend(); iterDel++)
		delete *iterDel;
	Game_DeleleQueue.clear();



	//load game--------
	FILE* file = fopen(Game_LoadFileName, "rb");
	if(!file)
		return;
	uint nObj = 0;
	fread(&nObj, sizeof(nObj), 1, file);
	for(uint i = 0; i < nObj; i++)
	{
		CGameObject* obj = _AddObjectRaw();
		if(!obj->_readFromFile(file))
			break;
	}
	fclose(file);



	//init after load---------
	for(auto iterInitObj = Game_initObjAL.cbegin(); iterInitObj != Game_initObjAL.cend(); iterInitObj++)
		if((*iterInitObj).index != -1)
			*(*iterInitObj).dst = CGame::GetObjByIndex((*iterInitObj).index);
		else
			*(*iterInitObj).dst = nullptr;
	Game_initObjAL.clear();

	for(auto iterInitCom = Game_initComponentAL.cbegin(); iterInitCom != Game_initComponentAL.cend(); iterInitCom++)
		if((*iterInitCom).ObjIndex != -1 && (*iterInitCom).ComponentIndex != -1)
		{
			CGameObject* obj =  CGame::GetObjByIndex((*iterInitCom).ObjIndex);
			if(obj)
				*(*iterInitCom).dst = obj->getComponentByIndex((*iterInitCom).ComponentIndex);
			else
				*(*iterInitCom).dst = nullptr;
		}
		else
			*(*iterInitCom).dst = nullptr;
	Game_initComponentAL.clear();



	std::cout << "Game Loaded.\t" << Game_LoadFileName << '\n';
	Game_DoLoad = false;
	Game_LoadFileName = nullptr;
}

const CComponentClassInfo* CGame::GetComponentClass( uint hash )
{
	CComponentClassInfo* cci = Game_ComponentInfoHead;
	while(cci)
	{
		if(cci->_classNameHash == hash)
			return cci;
		cci = cci->_next;
	}
	return nullptr;
}

const CComponentClassInfo* CGame::GetComponentClass( cstr className )
{
	uint hash = StrHash(className);
	CComponentClassInfo* cci = Game_ComponentInfoHead;
	while(cci)
	{
		if(cci->_classNameHash == hash)
			return cci;
		cci = cci->_next;
	}
	return nullptr;
}


const CComponentClassInfo* CGame::RegComponentClass( cstr className, uint classSize, SComponentVarInfo* vars 
	, uint nVar, std::function<CComponent*()> funcNew, bool showInEd )
{
	CComponentClassInfo* newCCI	= new CComponentClassInfo;
	newCCI->_next				= Game_ComponentInfoHead;
	newCCI->_className			= className;
	newCCI->_packName			= Game_CurLoadingDLLName;
	newCCI->_classNameHash		= StrHash(className);
	newCCI->_classSize			= classSize;
	newCCI->_vars				= vars;
	newCCI->_varCount			= nVar;
	newCCI->_getIns				= funcNew;
	newCCI->_showInEd			= showInEd;
	Game_ComponentInfoHead		= newCCI;
	return newCCI;
}

//render && delete objects
void CGame::RenderObjects()
{
	CGameObject* obj = Game_FirstObj;
	CGameObject* objPre = nullptr;
	while(obj)
	{
		if(obj->_aliveActive())
		{
			obj->_render();
			objPre = obj;
			obj = obj->_next;
		}
		else if(obj->_alive == false)
		{
			if(objPre)
				objPre->_next = obj->_next;
			else
				Game_FirstObj = obj->_next;

			if(obj == Game_LastObj)
				Game_LastObj = objPre;

			CGameObject* tmp = obj;
			obj = obj->_next;
			delete tmp;
		}
		else
		{
			objPre = obj;
			obj = obj->_next;
		}
	}
}

void CGame::UpdateObjects()
{
	CGameObject* obj = Game_FirstObj;
	while(obj)
	{
		if(Game_DoUpdateObj)
		{
			obj->_update();
			obj = obj->_next;
		}
		else
		{
			Game_DoUpdateObj = true;
			break;
		}
	}
}

void CGame::Clear()
{
	if(Game_DoClear)
		return;

	Game_DoUpdateObj = false;
	Game_DoClear = true;

	CGameObject* obj = Game_FirstObj;
	while(obj)
	{
		obj->destroy();
		obj = obj->_next;
	}
}


void CGame::_ClearObjectsIfNeed()
{
	if(!Game_DoClear)
		return;

	CGameObject* obj = Game_FirstObj;
	while(obj)
	{
		CGameObject* tmp = obj;
		obj = obj->_next;
		delete tmp;
	}

	Game_FirstObj = Game_LastObj = nullptr;
	Game_DoClear = false;
}

void CGame::Dbg_PrinComponentClass()
{
	CComponentClassInfo* cci = Game_ComponentInfoHead;
	while(cci)
	{
		std::cout << "-------------- Component --------------\n";
		std::cout << "PackName  " << cci->packName() << '\n';
		std::cout << "\tClassName  " << cci->className() << '\n';
		std::cout << "\tClassSize " << cci->classSize() << '\n';
		std::cout << "\tVarCount  " << cci->varCount() << '\n';
		for(uint i= 0; i < cci->varCount(); i++)
		{
			std::cout << "\tVarName  " << cci->getVarInfo(i).varName << '\n';
			std::cout << "\tVarOffset  " << cci->getVarInfo(i).varOffset << '\n';
			std::cout << "\tTypeName  " << cci->getVarInfo(i).typeName << '\n';
			std::cout << "\tTypeSize  " << cci->getVarInfo(i).typeSize << "\n\n";
		}

		cci = cci->_next;
	}
}

uint CGame::ObjectCount()
{
	uint n = 0;	
	CGameObject* obj = Game_FirstObj;
	while(obj)
	{
		if(obj->_alive)
			n++;
		obj = obj->_next;
	}
	return n;
}



void CGame::_InitVarAfterGameLoad( CGameObject** ppObj, int index )
{
	_SInitObjAL s = { ppObj, index};
	Game_initObjAL.push_back(s);
}

void CGame::_InitVarAfterGameLoad( CComponent** ppCom, int objIndex, int compIndex )
{
	_SInitComponentAL s = {ppCom, objIndex, compIndex};
	Game_initComponentAL.push_back(s);
}

void CGame::_DeletePreGameLoad( void* ptr )
{
	Game_DeleleQueue.push_back(ptr);
}

CGameObject* CGame::GetObjByIndex( uint index )
{
	CGameObject* obj = Game_FirstObj;
	while(obj)
	{
		if(obj->_alive)
		{
			if(index == 0)
				return obj;
			index--;
		}
		obj = obj->_next;
	}

	return nullptr;
}

void CGame::_Release()
{
	GameDestroyWND();
	auto iterDel = Game_DeleleQueue.cbegin();
	for(;iterDel != Game_DeleleQueue.cend(); iterDel++)
		delete *iterDel;

	Game_DeleleQueue.clear();
	Game_initObjAL.clear();
	Game_initComponentAL.clear();

	FreeDlls();
}



void CGame::EDEvent( MSG* message )
{
	switch(message->message)
	{
	case WM_KEYDOWN:
		Game_KeysCur[message->wParam] = true;
		break;

	case WM_KEYUP:
		Game_KeysCur[message->wParam] = false;
		break;

	case WM_SIZE :
		Game_WndH = HIWORD(message->lParam);
		Game_WndW = LOWORD(message->lParam);
		glViewport(0, 0, Game_WndW, Game_WndH);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,Game_WndW, Game_WndH, 0, 0, 100);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		break;

	case WM_MOUSEMOVE:
		Game_MouseX = GET_X_LPARAM(message->lParam);
		Game_MouseY = GET_Y_LPARAM(message->lParam);
		break;

	case WM_LBUTTONDOWN:
		Game_MouseBtnCur[0] = true;
		break;
	case WM_LBUTTONUP:
		Game_MouseBtnCur[0] = false;
		break;

	case WM_RBUTTONDOWN:
		Game_MouseBtnCur[1] = true;
		break;
	case WM_RBUTTONUP:
		Game_MouseBtnCur[1] = false;
		break;

	case WM_MBUTTONDOWN:
		Game_MouseBtnCur[2] = true;
		break;
	case WM_MBUTTONUP:
		Game_MouseBtnCur[2] = false;
		break;

	case WM_DESTROY :
	case WM_CLOSE :
	case WM_QUIT :
		CGame::Exit();
	}
}

int CGame::EDInit( HDC hdc )
{
	Game_IsEditor = true;
	Game_HDC = hdc;
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize		= sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion	= 1;
	pfd.dwFlags		= PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType	= PFD_TYPE_RGBA;
	pfd.cColorBits	= 24;
	pfd.cDepthBits	= 24;
	pfd.iLayerType	= PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(Game_HDC, &pfd);

	if (nPixelFormat == 0) 
		return 1;

	BOOL bResult = SetPixelFormat (Game_HDC, nPixelFormat, &pfd);
	if (!bResult) 
		return 2;

	Game_HGLRC = wglCreateContext(Game_HDC);
	if(wglMakeCurrent(Game_HDC, Game_HGLRC) == FALSE)
		return 3;

	glClearColor(0,0,0,0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, Game_WndW, Game_WndH, 0, 0, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	LoadDlls();

	return 0;
}


bool CGame::IsEditor()
{
	return Game_IsEditor;
}

void CGame::EDTick()
{
	_ClearObjectsIfNeed();
	_LoadGameIfNeed();
	RenderObjects();
	SwapBuffers(Game_HDC);
	glClear(GL_COLOR_BUFFER_BIT);
}



void CGame::LoadDlls()
{
	WIN32_FIND_DATA findData;
	HANDLE file = FindFirstFile("component_*.dll", &findData);

	if(file == INVALID_HANDLE_VALUE) 
		return;

	std::cout << "DLL Find...\n";
	do 
	{
		std::cout << '\t' << findData.cFileName << '\n';

		cstr packNameStart = strstr(findData.cFileName, "_")+1;
		size_t len = strlen(packNameStart)-4;
		char* str = new char[len+1];
		memcpy(str, packNameStart, len);
		str[len] = '\0';
		Game_CurLoadingDLLName = str;

		HMODULE lib = LoadLibrary(findData.cFileName);
		if(lib)
		{
			std::cout << "\tLoaded." << '\n';
			Game_DllList.push_back(lib);
		}

	} while (FindNextFile(file, &findData));

	
}

void CGame::FreeDlls()
{
	auto ci = Game_ComponentInfoHead;
	while(ci)
	{
		auto tmp = ci;
		ci = ci->_next;
		delete tmp;
	}
	Game_ComponentInfoHead = nullptr;


	for(auto iter = Game_DllList.cbegin(); iter != Game_DllList.cend(); iter++)
		FreeLibrary(*iter);
	Game_DllList.clear();
}

const CComponentClassInfo* CGame::GetComponentClassHead()
{
	return Game_ComponentInfoHead;
}

