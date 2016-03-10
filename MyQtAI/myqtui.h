#ifndef MYQTUI_H
#define MYQTUI_H

/**
* Reza Adhitya Saputra
* radhitya@uwaterloo.ca
*/

#include <QtWidgets/QMainWindow>
#include "ui_myqtui.h"

#include <vector>

#include "APath.h"

class MyQTUI : public QMainWindow
{
	Q_OBJECT

public:
	MyQTUI(QWidget *parent = 0);
	~MyQTUI();

	QTextEdit* GetTextEdit() { return ui.textEdit; }

	void SendData(int width, int height, std::vector<QColor> colorList);
	void SetPaths(std::vector<APath> paths);

	// delete this
	void Refresh();

private:
	Ui::MyQTUIClass ui;

private slots:
	void QtDisplayMessage(QString msg);

	void LoadFileAction();

	void SaveFileAction();
};

#endif // MYQTUI_H
