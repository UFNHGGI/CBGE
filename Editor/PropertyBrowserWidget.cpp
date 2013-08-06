#include "PropertyBrowserWidget.h"

#include "editor.h"

QVector<char*>		CPropertyCStrWidget::AllocatedStrs;

QListWidget*		CPropertyGameObjectWidget::TargetSelectionList	= nullptr;
QTreeWidget*		CPropertyComponentWidget::TargetSelectionList	= nullptr;


void CPropertyBrowserWidget::slot_MenuRequested( const QPoint& p )
{
	auto index = this->indexAt(p);
	QString indexStr = index.data().toString();
	if(index.column() == 0 && !index.parent().isValid() && indexStr != "Object")
	{
		QMenu menu;
		menu.addAction("Delete");
		if(menu.exec(this->mapToGlobal(p)))
			Editor::SelectedObj->getComponent(indexStr.toAscii().data())->destroy();

		Editor::SelectObj(Editor::SelectedObj);
		CGame::EDTick();
	}
}


void CPropertyBrowserWidget::attachObj( CGameObject* obj )
{
	clearProperties();
	m_attechedObj = obj;
	if(obj == nullptr)
		return;

	pushGroup("Object");
	addProperty("Active", EVT_BOOL, &obj->active);
	addProperty("Position", EVT_VEC2, &obj->position);
	addProperty("Size", EVT_VEC2, &obj->size);
	addProperty("Color", EVT_COLOR, &obj->color);
	addProperty("Rotation", EVT_FLOAT, &obj->rotation);
	popGroup();

	CComponent* c = obj->getComponentByIndex(0);
	while(c)
	{
		pushGroup(c->info()->className());
		for(uint i = 0; i < c->info()->varCount(); i++)
		{
			const SComponentVarInfo& var = c->info()->getVarInfo(i);
			if(var.showInEd)
				addProperty(var.varName, var.type, c->getVarAddress(i));
		}
		popGroup();
		c = c->getNext();
	}

	this->expandAll();
}

void CPropertyBrowserWidget::clearProperties()
{
	m_model->clear();
	m_model->setColumnCount(2);
	m_model->setHeaderData(0, Qt::Horizontal, "");
	m_model->setHeaderData(1, Qt::Horizontal, "");
	m_curPropertyIndex = 0;
	m_curGroupIndex = 0;
	m_attechedObj = nullptr;
}

void CPropertyBrowserWidget::pushGroup( cstr name )
{
	m_curItem = new QStandardItem(name);
	m_model->setItem(m_curGroupIndex, 0,  m_curItem);
	m_curItem->setEditable(false);
	m_curGroupIndex++;
}

void CPropertyBrowserWidget::popGroup()
{
	m_curItem = nullptr;
	m_curPropertyIndex = 0;
}

void CPropertyBrowserWidget::addProperty( cstr name, EComponentVarType varType, void* varAddress )
{
	auto itemVarName = new QStandardItem(name);
	itemVarName->setEditable(false);
	m_curItem->setChild(m_curPropertyIndex, 0, itemVarName);
	auto itemVarWidget = new QStandardItem();
	m_curItem->setChild(m_curPropertyIndex, 1, itemVarWidget);
	m_curPropertyIndex++;
	switch(varType)
	{
	case  EVT_BOOL:
		itemVarName->setToolTip("bool");
		setIndexWidget(itemVarWidget->index(), new CPropertyBoolWidget((bool*)varAddress));
		break;
	case EVT_CHAR:
		itemVarName->setToolTip("char");
		setIndexWidget(itemVarWidget->index(), new CPropertyCharWidget((char*)varAddress));
		break;
	case EVT_UCHAR:
		itemVarName->setToolTip("unsigned char");
		setIndexWidget(itemVarWidget->index(), new CPropertyUCharWidget((unsigned char*)varAddress));
		break;
	case EVT_SHORT:
		itemVarName->setToolTip("short");
		setIndexWidget(itemVarWidget->index(), new CPropertyShortWidget((short*)varAddress));
		break;
	case EVT_USHORT:
		itemVarName->setToolTip("unsigned short");
		setIndexWidget(itemVarWidget->index(), new CPropertyUShortWidget((unsigned short*)varAddress));
		break;
	case  EVT_INT:
		itemVarName->setToolTip("int");
		setIndexWidget(itemVarWidget->index(), new CPropertyIntWidget((int*)varAddress));
		break;
	case  EVT_UINT:
		itemVarName->setToolTip("unsigned int");
		setIndexWidget(itemVarWidget->index(), new CPropertyUIntWidget((unsigned int*)varAddress));
		break;
	case  EVT_LONG:
		itemVarName->setToolTip("long");
		setIndexWidget(itemVarWidget->index(), new CPropertyLongWidget((long*)varAddress));
		break;
	case  EVT_ULONG:
		itemVarName->setToolTip("unsigned long");
		setIndexWidget(itemVarWidget->index(), new CPropertyULongWidget((unsigned long*)varAddress));
		break;
	case  EVT_INT64:
		itemVarName->setToolTip("int64");
		setIndexWidget(itemVarWidget->index(), new CPropertyInt64Widget((long long*)varAddress));
		break;
	case  EVT_UINT64:
		itemVarName->setToolTip("uint64");
		setIndexWidget(itemVarWidget->index(), new CPropertyUInt64Widget((unsigned long long*)varAddress));
		break;
	case  EVT_FLOAT:
		itemVarName->setToolTip("float");
		setIndexWidget(itemVarWidget->index(), new CPropertyFloatWidget((float*)varAddress));
		break;
	case  EVT_DOUBLE:
		itemVarName->setToolTip("double");
		setIndexWidget(itemVarWidget->index(), new CPropertyDoubleWidget((double*)varAddress));
		break;
	case  EVT_VEC2:
		itemVarName->setToolTip("SVec2");
		setIndexWidget(itemVarWidget->index(), new CPropertyVec2Widget((SVec2*)varAddress));
		break;
	case  EVT_COLOR:
		itemVarName->setToolTip("SColor");
		setIndexWidget(itemVarWidget->index(), new CPropertyColorWidget((SColor*)varAddress));
		break;
	case  EVT_CSTR:
		itemVarName->setToolTip("cstr");
		setIndexWidget(itemVarWidget->index(), new CPropertyCStrWidget((cstr*)varAddress));
		break;
	case EVT_GAMEOBJECTPTR:
		itemVarName->setToolTip("CGameObject*");
		setIndexWidget(itemVarWidget->index(), new CPropertyGameObjectWidget((CGameObject**)varAddress));
		break;
	case EVT_COMPONENTPTR:
		itemVarName->setToolTip("CComponent*");
		setIndexWidget(itemVarWidget->index(), new CPropertyComponentWidget((CComponent**)varAddress));
		break;
	}
}

CPropertyBrowserWidget::CPropertyBrowserWidget( QWidget* parent ) : QTreeView(parent)
{
	m_curItem = nullptr;
	m_curGroupIndex = 0;
	m_curPropertyIndex = 0;

	m_model = new QStandardItemModel();
	m_model->setColumnCount(2);
	m_model->setHeaderData(0, Qt::Horizontal, "");
	m_model->setHeaderData(1, Qt::Horizontal, "");
	this->setModel(m_model);
	this->header()->setMovable(false);

	this->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
	this->connect(this, SIGNAL(customContextMenuRequested(const QPoint&))
		, this, SLOT(slot_MenuRequested(const QPoint&)));
}
