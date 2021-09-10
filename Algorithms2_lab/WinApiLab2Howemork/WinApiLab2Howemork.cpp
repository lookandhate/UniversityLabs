// WinApiLab2Howemork.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "WinApiLab2Howemork.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


/************************************
************DRAWING UTILS************
*************************************
************************************/


void DrawFlower(HDC& hdc, POINT root)
{

	MoveToEx(hdc, root.x, root.y, NULL);
	LineTo(hdc, root.x, root.y + 20);
	
    // Create custom brush in order to draw a "Colored" head of the flower
    HBRUSH hBrush = CreateSolidBrush(RGB(128, 128, 0));
	SelectObject(hdc, hBrush);

    // Represent flower head as ellipse
	Ellipse(hdc, root.x - 5, root.y - 4, root.x + 5, root.y + 4);

    DeleteObject(hBrush);

}

void DrawFloor(HDC& hdc, POINT topLeft, POINT bottomRight)
{
    // Brush with color of the grass
    auto color = RGB(126, 200, 80);
    HBRUSH hBrush = CreateSolidBrush(color);
    
    SelectObject(hdc, hBrush);

    Rectangle(hdc, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);

    DeleteObject(hBrush);
}

void DrawLake(HDC& hdc, POINT lakeRoot, UINT sizeDelta) {
    // Draw lake using ellipse

    // Create brush with blue water-like color
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 141, 151));
    SelectObject(hdc, hBrush);

    Ellipse(hdc,
        lakeRoot.x - sizeDelta, lakeRoot.y - sizeDelta,
        lakeRoot.x + sizeDelta, lakeRoot.y + sizeDelta
    );

    DeleteObject(hBrush);
    

}

void DrawLake(HDC& hdc, POINT lakeRoot, UINT sizeDeltaX, UINT sizeDeltaY) {
	// Draw lake using ellipse

    // Create brush with blue water-like color
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 141, 151));
	SelectObject(hdc, hBrush);

	Ellipse(hdc,
		lakeRoot.x - sizeDeltaX, lakeRoot.y - sizeDeltaY,
		lakeRoot.x + sizeDeltaX, lakeRoot.y + sizeDeltaY
	);

	DeleteObject(hBrush);
}

POINT& CreatePoint(int x, int y) {
    POINT p = POINT();
    p.x = x;
    p.y = y;
    
    return p;
}

/************************************
**********DRAWING UTILS END**********
*************************************
************************************/

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPILAB2HOWEMORK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPILAB2HOWEMORK));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPILAB2HOWEMORK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPILAB2HOWEMORK);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}



//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            /************************************
            *************************************
            ******** GOVNOCODE GOES HERE ********
            *************************************
            *************************************/


            // Defines grass properties
            POINT grassTopLeft = CreatePoint(100, 100);
            POINT grassBottomRight = CreatePoint(600, 600);
            
            // Defines lake properties
            POINT lakeRoot = CreatePoint(450, 450);
            UINT lakeSizeDelta = 100;


            POINT point = CreatePoint(200, 200);

            DrawFloor(hdc, grassTopLeft, grassBottomRight);
            DrawFlower(hdc, point);
            DrawLake(hdc, lakeRoot, lakeSizeDelta - 10, lakeSizeDelta+ 10);
           



            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
