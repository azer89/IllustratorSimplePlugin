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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyQTUIClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MyQTUIClass)
    {
        if (MyQTUIClass->objectName().isEmpty())
            MyQTUIClass->setObjectName(QStringLiteral("MyQTUIClass"));
        MyQTUIClass->resize(750, 624);
        centralWidget = new QWidget(MyQTUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        gridLayout->addWidget(textEdit, 0, 0, 1, 1);

        MyQTUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MyQTUIClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 750, 26));
        MyQTUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyQTUIClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MyQTUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MyQTUIClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MyQTUIClass->setStatusBar(statusBar);

        retranslateUi(MyQTUIClass);

        QMetaObject::connectSlotsByName(MyQTUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *MyQTUIClass)
    {
        MyQTUIClass->setWindowTitle(QApplication::translate("MyQTUIClass", "Awesome Window", 0));
    } // retranslateUi

};

namespace Ui {
    class MyQTUIClass: public Ui_MyQTUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYQTUI_H
