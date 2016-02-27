#include "myqtui.h"
#include "GLWidget.h"

/**
* Reza Adhitya Saputra
* radhitya@uwaterloo.ca
*/

MyQTUI::MyQTUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.textEdit->append("MyQTUI OK");

	//ui.widget->GetGLWidget()->textEdit = ui.textEdit;
	//connect(ui.widget->GetGLWidget(), SIGNAL(QtSendMessage(QString)), this, SLOT(QtDisplayMessage(QString)));
}

MyQTUI::~MyQTUI()
{

}

void MyQTUI::SendData(int width, int height, std::vector<QColor> colorList)
{
	ui.textEdit->append("width :" + QString::number(width));
	ui.textEdit->append("height :" + QString::number(height));
	ui.textEdit->append("colorList size :" + QString::number(colorList.size()));

	ui.widget->GetGLWidget()->SetImage(width, height, colorList);
}

void MyQTUI::QtDisplayMessage(QString msg)
{
	ui.textEdit->append(msg);
}
