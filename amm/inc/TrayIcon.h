#pragma once

#include <wx/taskbar.h>
#include "App.h"

class App;

class TrayIcon : public wxTaskBarIcon
{
public:
  TrayIcon(App* app, bool isActive);
  void SetActive(bool isActive);

private:
  bool m_isActive = false;
  void OnMenuExit(wxCommandEvent& event);
  void OnMenuRun(wxCommandEvent& event);
  virtual wxMenu* CreatePopupMenu() wxOVERRIDE;
  App* m_app;

  DECLARE_EVENT_TABLE();
};