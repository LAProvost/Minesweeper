#pragma once
#include "wx/wx.h"

class MainWindow : public wxFrame
{
public:
	MainWindow();
	~MainWindow();

	void OnButtonClick(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();

public:
	int FieldWidth = 10;
	int FieldHeight = 10;
	wxButton** btn;
	int *Field = nullptr;
	bool bFirstClick = true;
};

