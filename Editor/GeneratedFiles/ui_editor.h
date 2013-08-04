/********************************************************************************
** Form generated from reading UI file 'editor.ui'
**
** Created: Mon Aug 5 00:03:04 2013
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITOR_H
#define UI_EDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "gamewidget.h"
#include "propertybrowserwidget.h"

QT_BEGIN_NAMESPACE

class Ui_EditorClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    CGameWidget *widgetGame;
    QMenuBar *menuBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget_3;
    QWidget *dockWidgetContents_3;
    QHBoxLayout *horizontalLayout;
    CPropertyBrowserWidget *widgetPropertyBrowser;
    QDockWidget *dockWidget_4;
    QWidget *dockWidgetContents_4;
    QVBoxLayout *verticalLayout;
    QListWidget *widgetListObj;

    void setupUi(QMainWindow *EditorClass)
    {
        if (EditorClass->objectName().isEmpty())
            EditorClass->setObjectName(QString::fromUtf8("EditorClass"));
        EditorClass->resize(888, 542);
        EditorClass->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(EditorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widgetGame = new CGameWidget(centralWidget);
        widgetGame->setObjectName(QString::fromUtf8("widgetGame"));
        widgetGame->setMinimumSize(QSize(480, 400));

        verticalLayout_2->addWidget(widgetGame);

        EditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EditorClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 888, 21));
        EditorClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(EditorClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setSizeGripEnabled(true);
        EditorClass->setStatusBar(statusBar);
        dockWidget_3 = new QDockWidget(EditorClass);
        dockWidget_3->setObjectName(QString::fromUtf8("dockWidget_3"));
        dockWidget_3->setMinimumSize(QSize(260, 300));
        dockWidget_3->setStyleSheet(QString::fromUtf8(""));
        dockWidget_3->setFloating(false);
        dockWidget_3->setFeatures(QDockWidget::DockWidgetMovable);
        dockWidget_3->setAllowedAreas(Qt::AllDockWidgetAreas);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
        horizontalLayout = new QHBoxLayout(dockWidgetContents_3);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widgetPropertyBrowser = new CPropertyBrowserWidget(dockWidgetContents_3);
        widgetPropertyBrowser->setObjectName(QString::fromUtf8("widgetPropertyBrowser"));

        horizontalLayout->addWidget(widgetPropertyBrowser);

        dockWidget_3->setWidget(dockWidgetContents_3);
        EditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_3);
        dockWidget_4 = new QDockWidget(EditorClass);
        dockWidget_4->setObjectName(QString::fromUtf8("dockWidget_4"));
        dockWidget_4->setMinimumSize(QSize(160, 200));
        dockWidget_4->setFeatures(QDockWidget::DockWidgetMovable);
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QString::fromUtf8("dockWidgetContents_4"));
        verticalLayout = new QVBoxLayout(dockWidgetContents_4);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widgetListObj = new QListWidget(dockWidgetContents_4);
        widgetListObj->setObjectName(QString::fromUtf8("widgetListObj"));

        verticalLayout->addWidget(widgetListObj);

        dockWidget_4->setWidget(dockWidgetContents_4);
        EditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_4);

        retranslateUi(EditorClass);

        QMetaObject::connectSlotsByName(EditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *EditorClass)
    {
        EditorClass->setWindowTitle(QApplication::translate("EditorClass", "Editor", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        widgetGame->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
    } // retranslateUi

};

namespace Ui {
    class EditorClass: public Ui_EditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITOR_H
