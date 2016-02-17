#include "myqtui.h"

MyQTUI::MyQTUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.textEdit->append("MyQTUI OK");

	ui.widget->GetGLWidget()->textEdit = ui.textEdit;
	//connect(ui.widget->GetGLWidget(), SIGNAL(QtSendMessage(QString)), this, SLOT(QtDisplayMessage(QString)));
}

MyQTUI::~MyQTUI()
{

}

void MyQTUI::QtDisplayMessage(QString msg)
{
	ui.textEdit->append(msg);
}
