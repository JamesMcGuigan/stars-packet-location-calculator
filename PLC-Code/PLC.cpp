// Written By James McGuigan - james@starsfaq.com
// Packet Location Calculator v1.0.1
// GUI Code written using Borland Builder v3


//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("PLC.res");
USEFORM("PLCU.cpp", Form1);
USEFORM("GNU.cpp", FormGNU);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
    Application->Initialize();
    Application->CreateForm(__classid(TForm1), &Form1);
        Application->CreateForm(__classid(TFormGNU), &FormGNU);
        Application->Run();
  }
  catch (Exception &exception)
  {
    Application->ShowException(&exception);
  }
  return 0;
}
//---------------------------------------------------------------------------
