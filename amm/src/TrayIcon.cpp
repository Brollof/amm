#include <wx/wx.h>
#include <wx/taskbar.h>
#include <wx/icon.h> 
#include <wx/dc.h>
#include <wx/image.h>
#include <string>
#include "Main.h"
#include "TrayIcon.h"
#include "Common.h"


#define ICON_SIZE                 32
#define ACTIVE_NORMAL_COLOR       wxColour("GREEN")
#define ACTIVE_BAD_COLOR          wxColour("YELLOW")
#define ACTIVE_CRITICAL_COLOR     wxColour("RED")
#define INACTIVE_COLOR            wxColour("GREY")


BEGIN_EVENT_TABLE(TrayIcon, wxTaskBarIcon)
  EVT_MENU(ID_TRAY_BTN_EXIT, TrayIcon::OnMenuExit)
  EVT_MENU(ID_TRAY_BTN_RUN, TrayIcon::OnMenuRun)
END_EVENT_TABLE()


TrayIcon::TrayIcon(Main* window) : wxTaskBarIcon()
{
  m_frame = window;
  SetActive(false);
}

void TrayIcon::OnMenuExit(wxCommandEvent& event)
{
  m_frame->Destroy();
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
  SetActive(!m_isActive);
  m_frame->OnButtonRun(m_isActive);
}