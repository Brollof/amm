#include <wx/display.h>
#include <iostream>
#include "Main.h"


#define APP_WIDTH 200
#define APP_HEIGHT 100
#define MOUSE_IDLE_TIME 5000
#define TIMER_PERIOD 500


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

  m_timer.Bind(wxEVT_TIMER, &Main::OnTimer, this);
  m_timer.Start(TIMER_PERIOD);
}

Main::~Main()
{

}

std::ostream& operator<<(std::ostream& os, const wxPoint& pt)
{
  os << "{" << pt.x << "," << pt.y << "}";
  return os;
}

void Main::OnTimer(wxTimerEvent& event)
{
  wxPoint pt = wxGetMousePosition();
  std::cout << pt << std::endl;

  // Mouse has moved
  if (pt != m_lastMousePos)
  {
    m_timCnt = 0;
  }
  else
  {
    m_timCnt++;
    if (m_timCnt * TIMER_PERIOD >= MOUSE_IDLE_TIME) // move mouse manually
    {
      m_dir *= -1; // invert direction
      m_sim.MouseMove({m_lastMousePos.x + m_dir, m_lastMousePos.y});
      std::cout << "moving mouse, dir: " << m_dir << std::endl;
    }
  }
  m_lastMousePos = pt;
}