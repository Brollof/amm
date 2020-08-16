#pragma once

#include <wx/taskbar.h>

class Main;

class TrayIcon : public wxTaskBarIcon
{
public:
  TrayIcon(Main* frame);
  void SetActive(bool isActive);

private:
  bool m_isActive = false;
  Main* m_frame = nullptr;
  void OnMenuExit(wxCommandEvent& event);
  void OnMenuRun(wxCommandEvent& event);
  virtual wxMenu* CreatePopupMenu() wxOVERRIDE;
  void SetIconFromNumber(int n);
  DECLARE_EVENT_TABLE();
};