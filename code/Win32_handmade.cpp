#include<windows.h>


LRESULT CALLBACK
MainWindowCallback(HWND Window,
		   UINT Message,
		   WPARAM WParam,
		   LPARAM LParam)
{
  
}


int WINAPI WinMain
( HINSTANCE Instance,
  HINSTANCE PrevInstance,
  LPSTR CommanddLine,
  int ShowCode)
{
  WNDCLASS windowClass ={};

  //TODO(sam)check if style CS_HREDRAW & CS_VREDRAW is still relevant
  windowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
  windowClass.lpfnWndProc = MainWindowCallback;
  windowClass.hInstance = Instance;
  // HICON     hIcon;
  // LPCSTR    lpszMenuName;
  windowClass.lpszClassName = "handMadeHeroWindowClass";
  
  MessageBox(0,"this is a window"," handmade hero",
	     MB_OK|MB_ICONINFORMATION);
  return(0);
}
