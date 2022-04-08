#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_BUTTON(100, OnButtonClick)
wxEND_EVENT_TABLE();

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Minesweeper", wxPoint(200, 200), wxSize(600, 400))
{
	btn = new wxButton*[FieldWidth * FieldHeight];
	wxGridSizer *grid = new wxGridSizer(FieldWidth, FieldHeight, 0, 0);

	Field = new int[FieldWidth * FieldHeight];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int x = 0; x < FieldWidth; x++)
	{
		for (int y = 0; y < FieldHeight; y++)
		{
			btn[y * FieldWidth + x] = new wxButton(this, 10000 + (y * FieldWidth + x));
			btn[y * FieldWidth + x]->SetFont(font);
			grid->Add(btn[y * FieldWidth + x], 1, wxEXPAND | wxALL);

			btn[y * FieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClick, this);
			Field[y * FieldWidth + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();
}

MainWindow::~MainWindow() 
{
	delete[] btn;
}

void MainWindow::OnButtonClick(wxCommandEvent& evt)
{
	//Get Coords of btn in field array
	int x = (evt.GetId() - 10000) % FieldWidth;
	int y = (evt.GetId() - 10000) / FieldWidth;

	if (bFirstClick)
	{
		int mines = 30;
		while (mines)
		{
			int rx = rand() % FieldWidth;
			int ry = rand() % FieldHeight;

			if (Field[ry*FieldWidth+rx]== 0 && rx != x && ry != y)
			{
				Field[ry * FieldWidth + rx] = -1;
				mines--;
			}
		}
		bFirstClick = false;
	}

	//Disable btn
	btn[y * FieldWidth + x]->Enable(false);

	//check if player hit mine
	if (Field[y * FieldWidth + x] == -1)
	{
		wxMessageBox("KABOOOOOOOM!! - GAME OVER -");

		//reset game
		bFirstClick = true;
		for (int x = 0; x < FieldWidth; x++)
		{
			for (int y = 0; y < FieldHeight; y++)
			{
				Field[y * FieldWidth + x] = 0;
				btn[y * FieldWidth + x]->SetLabel("");
				btn[y * FieldWidth + x]->Enable(true);
			}
		}
	}
	else
	{
		//count negihbouring mines
		int mine_count = 0;
		for (int h = -1; h < 2; h++)
		{
			for (int i = -1; i < 2; i++)
			{
				if (x + 1 >= 0 && x + h < FieldWidth && y + i >= 0 && y + i < FieldHeight)
				{
					if (Field[(y + i) * FieldWidth + (x + h)] == -1)
					{
						mine_count++;
					}
				}
			}
		}
		//update btns label to show mine count if > 0
		if (mine_count > 0)
		{
			btn[y * FieldWidth + x]->SetLabel(std::to_string(mine_count));
		}
	}

	evt.Skip();
}
