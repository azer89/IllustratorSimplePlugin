// MyStandaloneApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//QT
#include <QTextEdit>
#include <iostream>
#include "myqtui.h"
#include <QtWidgets/QApplication>
#include "SystemParams.h"



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MyQTUI w;
	w.show();
	return a.exec();
}



