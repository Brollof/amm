#pragma once

#include "wx/wx.h"
#include <wx/uiaction.h>
#include "TrayIcon.h"

class Main : public wxFrame
{
public:
  Main(std::string appName);
  ~Main();
  void OnButtonRun(bool run);

private:
  void OnTimer(wxTimerEvent& event);
  int m_timCnt = 0;
  int m_dir = 1;
  wxTimer m_timer;
  wxPoint m_lastMousePos;
  wxUIActionSimulator m_sim;
  TrayIcon* m_tray = nullptr;
};