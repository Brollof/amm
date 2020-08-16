#include "App.h"
#include "Version.h"

wxIMPLEMENT_APP(App);

#define MOUSE_IDLE_TIME 5000
#define TIMER_PERIOD 500

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
  m_tray = new TrayIcon(this);
  return true;
}

void App::OnTimer(wxTimerEvent& event)
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
      m_sim.MouseMove({ m_lastMousePos.x + m_dir, m_lastMousePos.y });
    }
  }
  m_lastMousePos = pt;
}

void App::OnRunButton(bool run)
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