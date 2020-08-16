#pragma once

#include "wx/wx.h"
#include <wx/uiaction.h>
#include "TrayIcon.h"

class TrayIcon;

class App : public wxApp
{
public:
  App();
  ~App();
  virtual bool OnInit();
  void OnRunButton(bool run);

private:
  TrayIcon* m_tray = nullptr;
  void OnTimer(wxTimerEvent& event);
  int m_timCnt = 0;
  int m_dir = 1;
  wxTimer m_timer;
  wxPoint m_lastMousePos;
  wxUIActionSimulator m_sim;
};