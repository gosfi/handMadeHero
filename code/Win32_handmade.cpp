#include<windows.h>


int WINAPI WinMain
( HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR lpCmdLine,
  int nShowCms)
{
  MessageBox(0,"this is a window"," handmade hero",
	     MB_OK|MB_ICONINFORMATION);
  return(0);
}
