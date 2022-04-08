#pragma once
#include "wx/wx.h"

class MainWindow;

class msApp : public wxApp
{
private:
	MainWindow* mainwindow = nullptr;
public:
	msApp();
	~msApp();
	bool OnInit();
};

