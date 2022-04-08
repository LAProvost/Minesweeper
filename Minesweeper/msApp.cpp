#include "msApp.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(msApp);

msApp::msApp()
{

}

msApp::~msApp()
{

}


bool msApp::OnInit()
{
	mainwindow = new MainWindow();
	mainwindow->Show();
	return true;
}
