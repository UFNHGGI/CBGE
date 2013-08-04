#include "PropertyBrowserWidget.h"

#include "editor.h"

QVector<char*> CPropertyCStrWidget::Strs;




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
			addProperty(c->info()->getVarInfo(i).varName, c->info()->getVarInfo(i).type, c->getVarAddress(i));
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
	case  EVT_CSTR:
		itemVarName->setToolTip("cstr");
		setIndexWidget(itemVarWidget->index(), new CPropertyCStrWidget((cstr*)varAddress));
		break;
	case  EVT_INT:
		itemVarName->setToolTip("int");
		setIndexWidget(itemVarWidget->index(), new CPropertyIntWidget((int*)varAddress));
		break;
	case  EVT_FLOAT:
		itemVarName->setToolTip("float");
		setIndexWidget(itemVarWidget->index(), new CPropertyFloatWidget((float*)varAddress));
		break;
	case  EVT_VEC2:
		itemVarName->setToolTip("SVec2");
		setIndexWidget(itemVarWidget->index(), new CPropertyVec2Widget((SVec2*)varAddress));
		break;
	case  EVT_COLOR:
		itemVarName->setToolTip("SColor");
		setIndexWidget(itemVarWidget->index(), new CPropertyColorWidget((SColor*)varAddress));
		break;
	}
}
