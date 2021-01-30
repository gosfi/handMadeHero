#include<windows.h>


int WINAPI WinMain
( HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR lpCmdLine,
  int nShowCms)
{
  WNDCLASS windowClass ={};

  //TODO(sam)check if style is still relevant
  windowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
  windowClass.lpfnWndProc = ;
  windowClass.hInstance = hInstance;
  // HICON     hIcon;
  // LPCSTR    lpszMenuName;
  windowClass.lpszClassName = "handMadeHeroWindowClass";
  
  MessageBox(0,"this is a window"," handmade hero",
	     MB_OK|MB_ICONINFORMATION);
  return(0);
}
