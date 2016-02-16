#include "myqtui.h"

MyQTUI::MyQTUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.textEdit->append("REZA");
	ui.textEdit->append("I'm Indonesian");
}

MyQTUI::~MyQTUI()
{

}
