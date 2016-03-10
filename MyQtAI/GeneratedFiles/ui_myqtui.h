/********************************************************************************
** Form generated from reading UI file 'myqtui.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYQTUI_H
#define UI_MYQTUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "GLContainer.h"

QT_BEGIN_NAMESPACE

class Ui_MyQTUIClass
{
public:
    QAction *actionSave;
    QAction *actionLoad;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTextEdit *textEdit;
    QListWidget *listWidget;
    GLContainer *widget;
    QMenuBar *menuBar;
    QMenu *menuFile;

    void setupUi(QMainWindow *MyQTUIClass)
    {
        if (MyQTUIClass->objectName().isEmpty())
            MyQTUIClass->setObjectName(QStringLiteral("MyQTUIClass"));
        MyQTUIClass->resize(1200, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MyQTUIClass->setWindowIcon(icon);
        MyQTUIClass->setAutoFillBackground(false);
        actionSave = new QAction(MyQTUIClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionLoad = new QAction(MyQTUIClass);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        centralWidget = new QWidget(MyQTUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setMaximumSize(QSize(250, 16777215));

        gridLayout->addWidget(textEdit, 1, 0, 1, 1);

        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setMaximumSize(QSize(250, 16777215));

        gridLayout->addWidget(listWidget, 0, 0, 1, 1);

        widget = new GLContainer(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setAutoFillBackground(false);

        gridLayout->addWidget(widget, 0, 1, 3, 1);

        MyQTUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MyQTUIClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1200, 31));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MyQTUIClass->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addAction(actionLoad);

        retranslateUi(MyQTUIClass);

        QMetaObject::connectSlotsByName(MyQTUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *MyQTUIClass)
    {
        MyQTUIClass->setWindowTitle(QApplication::translate("MyQTUIClass", "Awesome Window", 0));
        actionSave->setText(QApplication::translate("MyQTUIClass", "Save", 0));
        actionLoad->setText(QApplication::translate("MyQTUIClass", "Load", 0));
        menuFile->setTitle(QApplication::translate("MyQTUIClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MyQTUIClass: public Ui_MyQTUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYQTUI_H
