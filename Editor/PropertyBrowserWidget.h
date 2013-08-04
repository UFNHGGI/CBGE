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
#include <QVector>

#include <Engine.h>



#define PROPERTY_MIN_WIDTH			160
#define PROPERTY_MIN_HEIGHT			32
#define PROPERTY_CONTENT_MERGIN		2,2,8,2

//////////////////////////////////////////////////////////////////////////fwd decl
class CPropertyWidget;
class CPropertyPageWidget;
class CPropertyBrowserWidget;


class CPropertyBoolWidget;
class CPropertyIntWidget;
class CPropertyFloatWidget;
class CPropertyVec2Widget;
class CPropertyColorWidget;


class CPropertyCStrWidget : public QWidget
{
	Q_OBJECT

private:
	static QVector<char*> Strs;

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
			for(auto iter = Strs.begin(); iter != Strs.end(); iter++)
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
		Strs.push_back(strBuff);

SEC1:
		*m_var = strBuff;
		layout->addWidget(le);

		connect(le, SIGNAL(textChanged(const QString&)), this, SLOT(slot_textChange(const QString&)));
	}
};

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
		sb->setRange(INT_MIN, INT_MIN);
		sb->setValue(*varPtr);
		layout->addWidget(sb);
		
		connect(sb, SIGNAL(valueChanged(int)), this,  SLOT(slot_ValChanged(int)));
	}
};
class CPropertyFloatWidget : public QWidget
{
	Q_OBJECT

private:
	float*				m_var;

private slots :
	void slot_ValChanged(double val) { *m_var = val; CGame::EDTick(); }

public:
	CPropertyFloatWidget(float* varPtr)
	{
		m_var = varPtr;
		this->setMinimumSize(PROPERTY_MIN_WIDTH, PROPERTY_MIN_HEIGHT);
		
		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->setSpacing(4);
		layout->setContentsMargins(PROPERTY_CONTENT_MERGIN);

		auto dsb = new QDoubleSpinBox(this);
		dsb->setRange(-99999, 99999);
		dsb->setValue(*varPtr);
		layout->addWidget(dsb);

		connect(dsb, SIGNAL(valueChanged(double)), this,  SLOT(slot_ValChanged(double)));
	}
};

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


class CPropertyPageWidget : public QWidget
{
	Q_OBJECT

	QVector<CPropertyWidget*> properties;

	CPropertyIntWidget* addPropertyInt()
	{

	}
};


class CPropertyBrowserWidget : public QTreeView
{
	Q_OBJECT

public:
	QStandardItemModel*				m_model;
	CGameObject*					m_attechedObj;
	QVector<CPropertyPageWidget*>	m_pages;
	QStandardItem*					m_curItem;
	int								m_curGroupIndex;
	int								m_curPropertyIndex;

private slots:
	void slot_MenuRequested(const QPoint& p);

public:
	CPropertyBrowserWidget(QWidget* parent)
		: QTreeView(parent)
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

	~CPropertyBrowserWidget(void)
	{

	}


	void clearProperties();
	void attachObj(CGameObject* obj);

	
	void pushGroup(cstr name);
	void addProperty(cstr name, EComponentVarType varType, void* varAddress);
	void popGroup();
	
};

#endif	//__PROPERTYBROWSER_H__