#include "App.h"

wxIMPLEMENT_APP(App);

App::App()
{
#ifdef _DEBUG
  AllocConsole();
  FILE* fDummy;
  freopen_s(&fDummy, "CONIN$", "r", stdin);
  freopen_s(&fDummy, "CONOUT$", "w", stderr);
  freopen_s(&fDummy, "CONOUT$", "w", stdout);
#endif

  // PrintVersion();
  // PrintBuildType();
}

App::~App()
{
  delete m_frame;
}

bool App::OnInit()
{
  wxImage::AddHandler(new wxJPEGHandler);
  m_frame = new Main("test" /* GetAppTitle() */ );
  return true;
}