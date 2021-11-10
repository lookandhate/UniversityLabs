// Lab10Game.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Lab10Game.h"
#include "GameManager.h"



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
    LoadStringW(hInstance, IDC_LAB10GAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB10GAME));

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


CGameManager* gameManager = new CGameManager();


namespace DrawingUtils {


    void DrawLevelMatrixOnScreen(int rows, int columns, const HDC& hdc, int** matrixToDraw)
    {
        int baseXOffset = 100;
        int baseYOffset = 100;
        for (int row = 0; row < rows; row++)
        {
            for (int column = 0; column < columns; column++)
            {
                
                SelectObject(hdc, brushesForObjects[matrixToDraw[row][column] - 1]);

                Rectangle(hdc, (column * 40) + baseXOffset, // x left
                    row * 40 + baseYOffset, //y top
                    (column + 1) * 40 + baseXOffset, //x right
                    (row + 1) * 40 + baseYOffset //y bottom
                );
            }
        }
    }
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB10GAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB10GAME);
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

   // Load first level in init
   gameManager->LoadLevel(1, mlevelPaths[0]);


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
    case WM_KEYDOWN:
    {
        int pressedKey = wParam;
        int movementResult = 0;
        switch (pressedKey)
        {
        case VK_LEFT:
        {
            movementResult = gameManager->MovePlayer(EPlayerMovementDirection::Left);
            break;
        }
        case VK_RIGHT:
        {
            movementResult = gameManager->MovePlayer(EPlayerMovementDirection::Right);
            break;
        }
        case VK_UP:
        {
            movementResult = gameManager->MovePlayer(EPlayerMovementDirection::Up);
            break;
        }
        case VK_DOWN:
        {
            movementResult = gameManager->MovePlayer(EPlayerMovementDirection::Down);
            break;
        }
#if GameDebug 1
        // Debug cheat that proceeds to next level
        case VK_F2:
        {
            gameManager->NextLevel();
            break;
        }
        
        case VK_F3:
        {
            gameManager->ReloadCurrentLevel();
            break;
        }
#endif
        }
        switch (movementResult)
        {
        case EMovementResult::MovedOnBomb:
            MessageBox(hWnd, L"You are moved on bomb. restart level", NULL, MB_OK);
            // TODO ADD MESSAGE BOX THAT ALERTS ABOUT LOSE
            gameManager->ChangeGameState(EGameConditions::LostDueExplosion);
            break;
        case EMovementResult::MovedOnLevelEnd:
            MessageBox(hWnd, L"You passed level, proceed to the next one", NULL, MB_OK);
            gameManager->ChangeGameState(EGameConditions::WonCurrentLevel);

        }

        InvalidateRect(hWnd, NULL, TRUE);
    }

    
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            DrawingUtils::DrawLevelMatrixOnScreen(gameManager->GetRowsCount(), gameManager->GetColumnsCount(), hdc, gameManager->GetLevelMatrixPointer());


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
