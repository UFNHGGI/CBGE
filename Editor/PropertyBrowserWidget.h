#ifndef __PROPERTYBROWSER_H__
#define __PROPERTYBROWSER_H__


#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QToolBox>
#include <QtGui/QMainWindow>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeView>
#include <QtGui/QStandardItem>
#include <QtGui/QStandardItemModel>
#include <QtGui/QHeaderView>
#include <QtGui/QCheckBox>
#include <QtGui/QLineEdit>
#include <QtGui/QMenu>
#include <QtGui/QAction>
#include <QtGui/QToolButton>
#include <QtGui/QCommandLinkButton>
#include <QtGui/QListWidget>
#include <QtGui/QTreeWidget>
#include <QVector>

#include <Engine.h>



#define PROPERTY_MIN_WIDTH			160
#define PROPERTY_MIN_HEIGHT			32
#define PROPERTY_CONTENT_MERGIN		2,2,8,2

//////////////////////////////////////////////////////////////////////////fwd decl
class CPropertyBoolWidget;
class CPropertyCharWidget;
class CPropertyUCharWidget;
class CPropertyShortWidget;
class CPropertyUShortWidget;
class CPropertyIntWidget;
class CPropertyUIntWidget;
class CPropertyLongWidget;
class CPropertyULongWidget;
class CPropertyInt64Widget;
class CPropertyUInt64Widget;
class CPropertyFloatWidget;
class CPropertyDoubleWidget;
class CPropertyVec2Widget;
class CPropertyColorWidget;
class CPropertyCStrWidget;
class CPropertyGameObjectWidget;
class CPropertyComponentWidget;

class CPropertyBrowserWidget;



//////////////////////////////////////////////////////////////////////////CPropertyBoolWidget
class CPropertyBoolWidget : public QWidget
{
	Q_OBJECT
private:
	bool* m_var;

private slots :
		void slot_stateChanged(int i)
		{
			*m_var = (i == Qt::Checked);
			CGame::EDTick();
		}

public:
	CPropertyBoolWidget(bool* varPtr)
	{
		m_var = varPtr;
		this->setMinimumSize(PROPERTY_MIN_WIDTH, PROPERTY_MIN_HEIGHT);
		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setSpacing(4);
		layout->setContentsMargins(PROPERTY_CONTENT_MERGIN);

		auto chb = new QCheckBox(this);
		chb->setChecked(*varPtr);
		layout->addWidget(chb);

		connect(chb, SIGNAL(stateChanged(int)), this, SLOT(slot_stateChanged(int)));
	}
};


//////////////////////////////////////////////////////////////////////////CPropertyCharWidget
class CPropertyCharWidget : public QWidget
{
	Q_OBJECT

private:
	char*		m_var;

private slots :
	void slot_ValChanged(int val) { *m_var = (char)val; CGame::EDTick(); }

public:
	CPropertyCharWidget(char* varPtr)
	{
		m_var = varPtr;
		this->setMinimumSize(PROPERTY_MIN_WIDTH, PROPERTY_MIN_HEIGHT);

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setSpacing(4);
		layout->setContentsMargins(PROPERTY_CONTENT_MERGIN);

		auto sb = new QSpinBox(this);
		sb->setRange(CHAR_MIN, CHAR_MAX);
		sb->setValue(*varPtr);
		layout->addWidget(sb);

		connect(sb, SIGNAL(valueChanged(int)), this, SLOT(slot_ValChanged(int)));
	}
};


//////////////////////////////////////////////////////////////////////////CPropertyUCharWidget
class CPropertyUCharWidget : public QWidget
{
	Q_OBJECT

private:
	unsigned char*		m_var;

	private slots :
		void slot_ValChanged(int val) { *m_var = (unsigned char)val; CGame::EDTick(); }

public:
	CPropertyUCharWidget(unsigned char* varPtr)
	{
		m_var = varPtr;
		this->setMinimumSize(PROPERTY_MIN_WIDTH, PROPERTY_MIN_HEIGHT);

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setSpacing(4);
		layout->setContentsMargins(PROPERTY_CONTENT_MERGIN);

		auto sb = new QSpinBox(this);
		sb->setRange(0, 0xFF);
		sb->setValue(*varPtr);
		layout->addWidget(sb);

		connect(sb, SIGNAL(valueChanged(int)), this, SLOT(slot_ValChanged(int)));
	}
};


//////////////////////////////////////////////////////////////////////////CPropertyShortWidget
class CPropertyShortWidget : public QWidget
{
	Q_OBJECT

private:
	short*		m_var;

private slots :
		void slot_ValChanged(int val) { *m_var = (short)val; CGame::EDTick(); }

public:
	CPropertyShortWidget(short* varPtr)
	{
		m_var = varPtr;
		this->setMinimumSize(PROPERTY_MIN_WIDTH, PROPERTY_MIN_HEIGHT);

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setSpacing(4);
		layout->setContentsMargins(PROPERTY_CONTENT_MERGIN);

		auto sb = new QSpinBox(this);
		sb->setRange(-32768, 32767);
		sb->setValue(*varPtr);
		layout->addWidget(sb);

		connect(sb, SIGNAL(valueChanged(int)), this, SLOT(slot_ValChanged(int)));
	}
};


//////////////////////////////////////////////////////////////////////////CPropertyUShortWidget
class CPropertyUShortWidget : public QWidget
{
	Q_OBJECT

private:
	unsigned short*		m_var;

	private slots :
		void slot_ValChanged(int val) { *m_var = (unsigned short)val; CGame::EDTick(); }

public:
	CPropertyUShortWidget(unsigned short* varPtr)
	{
		m_var = varPtr;
		this->setMinimumSize(PROPERTY_MIN_WIDTH, PROPERTY_MIN_HEIGHT);

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setSpacing(4);
		layout->setContentsMargins(PROPERTY_CONTENT_MERGIN);

		auto sb = new QSpinBox(this);
		sb->setRange(0, 0xFFFF);
		sb->setValue(*varPtr);
		layout->addWidget(sb);

		connect(sb, SIGNAL(valueChanged(int)), this, SLOT(slot_ValChanged(int)));
	}
};


//////////////////////////////////////////////////////////////////////////CPropertyIntWidget
class CPropertyIntWidget : public QWidget
{
	Q_OBJECT

private:
	int*		m_var;

	private slots :
		void slot_ValChanged(int val) { *m_var = val; CGame::EDTick(); }

public:
	CPropertyIntWidget(int* varPtr)
	{
		m_var = varPtr;
		this->setMinimumSize(PROPERTY_MIN_WIDTH, PROPERTY_MIN_HEIGHT);

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setSpacing(4);
		layout->setContentsMargins(PROPERTY_CONTENT_MERGIN);

		auto sb = new QSpinBox(this);
		sb->setRange(INT_MIN, INT_MAX);
		sb->setValue(*varPtr);
		layout->addWidget(sb);

		connect(sb, SIGNAL(valueChanged(int)), this,  SLOT(slot_ValChanged(int)));
	}
};


//////////////////////////////////////////////////////////////////////////CPropertyUIntWidget
class CPropertyUIntWidget : public QWidget
{
	Q_OBJECT

private:
	unsigned int*		m_var;

	private slots :
		void slot_ValChanged(int val) { *m_var = (unsigned int)val; CGame::EDTick(); }

public:
	CPropertyUIntWidget(unsigned int* varPtr)
	{
		m_var = varPtr;
		this->setMinimumSize(PROPERTY_MIN_WIDTH, PROPERTY_MIN_HEIGHT);

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setSpacing(4);
		layout->setContentsMargins(PROPERTY_CONTENT_MERGIN);

		auto sb = new QSpinBox(this);
		sb->setRange(0, INT_MAX);
		sb->setValue(*varPtr);
		layout->addWidget(sb);

		connect(sb, SIGNAL(valueChanged(int)), this,  SLOT(slot_ValChanged(int)));
	}
};


//////////////////////////////////////////////////////////////////////////CPropertyLongWidget
class CPropertyLongWidget : public QWidget
{
	Q_OBJECT

private:
	long*		m_var;

	private slots :
		void slot_ValChanged(int val) { *m_var = (long)val; CGame::EDTick(); }

public:
	CPropertyLongWidget(long* varPtr)
	{
		m_var = varPtr;
		this->setMinimumSize(PROPERTY_MIN_WIDTH, PROPERTY_MIN_HEIGHT);

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setSpacing(4);
		layout->setContentsMargins(PROPERTY_CONTENT_MERGIN);

		auto sb = new QSpinBox(this);
		sb->setRange(INT_MIN, INT_MAX);
		sb->setValue(*varPtr);
		layout->addWidget(sb);

		connect(sb, SIGNAL(valueChanged(int)), this,  SLOT(slot_ValChanged(int)));
	}
};


//////////////////////////////////////////////////////////////////////////CPropertyULongWidget
class CPropertyULongWidget : public QWidget
{
	Q_OBJECT

private:
	unsigned long*		m_var;

	private slots :
		void slot_ValChanged(int val) { *m_var = (unsigned long)val; CGame::EDTick(); }

public:
	CPropertyULongWidget(unsigned long* varPtr)
	{
		m_var = varPtr;
		this->setMinimumSize(PROPERTY_MIN_WIDTH, PROPERTY_MIN_HEIGHT);

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setSpacing(4);
		layout->setContentsMargins(PROPERTY_CONTENT_MERGIN);

		auto sb = new QSpinBox(this);
		sb->setRange(0, INT_MAX);
		sb->setValue(*varPtr);
		layout->addWidget(sb);

		connect(sb, SIGNAL(valueChanged(int)), this,  SLOT(slot_ValChanged(int)));
	}
};


//////////////////////////////////////////////////////////////////////////CPropertyInt64Widget
class CPropertyInt64Widget : public QWidget
{
	Q_OBJECT

private:
	long long*		m_var;

	private slots :
		void slot_ValChanged(int val) { *m_var = (long long)val; CGame::EDTick(); }

public:
	CPropertyInt64Widget(long long* varPtr)
	{
		m_var = varPtr;
		this->setMinimumSize(PROPERTY_MIN_WIDTH, PROPERTY_MIN_HEIGHT);

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setSpacing(4);
		layout->setContentsMargins(PROPERTY_CONTENT_MERGIN);

		//@Replace Int64SpinBox
		auto sb = new QSpinBox(this);
		sb->setRange(INT_MIN, INT_MAX);
		sb->setValue(*varPtr);
		layout->addWidget(sb);

		connect(sb, SIGNAL(valueChanged(int)), this,  SLOT(slot_ValChanged(int)));
	}
};


//////////////////////////////////////////////////////////////////////////CPropertyInt64Widget
class CPropertyUInt64Widget : public QWidget
{
	Q_OBJECT

private:
	unsigned long long*		m_var;

	private slots :
		void slot_ValChanged(int val) { *m_var = (unsigned long long)val; CGame::EDTick(); }

public:
	CPropertyUInt64Widget(unsigned long long* varPtr)
	{
		m_var = varPtr;
		this->setMinimumSize(PROPERTY_MIN_WIDTH, PROPERTY_MIN_HEIGHT);

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setSpacing(4);
		layout->setContentsMargins(PROPERTY_CONTENT_MERGIN);

		//@Replace Int64SpinBox
		auto sb = new QSpinBox(this);
		sb->setRange(0, INT_MAX);
		sb->setValue(*varPtr);
		layout->addWidget(sb);

		connect(sb, SIGNAL(valueChanged(int)), this,  SLOT(slot_ValChanged(int)));
	}
};


//////////////////////////////////////////////////////////////////////////CPropertyFloatWidget
class CPropertyFloatWidget : public QWidget
{
	Q_OBJECT

private:
	float*				m_var;

	private slots :
		void slot_ValChanged(double val) { *m_var = (float)val; CGame::EDTick(); }

public:
	CPropertyFloatWidget(float* varPtr)
	{
		m_var = varPtr;
		this->setMinimumSize(PROPERTY_MIN_WIDTH, PROPERTY_MIN_HEIGHT);

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setSpacing(4);
		layout->setContentsMargins(PROPERTY_CONTENT_MERGIN);

		auto dsb = new QDoubleSpinBox(this);
		dsb->setRange(-999999, 999999);
		dsb->setValue(*varPtr);
		layout->addWidget(dsb);

		connect(dsb, SIGNAL(valueChanged(double)), this,  SLOT(slot_ValChanged(double)));
	}
};


//////////////////////////////////////////////////////////////////////////CPropertyDoubleWidget
class CPropertyDoubleWidget : public QWidget
{
	Q_OBJECT

private:
	double*				m_var;

private slots :
		void slot_ValChanged(double val) { *m_var = val; CGame::EDTick(); }

public:
	CPropertyDoubleWidget(double* varPtr)
	{
		m_var = varPtr;
		this->setMinimumSize(PROPERTY_MIN_WIDTH, PROPERTY_MIN_HEIGHT);

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setSpacing(4);
		layout->setContentsMargins(PROPERTY_CONTENT_MERGIN);

		auto dsb = new QDoubleSpinBox(this);
		dsb->setRange(-999999999, 999999999);
		dsb->setValue(*varPtr);
		layout->addWidget(dsb);

		connect(dsb, SIGNAL(valueChanged(double)), this,  SLOT(slot_ValChanged(double)));
	}
};


//////////////////////////////////////////////////////////////////////////CPropertyVec2Widget
class CPropertyVec2Widget : public QWidget
{
	Q_OBJECT

private:
	SVec2*				m_var;

	private slots :
		void slot_ValXChanged(double val) { m_var->x = val; CGame::EDTick(); }
		void slot_ValYChanged(double val) { m_var->y = val; CGame::EDTick(); }

public:
	CPropertyVec2Widget(SVec2* varPtr)
	{
		m_var = varPtr;
		this->setMinimumSize(PROPERTY_MIN_WIDTH, PROPERTY_MIN_HEIGHT);

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setSpacing(4);
		layout->setContentsMargins(PROPERTY_CONTENT_MERGIN);

		auto dsbX = new QDoubleSpinBox(this);
		dsbX->setRange(-99999, 99999);
		dsbX->setValue(varPtr->x);
		dsbX->setToolTip("X");
		layout->addWidget(dsbX);


		auto dsbY = new QDoubleSpinBox(this);
		dsbY->setRange(-99999, 99999);
		dsbY->setValue(varPtr->y);
		dsbY->setToolTip("Y");
		layout->addWidget(dsbY);

		connect(dsbX, SIGNAL(valueChanged(double)), this, SLOT(slot_ValXChanged(double)));
		connect(dsbY, SIGNAL(valueChanged(double)), this, SLOT(slot_ValYChanged(double)));
	}
};


//////////////////////////////////////////////////////////////////////////CPropertyColorWidget
class CPropertyColorWidget : public QWidget
{
	Q_OBJECT

private:
	SColor*			m_var;

	private slots :
		void slot_ValRChanged(double val) { m_var->r = val; CGame::EDTick(); }
		void slot_ValGChanged(double val) { m_var->g = val; CGame::EDTick(); }
		void slot_ValBChanged(double val) { m_var->b = val; CGame::EDTick(); }

public:
	CPropertyColorWidget(SColor* varPtr)
	{
		m_var = varPtr;
		this->setMinimumSize(PROPERTY_MIN_WIDTH, PROPERTY_MIN_HEIGHT);

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setSpacing(4);
		layout->setContentsMargins(PROPERTY_CONTENT_MERGIN);

		auto dsbR = new QDoubleSpinBox(this);
		dsbR->setRange(0.0, 1.0);
		dsbR->setSingleStep(0.01);
		dsbR->setDecimals(3);
		dsbR->setValue(varPtr->r);
		dsbR->setToolTip("R");
		layout->addWidget(dsbR);


		auto dsbG = new QDoubleSpinBox(this);
		dsbG->setRange(0.0, 1.0);
		dsbG->setSingleStep(0.01);
		dsbG->setValue(varPtr->g);
		dsbG->setDecimals(3);
		dsbG->setToolTip("G");
		layout->addWidget(dsbG);

		auto dsbB = new QDoubleSpinBox(this);
		dsbB->setRange(0.0, 1.0);
		dsbB->setSingleStep(0.01);
		dsbB->setValue(varPtr->b);
		dsbB->setDecimals(3);
		dsbB->setToolTip("B");
		layout->addWidget(dsbB);

		connect(dsbR, SIGNAL(valueChanged(double)), this, SLOT(slot_ValRChanged(double)));
		connect(dsbG, SIGNAL(valueChanged(double)), this, SLOT(slot_ValGChanged(double)));
		connect(dsbB, SIGNAL(valueChanged(double)), this, SLOT(slot_ValBChanged(double)));
	}
};


//////////////////////////////////////////////////////////////////////////CPropertyCStrWidget
class CPropertyCStrWidget : public QWidget
{
	Q_OBJECT

private:
	static QVector<char*> AllocatedStrs;

	cstr*	m_var;
	char*	strBuff;

private slots :
	void slot_textChange(const QString& str)
	{
		strcpy(strBuff, str.toAscii().data());
	}

public:
	CPropertyCStrWidget(cstr* varPtr)
	{
		m_var = varPtr;
		this->setMinimumSize(PROPERTY_MIN_WIDTH, PROPERTY_MIN_HEIGHT);
		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setSpacing(4);
		layout->setContentsMargins(PROPERTY_CONTENT_MERGIN);

		auto le = new QLineEdit(this);
		le->setMaxLength(63);

		if(*varPtr)
		{
			le->setText(*varPtr);
			for(auto iter = AllocatedStrs.begin(); iter != AllocatedStrs.end(); iter++)
			{
				if(*iter == *varPtr)
				{
					strBuff = *iter;
					strcpy(strBuff, *varPtr);
					goto SEC1;
				}
			}
		}


		strBuff = new char[64];
		strBuff[0] = '\0';
		AllocatedStrs.push_back(strBuff);

SEC1:
		*m_var = strBuff;
		layout->addWidget(le);

		connect(le, SIGNAL(textChanged(const QString&)), this, SLOT(slot_textChange(const QString&)));
	}
};


//////////////////////////////////////////////////////////////////////////CPropertyGameObjectWidget
class CPropertyGameObjectWidget : public QWidget
{
	Q_OBJECT

private:
	CGameObject**			m_var;
	QCommandLinkButton*		m_btn;

	static QListWidget*		TargetSelectionList;
	

private slots :
		void slot_pressed()
		{
			if(TargetSelectionList == nullptr)
			{
				TargetSelectionList = new QListWidget;
				TargetSelectionList->setWindowTitle("Select Object");
				TargetSelectionList->setWindowOpacity(0.95f);
			}

			TargetSelectionList->clear();
			TargetSelectionList->disconnect(this);
			connect(TargetSelectionList, SIGNAL(itemClicked ( QListWidgetItem * ))
				, this, SLOT(slot_selectionListItemClicked(QListWidgetItem*)));

			TargetSelectionList->addItem("null");
			auto obj = CGame::GetObjByIndex(0);
			while(obj)
			{
				TargetSelectionList->addItem(obj->name);
				obj = obj->getNext();
			}
			TargetSelectionList->show();

		}

		void slot_selectionListItemClicked ( QListWidgetItem * item )
		{
			if(item->listWidget()->currentRow() == 0)
			{
				m_btn->setText("null");
				*m_var = nullptr;
			}
			else	//null selected
			{
				m_btn->setText(item->text());
				*m_var = CGame::GetObjByIndex(item->listWidget()->currentRow()-1);
			}
			item->listWidget()->close();
		}

public:
	CPropertyGameObjectWidget(CGameObject** varPtr)
	{
		this->setMinimumSize(PROPERTY_MIN_WIDTH, PROPERTY_MIN_HEIGHT);
		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setSpacing(4);
		layout->setContentsMargins(PROPERTY_CONTENT_MERGIN);

		m_btn = new QCommandLinkButton(this);
		layout->addWidget(m_btn);
		connect(m_btn, SIGNAL(pressed()), this, SLOT(slot_pressed()));

		m_var = varPtr;
		if(CGameObject::Exist(*varPtr))
		{
			m_btn->setText((*varPtr)->name);
		}
		else
		{
			*m_var = nullptr;
			m_btn->setText("null");
		}
	}
};


//////////////////////////////////////////////////////////////////////////CPropertyComponentWidget
class CPropertyComponentWidget : public QWidget
{
	Q_OBJECT

private:
	CComponent**			m_var;
	QCommandLinkButton*		m_btn;

	static QTreeWidget*		TargetSelectionList;

private slots:
		void slot_pressed()
		{
			if(TargetSelectionList == nullptr)
			{
				TargetSelectionList = new QTreeWidget;
				TargetSelectionList->setWindowTitle("Select Component");
				TargetSelectionList->setWindowOpacity(0.95f);
				TargetSelectionList->setHeaderHidden(true);
			}
			
			TargetSelectionList->clear();
			TargetSelectionList->disconnect(this);
			connect(TargetSelectionList, SIGNAL(itemClicked(QTreeWidgetItem*, int))
				, this, SLOT(slot_selectionListItemClicked (QTreeWidgetItem*, int)));


			QTreeWidgetItem* itemNull = new QTreeWidgetItem();
			itemNull->setText(0,"null");
			TargetSelectionList->addTopLevelItem(itemNull);


			/////////////////fill widget
			CGameObject* obj = CGame::GetObjByIndex(0);
			while(obj)
			{
				CComponent* comp = obj->getComponentByIndex(0);
				QTreeWidgetItem* item = new QTreeWidgetItem();
				item->setText(0,obj->name);
				item->setFlags(Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemIsUserCheckable);
				TargetSelectionList->addTopLevelItem(item);

				while(comp)
				{
					QTreeWidgetItem* childItem = new QTreeWidgetItem();
					childItem->setText(0,comp->info()->className());
					item->addChild(childItem);
					comp = comp->getNext();
				}
				obj = obj->getNext();
			}


			TargetSelectionList->expandAll();
			TargetSelectionList->show();
		}

		void slot_selectionListItemClicked ( QTreeWidgetItem * item, int column )
		{
			QModelIndex curIndex = item->treeWidget()->currentIndex();
			if(curIndex.parent().isValid()) //component selected?
			{
				CComponent* comp = CGame::GetObjByIndex(curIndex.parent().row()-1)->getComponentByIndex(curIndex.row());
				static QString Text;
				Text.clear();
				Text = comp->owner()->name;
				Text += "   ";
				Text += comp->info()->className();
				m_btn->setText(Text);
				*m_var = comp;
				item->treeWidget()->close();
			}
			else if(curIndex.row() == 0)	//null selected
			{
				m_btn->setText("null");
				*m_var = nullptr;
				item->treeWidget()->close();
			}
		}

public:
	CPropertyComponentWidget(CComponent** varPtr)
	{
		this->setMinimumSize(PROPERTY_MIN_WIDTH, PROPERTY_MIN_HEIGHT);
		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setSpacing(4);
		layout->setContentsMargins(PROPERTY_CONTENT_MERGIN);

		m_btn = new QCommandLinkButton(this);
		layout->addWidget(m_btn);
		connect(m_btn, SIGNAL(pressed()), this, SLOT(slot_pressed()));

		m_var = varPtr;
		if(CComponent::Exist(*varPtr))
		{
			m_var = varPtr;
			static QString Text;
			Text.clear();
			Text = (*m_var)->owner()->name;
			Text += "   ";
			Text += (*m_var)->info()->className();
			m_btn->setText(Text);
			
		}
		else
		{
			*m_var = nullptr;
			m_btn->setText("null");
		}
	}
};




//////////////////////////////////////////////////////////////////////////CPropertyBrowserWidget
class CPropertyBrowserWidget : public QTreeView
{
	Q_OBJECT

public:
	QStandardItemModel*				m_model;
	CGameObject*					m_attechedObj;
	QStandardItem*					m_curItem;
	int								m_curGroupIndex;
	int								m_curPropertyIndex;

private slots:
	void slot_MenuRequested(const QPoint& p);

public:
	CPropertyBrowserWidget(QWidget* parent);


	void clearProperties();
	void attachObj(CGameObject* obj);

	
	void pushGroup(cstr name);
	void addProperty(cstr name, EComponentVarType varType, void* varAddress);
	void popGroup();
	
};

#endif	//__PROPERTYBROWSER_H__