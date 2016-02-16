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
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyQTUIClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QWidget *widget;
    QTextEdit *textEdit;

    void setupUi(QMainWindow *MyQTUIClass)
    {
        if (MyQTUIClass->objectName().isEmpty())
            MyQTUIClass->setObjectName(QStringLiteral("MyQTUIClass"));
        MyQTUIClass->resize(1200, 600);
        MyQTUIClass->setAutoFillBackground(false);
        centralWidget = new QWidget(MyQTUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setAutoFillBackground(false);

        gridLayout->addWidget(widget, 0, 1, 1, 1);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);
        textEdit->setMinimumSize(QSize(300, 0));
        textEdit->setMaximumSize(QSize(300, 16777215));
        QFont font;
        font.setFamily(QStringLiteral("Courier New"));
        font.setPointSize(7);
        textEdit->setFont(font);
        textEdit->setReadOnly(true);

        gridLayout->addWidget(textEdit, 0, 0, 1, 1);

        MyQTUIClass->setCentralWidget(centralWidget);

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
