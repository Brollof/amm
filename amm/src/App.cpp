#include "App.h"
#include "Version.h"
#include "Windows.h"

wxIMPLEMENT_APP(App);

#define MOUSE_IDLE_TIME   5000 // ms

std::ostream& operator<<(std::ostream& os, const wxPoint& pt)
{
  os << "{" << pt.x << "," << pt.y << "}";
  return os;
}

App::App()
{
#ifdef _DEBUG
  AllocConsole();
  FILE* fDummy;
  freopen_s(&fDummy, "CONIN$", "r", stdin);
  freopen_s(&fDummy, "CONOUT$", "w", stderr);
  freopen_s(&fDummy, "CONOUT$", "w", stdout);
#endif

  PrintVersion();
  PrintBuildType();
}

App::~App()
{
#ifdef _DEBUG
  FreeConsole();
#endif

  delete m_tray;
}

bool App::OnInit()
{
  wxImage::AddHandler(new wxJPEGHandler);
  m_timer.Bind(wxEVT_TIMER, &App::OnTimer, this);
  m_tray = new TrayIcon(this, true);
  OnRunButton(true);
  return true;
}

void App::OnTimer(wxTimerEvent& event)
{
  std::cout << "moving mouse" << std::endl;
  // actually we don't move mouse at all, just sending a mouse event
  mouse_event(MOUSEEVENTF_MOVE, 0, 0, 0, 0);
}

void App::OnRunButton(bool run)
{
  if (run)
  {
    std::cout << "AMM running" << std::endl;
    m_timer.Start(MOUSE_IDLE_TIME);
  }
  else
  {
    std::cout << "AMM stopped" << std::endl;
    m_timer.Stop();
  }
}