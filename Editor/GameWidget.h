#ifndef __CGAMEWIDGET_H__
#define __CGAMEWIDGET_H__

#include "PropertyBrowserWidget.h"

class CGameWidget : public QWidget
{
	Q_OBJECT

public:
	CGameWidget(QWidget* parent)
		: QWidget(parent)
	{
		CGame::EDInit(this->getDC());
		CGame::EDTick();

		setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
		connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(slot_menuRequest(const QPoint&)));
	}
	bool winEvent(MSG *message, long *result)
	{
		CGame::EDEvent(message);
		CGame::EDTick();
		return false;
	}

private slots:
	void slot_menuRequest(const QPoint& p);
};


#endif	//__CGAMEWIDGET_H__