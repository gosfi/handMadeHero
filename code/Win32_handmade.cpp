#include<windows.h>


static bool Running;

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
      Running = false;
      OutputDebugStringA("WM_DESTROY\n");
    } break;
    case WM_CLOSE:
    {
      Running = false;
      OutputDebugStringA("WM_CLOSE\n");
    } break;
    case WM_ACTIVATEAPP:
    {
      OutputDebugStringA("WM_ACTIVATEAPP\n");
    } break;
    case WM_PAINT:
    {
      PAINTSTRUCT Paint;
      HDC DeviceContext = BeginPaint(Window, &Paint);
      int X = Paint.rcPaint.left;
      int Y = Paint.rcPaint.top;
      int Height = Paint.rcPaint.bottom -  Paint.rcPaint.top;
      int Width = Paint.rcPaint.right -  Paint.rcPaint.left;
      static DWORD Operation = WHITENESS; 
      PatBlt(DeviceContext, X, Y, Width, Height, Operation);
      if(Operation == WHITENESS)
      {
	Operation = BLACKNESS;
      }
      else
      {
	Operation = WHITENESS;
      }
      EndPaint(Window, &Paint);
    } break;
    default:
    {
      Result = DefWindowProc(Window, Message, WParam, LParam);
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

  if(RegisterClass(&windowClass))
  {
    HWND WindowHandle =
      CreateWindowExA(
		     0,
		     windowClass.lpszClassName,
		     "Handmade Hero",
		     WS_OVERLAPPEDWINDOW|WS_VISIBLE,
		     CW_USEDEFAULT,
		     CW_USEDEFAULT,
		     CW_USEDEFAULT,
		     CW_USEDEFAULT,
		     0,
		     0,
		     Instance,
		     0);
 if(WindowHandle != NULL)
 {
    MSG Message;
    while(Running)
    {
      BOOL MessageResult =  GetMessage(&Message, NULL, 0, 0);
      if(MessageResult > 0)
      {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
      }
      else
      {
        break;
      }
    }
  }
  else
  {
    //TODO(SAM): logging if failing
  }
					
  }
  else
  {
    //TODO(SAM): logging if failing
  }
  return(0);
}
