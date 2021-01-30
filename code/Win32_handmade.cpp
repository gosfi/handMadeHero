#include<windows.h>


LRESULT CALLBACK
MainWindowCallback(HWND Window,
		   UINT Message,
		   WPARAM WParam,
		   LPARAM LParam)
{
  LRESULT Result = 0;
  switch(Message)
  {
    case WM_SIZE:
    {
      OutputDebugStringA("WM_SIZE\n");
    } break;
    case WM_DESTROY:
    {
      OutputDebugStringA("WM_DESTROY\n");
    } break;
    case WM_CLOSE:
    {
      OutputDebugStringA("WM_CLOSE\n");
    } break;
    case WM_ACTIVATEAPP:
    {
      OutputDebugStringA("WM_ACTIVATEAPP\n");
    } break;
    default:
    {
      OutputDebugStringA("default\n");
      Result = 0;
    } break;
  }
  return(Result);
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
