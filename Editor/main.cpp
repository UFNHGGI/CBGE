#include "editor.h"
#include <QtGui/QApplication>
#include <QtGui/QPlastiqueStyle>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setStyle( new QPlastiqueStyle());
	Editor w;
	w.show();
	return a.exec();
}
