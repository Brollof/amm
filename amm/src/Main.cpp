#include <wx/display.h>
#include <iostream>
#include "Main.h"


#define APP_WIDTH 200
#define APP_HEIGHT 100
#define MOUSE_IDLE_TIME 5000
#define TIMER_PERIOD 500


Main::Main(std::string appName) : wxFrame(nullptr, wxID_ANY, appName)
{
  m_timer.Bind(wxEVT_TIMER, &Main::OnTimer, this);
  m_tray = new TrayIcon(this);
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
      std::cout << "moving mouse, dir: " << m_dir << std::endl;
      m_dir *= -1; // invert direction
      m_sim.MouseMove({m_lastMousePos.x + m_dir, m_lastMousePos.y});
    }
  }
  m_lastMousePos = pt;
}

void Main::OnButtonRun(bool run)
{
  if (run)
  {
    std::cout << "AMM running" << std::endl;
    m_timer.Start(TIMER_PERIOD);
  }
  else
  {
    std::cout << "AMM stopped" << std::endl;
    m_timer.Stop();
  }
}