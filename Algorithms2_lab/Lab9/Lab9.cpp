// Lab9.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Lab9.h"

#define MAX_LOADSTRING 100


namespace Utils {
    HBRUSH bruhes[] = {
       CreateSolidBrush(RGB(255, 0, 0)), // red
       CreateSolidBrush(RGB(0, 255, 0)), // green
       CreateSolidBrush(RGB(0, 0, 255)), // blue
       CreateSolidBrush(RGB(255,165,0)), // Orange
    };

    typedef struct Point {
        int row, column;
    } Point;
    
    void ReadDataFromTextFile(int& rows, int& columns, int matrixToFill[100][100])
    {
        FILE* filePtr;

        if (fopen_s(&filePtr, PATH_TO_TEXT_FILE, "rt"))
        {
            exit(0);
        };
        fscanf_s(filePtr, "%d", &rows);
        fscanf_s(filePtr, "%d", &columns);

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                fscanf_s(filePtr, "%d", &(matrixToFill[i][j]));
            }
        }

        fclose(filePtr);
    }

    void DrawMatrix(int rows, int columns, const HDC& hdc, int colors[100][100], int baseXOffset, int baseYOffset)
    {
        for (int row = 0; row < rows; row++)
        {
            for (int column = 0; column < columns; column++)
            {
                SelectObject(hdc, Utils::bruhes[colors[row][column] - 1]);

                Rectangle(hdc, (column * 40) + baseXOffset, // x left
                    row * 40 + baseYOffset, //y top
                    (column + 1) * 40 + baseXOffset, //x right
                    (row + 1) * 40 + baseYOffset //y bottom
                );
            }
        }
    }

   

    void FindMaxAndMinElements(int rows, int columns, int matrix[][100], Utils::Point* maxPtr, Utils::Point* minPtr)
    {

        int maxValue = matrix[maxPtr->row][maxPtr->column];
        int minValue = matrix[minPtr->row][minPtr->column];
        
        

        for (int row = 0; row < rows; row++)
        {
            for (int column = 0; column < columns; column++)
            {
                if (minValue > matrix[row][column])
                {
                    minPtr->row = row;
                    minPtr->column = column;
                    minValue = matrix[minPtr->row][minPtr->column];
                }

                if (maxValue < matrix[row][column])
                {
                }
            }
        }
    }

    void MutateMatrixD(int& rows, int& columns, int matrixToMutate[100][100])
    {
        Utils::Point minPoint = Point();
        Utils::Point maxPoint = Point();

        FindMaxAndMinElements(rows, columns, matrixToMutate, &maxPoint, &minPoint);

        int newRowCount = 0;
        
        for (int row = 0; row < rows; row++)
        {
            int currentColumn = 0;
            bool flagHasMinimal = false;
            
            for (int column = 0; column < columns; column++)
            {
                if ((row == minPoint.row && minPoint.column == column))
                {
                    flagHasMinimal = true;
                }
                else
                {
                    currentColumn++;
                }
            }
            if (!flagHasMinimal)
                newRowCount++;
        }
        rows = rows - 1;
        columns = columns - 1;
    }

}

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
void DrawMatrix(int m, int n, const HDC& hdc, int  colors[100][100], int baseXOffset, int baseYOffset);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_LAB9, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB9));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB9));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB9);
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

            int rows, columns;
            int matrix[100][100];
            Utils::ReadDataFromTextFile(rows, columns, matrix);

            int baseXOffset = 100;
            int baseYOffset = 100;

            Utils::DrawMatrix(rows, columns, hdc, matrix, baseXOffset, baseYOffset);
            Utils::MutateMatrixD(rows, columns, matrix);
            Utils::DrawMatrix(rows, columns, hdc, matrix, baseXOffset + 500, baseYOffset);


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
