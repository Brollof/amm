#include "App.h"
#include "Version.h"
#include "Windows.h"

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
  m_tray = new TrayIcon(this, true);
  OnRunButton(true);
  return true;
}

void App::OnTimer(wxTimerEvent& event)
{
  wxMouseState mouse = wxGetMouseState();
  wxPoint pt = { mouse.GetX(), mouse.GetY() };

  std::cout << pt << std::endl;

  // Mouse move or button press detected
  if (pt != m_lastMousePos || mouse.ButtonIsDown(wxMOUSE_BTN_ANY))
  {
    m_timCnt = 0;
  }
  else
  {
    m_timCnt++;
    if (m_timCnt * TIMER_PERIOD >= MOUSE_IDLE_TIME) // move mouse manually
    {
      m_dir *= -1; // invert direction
      std::cout << "moving mouse, dir: " << m_dir << std::endl;
      SetCursorPos(pt.x + m_dir, pt.y);
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