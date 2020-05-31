#include <wx/display.h>
#include <iostream>
#include "Main.h"


#define APP_WIDTH 200
#define APP_HEIGHT 100


Main::Main(std::string appName) : wxFrame(nullptr, wxID_ANY, appName)
{
  // Init window
  wxDisplay display(wxDisplay::GetFromWindow(this));
  wxRect screen = display.GetClientArea();
  this->SetInitialSize(wxSize(APP_WIDTH, APP_HEIGHT));
  this->SetPosition(wxPoint(screen.width / 2 - APP_WIDTH / 2, screen.height / 2 - APP_HEIGHT / 2));
  // Disable maximize button & disable window resizing
  this->SetWindowStyle(this->GetWindowStyle() & ~(wxMAXIMIZE_BOX | wxRESIZE_BORDER));
  this->SetIcon(wxICON(MAIN_ICON));

}

Main::~Main()
{

}

