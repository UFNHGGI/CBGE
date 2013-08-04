#ifndef EDITOR_H
#define EDITOR_H

#include <QtGui/QMainWindow>
#include "ui_editor.h"

#include <Engine.h>

class Editor : public QMainWindow
{
	Q_OBJECT

public:
	Editor(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Editor();

private:
	Ui::EditorClass ui;

	static Editor* Instance;

public:
	static CGameObject*		SelectedObj;

	static void			SelectObj(CGameObject* obj);

	static CGameObject*	AddObj(float x, float y);
	static void			SaveGame(cstr fileName);
	static void			LoadGame(cstr filename);

private slots:
	void slot_objList_ItemClicked ( QListWidgetItem * item );
	void slot_objList_MenuRequest(const QPoint& p);
	void slot_objList_ItemChanged(QListWidgetItem* item);


};

#endif // EDITOR_H
