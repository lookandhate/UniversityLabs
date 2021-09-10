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


#define myrand(minNum,maxNum) rand() % (maxNum - minNum) + minNum

POINT CreatePoint(int x, int y) {
	POINT p = POINT();
	p.x = x;
	p.y = y;

	return p;
}


void DrawFlower(HDC& hdc, POINT root, UINT stemSize)
{

	MoveToEx(hdc, root.x, root.y, NULL);
	LineTo(hdc, root.x, root.y + stemSize);
	
    // Create custom brush in order to draw a "Colored" head of the flower
    HBRUSH hBrush = CreateSolidBrush(RGB(128, 128, 0));
	SelectObject(hdc, hBrush);

    // Represent flower head as ellipse
	Ellipse(hdc, root.x - 16, root.y - 16, root.x + 16, root.y + 16);

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
    // Draw lake using Circle(i.e x-radius equal to y-radius)

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
	// Draw lake using ellipse(i.e x-radius equal is not to y-radius)

    // Create brush with blue water-like color
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 141, 151));
	SelectObject(hdc, hBrush);

	Ellipse(hdc,
		lakeRoot.x - sizeDeltaX, lakeRoot.y - sizeDeltaY,
		lakeRoot.x + sizeDeltaX, lakeRoot.y + sizeDeltaY
	);

	DeleteObject(hBrush);
}

void DrawSkyBox(HDC& hdc, int maximumYCoordinate) {
    // Draw skybox using blue rectangle
    
    HBRUSH hBrush = CreateSolidBrush(RGB(173, 216, 230));
    SelectObject(hdc, hBrush);

    Rectangle(hdc, 0, 0, 100000, maximumYCoordinate);
    
}

void newDrawHouse(HDC& hdc, const POINT topLeft, UINT wallLength) {
    // Draw house using Rectangle and self-made triagnle(using 3 lines)
    // Warning: Roof MUST be above grass upper line, because i cannot fill triagnle with custom color

    // Main body of the house that will be a rectangle

    // Create custom brush in order to fill rectangle with custom color(wood-like color in our case)
    HBRUSH hMainBodyBrush = CreateSolidBrush(RGB(186, 140, 99));
    SelectObject(hdc, hMainBodyBrush);
    Rectangle(hdc, topLeft.x, topLeft.y, topLeft.x + wallLength, topLeft.y + wallLength);
    
    // Do not forget to delete brush object, because we do not want to get a memory leak
    DeleteObject(hMainBodyBrush);

    // This point represent TOP of the triangle( point there two lines will collide with each other)
    POINT triangleRoofHighestpoint = CreatePoint((int)(topLeft.x + wallLength / 2), (int)(topLeft.y - wallLength / 3));
   
    // Draw a triangle using point we calculated above
    MoveToEx(hdc, topLeft.x, topLeft.y, NULL);
    LineTo(hdc, triangleRoofHighestpoint.x, triangleRoofHighestpoint.y);
    LineTo(hdc, topLeft.x + wallLength, topLeft.y);
    LineTo(hdc, topLeft.x, topLeft.y);



}

void DrawSun(HDC& hdc, int size) {
    // Draw sun using circle( ellipse with equal radiuses
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 0));
	SelectObject(hdc, hBrush);

	Ellipse(hdc,
		75 - size, 50- size,
		75+ size, 50 + size
	);

	DeleteObject(hBrush);

}

void GenerateFlowers(unsigned int flowersToGenerate, unsigned int maxXCoordinate, unsigned int maxYCoordinate,
	unsigned int minXCoordinate, unsigned int minYCoordinate,
	HDC hdc, UINT defaultFlowerStemSize
)
{
	for (int i = 0; i < flowersToGenerate; i++) {
		// coordinate = rand() % (max_number + 1 - minimum_number) + minimum_number

		int xCoordinate = myrand(minXCoordinate, maxXCoordinate);
		int yCoordinate = myrand(minYCoordinate, maxYCoordinate);

		// Delta on what flower steam can change
		int mutateSizeOfFlowerSteam = myrand(5, 60);

		DrawFlower(hdc, CreatePoint(xCoordinate, yCoordinate), defaultFlowerStemSize + mutateSizeOfFlowerSteam);
	}
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
			RECT clientRect;
			GetClientRect(hWnd, &clientRect);

            POINT grassTopLeft = CreatePoint(clientRect.left, clientRect.top + 300);
            POINT grassBottomRight = CreatePoint(clientRect.right, clientRect.bottom);
            

            // Flower Properties
            UINT defaultFlowerStemSize = 50;
            
            // Defines lake properties
            POINT lakeRoot = CreatePoint(800, 500);
            UINT lakeSizeDelta = 100;
           
            DrawFloor(hdc, grassTopLeft, grassBottomRight);
            
            // Adding flowers on the floor
            GenerateFlowers(10,
                clientRect.right - 100, clientRect.bottom, clientRect.left + 100, clientRect.top + 300,
                hdc, defaultFlowerStemSize
            );

            // Drawing a lake between two houses
            DrawLake(hdc, lakeRoot, lakeSizeDelta - 10, lakeSizeDelta+ 10);

            // Draw lake in random location
            

            // Placing houses
            newDrawHouse(hdc, CreatePoint(500, 300), 100);
            newDrawHouse(hdc, CreatePoint(900, 300), 100);

            DrawSkyBox(hdc, 150);
            DrawSun(hdc, 50);
       
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
