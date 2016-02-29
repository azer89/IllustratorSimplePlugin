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
	//ui.textEdit->append("MyQTUI OK");
	ui.widget->GetGLWidget()->textEdit = ui.textEdit;
}

MyQTUI::~MyQTUI()
{
}

// should delete this
void MyQTUI::Refresh()
{
	ui.widget->repaint();
	ui.widget->GetGLWidget()->repaint();
}

void MyQTUI::SendData(int width, int height, std::vector<QColor> colorList)
{
	ui.widget->GetGLWidget()->SetData(width, height, colorList);

	// I have a problem that when I set the image, 
	// OpenGL hasn't been initialized
	if (ui.widget->GetGLWidget()->IsInitialized())
		{ ui.widget->GetGLWidget()->SetImage(width, height, colorList); }
}

void MyQTUI::QtDisplayMessage(QString msg)
{
	ui.textEdit->append(msg);
}
