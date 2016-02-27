#ifndef MYQTUI_H
#define MYQTUI_H

/**
* Reza Adhitya Saputra
* radhitya@uwaterloo.ca
*/

#include <QtWidgets/QMainWindow>
#include "ui_myqtui.h"

#include <vector>

class MyQTUI : public QMainWindow
{
	Q_OBJECT

public:
	MyQTUI(QWidget *parent = 0);
	~MyQTUI();

	QTextEdit* GetTextEdit() { return ui.textEdit; }

	void SendData(int width, int height, std::vector<QColor> colorList);

private:
	Ui::MyQTUIClass ui;

private slots:
	// display message
	void QtDisplayMessage(QString msg);
};

#endif // MYQTUI_H
