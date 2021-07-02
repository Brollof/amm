#include <wx/taskbar.h>
#include <wx/icon.h> 
#include "TrayIcon.h"
#include "Common.h"


BEGIN_EVENT_TABLE(TrayIcon, wxTaskBarIcon)
  EVT_MENU(ID_TRAY_BTN_EXIT, TrayIcon::OnMenuExit)
  EVT_MENU(ID_TRAY_BTN_RUN, TrayIcon::OnMenuRun)
  EVT_TASKBAR_LEFT_DCLICK(TrayIcon::OnLeftDoubleClick)
END_EVENT_TABLE()


TrayIcon::TrayIcon(App* app, bool isActive) : wxTaskBarIcon()
{
  m_app = app;
  SetActive(isActive);
}

wxMenu* TrayIcon::CreatePopupMenu()
{
  wxMenu* menu = new wxMenu;
  menu->Append(ID_TRAY_BTN_RUN, m_isActive ? "Stop" : "Start");
  menu->Append(ID_TRAY_BTN_EXIT, "Exit");
  return menu;
}

void TrayIcon::SetActive(bool isActive)
{
  m_isActive = isActive;
  // Set icon depending on active state
  if (m_isActive)
  {
    std::cout << "tray icon active" << std::endl;
    SetIcon(wxICON(IDI_ICON1));
  }
  else
  {
    std::cout << "tray icon not active" << std::endl;
    SetIcon(wxICON(IDI_ICON2));
  }
}

void TrayIcon::OnMenuRun(wxCommandEvent& event)
{
  std::cout << "OnMenuRun" << std::endl;
  event.Skip();
  SetActive(!m_isActive);
  m_app->OnRunButton(m_isActive);
}

void TrayIcon::OnMenuExit(wxCommandEvent& event)
{
  m_app->Exit();
}

void TrayIcon::OnLeftDoubleClick(wxTaskBarIconEvent& event)
{
  SetActive(!m_isActive);
  m_app->OnRunButton(m_isActive);
}