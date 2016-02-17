#ifndef MYQTUI_H
#define MYQTUI_H

#include <QtWidgets/QMainWindow>
#include "ui_myqtui.h"

class MyQTUI : public QMainWindow
{
	Q_OBJECT

public:
	MyQTUI(QWidget *parent = 0);
	~MyQTUI();

	QTextEdit* GetTextEdit() { return ui.textEdit; }

private:
	Ui::MyQTUIClass ui;

private slots:
	// display message
	void QtDisplayMessage(QString msg);
};

#endif // MYQTUI_H
