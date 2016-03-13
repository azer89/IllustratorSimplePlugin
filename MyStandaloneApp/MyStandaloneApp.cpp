

/**
* Reza Adhitya Saputra
* radhitya@uwaterloo.ca
* March 2016
*/


#include "stdafx.h"

//QT
#include <QTextEdit>
#include <iostream>
#include "myqtui.h"
#include <QtWidgets/QApplication>
#include "SystemParams.h"

/*
This is an entry main function
so I don't have to run Illustrator everytime 
when I need to debug my program
*/
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MyQTUI w;
	w.show();
	return a.exec();
}



