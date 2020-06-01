#pragma once

#include "wx/wx.h"
#include <wx/uiaction.h>

class Main : public wxFrame
{
public:
  Main(std::string appName);
  ~Main();

private:
  void OnTimer(wxTimerEvent& event);
  int m_timCnt = 0;
  int m_dir = 1;
  wxTimer m_timer;
  wxPoint m_lastMousePos;
  wxUIActionSimulator m_sim;
  // wxDECLARE_EVENT_TABLE();

};