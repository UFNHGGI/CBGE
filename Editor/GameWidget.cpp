#include "GameWidget.h"

#include <QtGui/QFileDialog>

#include "editor.h";

void CGameWidget::slot_menuRequest( const QPoint& p )
{
	QMenu menu;
	QAction* actionAddObj = menu.addAction("Add Object Here");
	QAction* actionPlay = menu.addAction("Play");
	QAction* actionSave = menu.addAction("Save");
	QAction* actionLoad = menu.addAction("Load");
	QAction* retAction = menu.exec(this->mapToGlobal(p));

	if(retAction == actionAddObj)
	{
		Editor::AddObj(p.x(), p.y());
	}
	else if(retAction == actionPlay)
	{
		CGame::EDTick();
		CGame::Save("tmp.game");
		ShellExecuteA(nullptr, nullptr, "launcher.exe", "tmp.game", nullptr, SW_SHOW);
	}
	else if(retAction == actionSave)
	{
		QString ret = QFileDialog::getSaveFileName(nullptr, "Save", nullptr, "*.game");
		if(!ret.isNull())
			Editor::SaveGame(ret.toAscii().data());
	}
	else if(retAction == actionLoad)
	{
		QString ret = QFileDialog::getOpenFileName(nullptr, "Load", nullptr, "*.game");
		if(!ret.isNull())
			Editor::LoadGame(ret.toAscii().data());
	}
}
