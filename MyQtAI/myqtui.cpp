
#include "myqtui.h"
#include "GLWidget.h"
#include "SystemParams.h"

#include <QFileDialog>

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

	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(SaveFileAction()));
	connect(ui.actionLoad, SIGNAL(triggered()), this, SLOT(LoadFileAction()));
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

void MyQTUI::SetPaths(std::vector<APath> paths)
{
	ui.widget->GetGLWidget()->SetPaths(paths);
	if (ui.widget->GetGLWidget()->IsInitialized())
	{
		ui.widget->GetGLWidget()->InitializePaths();
	}
}

void MyQTUI::SendData(int width, int height, std::vector<QColor> colorList)
{
	/*
	ui.widget->GetGLWidget()->SetData(width, height, colorList);

	// I have a problem that when I set the image, 
	// OpenGL hasn't been initialized
	if (ui.widget->GetGLWidget()->IsInitialized())
	{ 
		ui.widget->GetGLWidget()->SetImage(QString::fromStdString(SystemParams::temp_png_location));
	}
	*/
}

void MyQTUI::LoadFileAction()
{
	//std::cout << "LoadFileAction\n";

	QString qFilename = QFileDialog::getOpenFileName(this, "Open Path");
	if (qFilename.isEmpty()) { return; }
	std::string  strFilename = qFilename.toStdString();

	// LoadPath
	ui.widget->GetGLWidget()->LoadPath(strFilename);


}

void MyQTUI::SaveFileAction()
{
	//std::cout << "SaveFileAction\n";

	QString qFilename = QFileDialog::getSaveFileName(this, "Save Path");
	if (qFilename.isEmpty()) return;
	std::string saveFilename = qFilename.toStdString();


	ui.widget->GetGLWidget()->SaveCurrentPaths(saveFilename);
	//std::cout << saveFilename << "\n";
	//QtDisplayMessage(qFilename);

	
}

void MyQTUI::QtDisplayMessage(QString msg)
{
	ui.textEdit->append(msg);
}
