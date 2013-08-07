#include "editor.h"


Editor*			Editor::Instance		= nullptr;
CGameObject*	Editor::SelectedObj		= nullptr;

Editor::Editor(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	Instance = this;
	

	////////////////////////////////Object List
	ui.widgetListObj->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);

	connect(ui.widgetListObj, SIGNAL(customContextMenuRequested(const QPoint&))
		, this, SLOT(slot_ObjectList_MenuRequest(const QPoint&)));

	connect(ui.widgetListObj, SIGNAL(itemClicked(QListWidgetItem *))
		, this, SLOT(slot_ObjectList_ItemClicked(QListWidgetItem*)));

	connect(ui.widgetListObj, SIGNAL(itemChanged ( QListWidgetItem *))
		, this, SLOT(slot_ObjectList_ItemChanged(QListWidgetItem*)));

}

Editor::~Editor()
{

}





void Editor::slot_ObjectList_ItemClicked( QListWidgetItem * item )
{
	SelectObj(CGame::GetObjByIndex(Instance->ui.widgetListObj->currentRow()));
}

void Editor::slot_ObjectList_MenuRequest( const QPoint& p )
{
	if(ui.widgetListObj->itemAt(p) == nullptr)
		return;

	static QMenu			mainMenu;
	static bool				firstExex = true;
	static QAction*			actionDelObj = nullptr;

	if(firstExex)
	{
		firstExex = false;
		actionDelObj = mainMenu.addAction("Delete");

		static QMenu*			menuAddComp = mainMenu.addMenu("Add Component");
		static QVector<QMenu*>  listMenuCompPack;
		
		auto ci = CGame::GetComponentClassHead();
		while(ci)
		{
			for(auto iter = listMenuCompPack.begin(); iter != listMenuCompPack.end(); iter++)
			{
				if(ci->packName() == (*iter)->title())
				{
					if(ci->showInEd())
						(*iter)->addAction(ci->className());
					goto SEC1;
				}
			}

			if(ci->showInEd())
			{
				QMenu* newMenu = menuAddComp->addMenu(ci->packName());
				newMenu->addAction(ci->className());
				listMenuCompPack.push_back(newMenu);
			}
SEC1:
			ci = ci->next();
		}
	}


	QAction* actionRet = mainMenu.exec(ui.widgetListObj->mapToGlobal(p));
	if(actionRet)
	{
		if(actionRet == actionDelObj)
		{
			CGameObject* obj = CGame::GetObjByIndex(ui.widgetListObj->currentRow());
			obj->destroy();
			delete ui.widgetListObj->takeItem(ui.widgetListObj->currentRow());
			Editor::SelectObj(nullptr);
		}
		else
		{
			CGameObject* obj = CGame::GetObjByIndex(ui.widgetListObj->currentRow());
			obj->addComponent(actionRet->text().toAscii().data());
			Editor::SelectObj(obj);
		}

		CGame::EDTick();
	}
}

void Editor::slot_ObjectList_ItemChanged( QListWidgetItem* item )
{
	static QVector<char*> AllocatedStrs;
	const uint MAX_STR_LENGTH = 64;

	CGameObject* obj = CGame::GetObjByIndex(Instance->ui.widgetListObj->currentRow());

	for(auto itr = AllocatedStrs.begin(); itr != AllocatedStrs.end(); itr++)
	{
		if(*itr == obj->name)
		{
			strcpy((char*)obj->name, item->text().toAscii().data());
			return;
		}
	}

	char* str  = new char[MAX_STR_LENGTH];
	strcpy(str, item->text().toAscii().data());
	AllocatedStrs.push_back(str);
	obj->name = str;
}


void Editor::SelectObj( CGameObject* obj )
{
	Editor::SelectedObj = obj;
	Instance->ui.widgetPropertyBrowser->attachObj(obj);
	CGame::EDTick();
}

CGameObject* Editor::AddObj( float x, float y )
{
	auto obj = CGame::AddObject("object", x, y);
	Editor::SelectedObj = obj;

	QListWidgetItem* item = new QListWidgetItem("Object");
	item->setFlags( item->flags()  | Qt::ItemFlag::ItemIsEditable);
	Instance->ui.widgetListObj->addItem(item);
	Instance->ui.widgetListObj->setCurrentItem(item);

	Instance->ui.widgetPropertyBrowser->attachObj(obj);

	CGame::EDTick();
	return obj;
}

void Editor::SaveGame( cstr fileName )
{
	CGame::EDTick();
	CGame::Save(fileName);
}

void Editor::LoadGame( cstr filename )
{
	SelectObj(nullptr);
	Instance->ui.widgetListObj->clear();
	CGame::Load(filename);
	CGame::EDTick();
	CGameObject* obj = CGame::GetObjByIndex(0);
	while(obj)
	{
		QListWidgetItem* item = new QListWidgetItem(obj->name);
		item->setFlags( item->flags()  | Qt::ItemFlag::ItemIsEditable);
		Instance->ui.widgetListObj->addItem(item);

		obj = obj->getNext();
	}
	CGame::EDTick();
}
