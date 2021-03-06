#include<windows.h>

#define internal static 
#define local_persist static 
#define global_variable static 
//TODO(Sam):global variable for now
global_variable bool Running;
global_variable BITMAPINFO BitmapInfo;
global_variable void *BitmapMemory;
global_variable int BitmapWidth;
global_variable int BitmapHeight;

internal void
Win32ResizeDIBSection(int Width, int Height)
{

  if(BitmapMemory)
  {
    VirtualFree(BitmapMemory, 0, MEM_RELEASE);
  }

  BitmapWidth = Width;
  BitmapHeight = Height;
  
  BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
  BitmapInfo.bmiHeader.biWidth = BitmapWidth;
  BitmapInfo.bmiHeader.biHeight = -BitmapHeight;
  BitmapInfo.bmiHeader.biPlanes = 1;
  BitmapInfo.bmiHeader.biBitCount = 32;
  BitmapInfo.bmiHeader.biCompression = BI_RGB;

  int BytesPerPixels = 4;
  int BitmapMemorySize = (BitmapWidth * BitmapHeight) * BytesPerPixels;
  BitmapMemory = VirtualAlloc(0,BitmapMemorySize, MEM_COMMIT,PAGE_READWRITE);
}

internal void
Win32UpdateWindow(HDC DeviceContext, RECT *WindowRect, int X, int Y, int Width, int Height)
{
  int WindowWidth = WindowRect->right - WindowRect->left;
  int WindowHeight = WindowRect->bottom - WindowRect->top; 
  StretchDIBits(DeviceContext,
		0, 0, BitmapWidth, BitmapHeight,
		0, 0, WindowWidth, WindowHeight,
                BitmapMemory,
                &BitmapInfo,
                DIB_RGB_COLORS,SRCCOPY);
}

LRESULT CALLBACK
Win32MainWindowCallback(HWND Window,
		   UINT Message,
		   WPARAM WParam,
		   LPARAM LParam)
{
  LRESULT Result = 0;
  PAINTSTRUCT Paint;
  switch(Message)
  {
    case WM_SIZE:
    {
      RECT ClientRect;
      GetClientRect(Window, &ClientRect);
      int Width = ClientRect.right - Paint.rcPaint.left;
      int Height = ClientRect.bottom - ClientRect.top;
      Win32ResizeDIBSection(Width, Height);
    } break;
    case WM_DESTROY:
    {
      //TODO(Sam): probably error, recreate window
      Running = false;
    } break;
    case WM_CLOSE:
    {
      //TODO(Sam): put a message to user
      Running = false;
    } break;
    case WM_ACTIVATEAPP:
    {
      OutputDebugStringA("WM_ACTIVATEAPP\n");
    } break;
    case WM_PAINT:
    {
      HDC DeviceContext = BeginPaint(Window, &Paint);
      int X = Paint.rcPaint.left;
      int Y = Paint.rcPaint.top;
      int Height = Paint.rcPaint.bottom -  Paint.rcPaint.top;
      int Width = Paint.rcPaint.right -  Paint.rcPaint.left;
      Win32UpdateWindow(DeviceContext,X, Y, Width, Height);
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
  windowClass.lpfnWndProc = Win32MainWindowCallback;
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
    Running = true;
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
