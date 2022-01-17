// ClassworkLab6.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include <stdio.h>
#include "ClassworkLab6.h"

#define MAX_LOADSTRING 100


#define X_LENGHT_OF_COLUMN 50 // Длина линии на оси oX для столбца
#define BOTTOM_Y_FOR_COLUMN 300 // Кооридната 

#define PATH_TO_FILE "C:\\Users\\root\\Desktop\\labs\\testTextFiles\\lab6.txt"

// Глобальные переменные:
int arraySize;
int arrayOfDigits[255];
int modificatedArray[255];

bool bSourceDiagramDrawed = false;
bool bModifiedDiagramDrawed = false;

HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLASSWORKLAB6, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLASSWORKLAB6));

    MSG msg;

    // Цикл основного сообщения:
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


void DrawColumn(HDC& hdc,int bottomRightX, int height, int startY)
{
    Rectangle(hdc, bottomRightX - X_LENGHT_OF_COLUMN, startY - height, bottomRightX, startY);

}

void DrawDiagram(HDC& hdc, size_t arraySize, int arrayToDraw[], int startY)
{
    int startX = 100;

    
    for (int i = 0; i < arraySize; i++)
    {
        DrawColumn(hdc, startX + i * X_LENGHT_OF_COLUMN, arrayToDraw[i], startY);
    }

    HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, pen);

    // Axes OY and OX
    MoveToEx(hdc, startX - X_LENGHT_OF_COLUMN, startY, NULL);
    LineTo(hdc, startX + X_LENGHT_OF_COLUMN * (arraySize + 2), startY);
    
    // Arrow at end of OX
    LineTo(hdc, startX + X_LENGHT_OF_COLUMN * (arraySize + 2) - 10, startY - 5);
    MoveToEx(hdc, startX + X_LENGHT_OF_COLUMN * (arraySize + 2), startY, NULL);
    LineTo(hdc, startX + X_LENGHT_OF_COLUMN * (arraySize + 2) - 10, startY + 5);

    // OY 
    MoveToEx(hdc, startX - X_LENGHT_OF_COLUMN, startY, NULL);
    LineTo(hdc, startX - X_LENGHT_OF_COLUMN, startY - 100);
    
    // Arrow at end of OY
    LineTo(hdc, startX - X_LENGHT_OF_COLUMN - 5, startY - 95);
    MoveToEx(hdc, startX - X_LENGHT_OF_COLUMN, startY - 100, NULL);
    LineTo(hdc, startX - X_LENGHT_OF_COLUMN + 5, startY - 95);

    if (DeleteObject(pen) == 0)
    {
        DebugBreak();
    };
}

void FindMinAndMax(size_t arraySize, int arrayToModificate[],
    int* maxElementPtr, int* minElementPtr,
    int* maxElementIndexPtr, int* minElementIndexPtr)
{
    *maxElementIndexPtr = 0;
    *minElementIndexPtr = 0;
    *maxElementPtr = arrayToModificate[0];
    *minElementPtr = arrayToModificate[0];
    for (int i = 0; i < arraySize; i++)
    {
        if (*maxElementPtr < arrayToModificate[i])
        {
            *maxElementPtr = arrayToModificate[i];
            *maxElementIndexPtr = i;
        }

        if (*minElementPtr > arrayToModificate[i])
        {
            *minElementPtr = arrayToModificate[i];
            *minElementIndexPtr = i;
        }
    }
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLASSWORKLAB6));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLASSWORKLAB6);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    // Getting data from text file
    FILE* f;
   
    fopen_s(&f, PATH_TO_FILE, "r");
    fscanf_s(f, "%d", &arraySize);

    for (int i = 0; i < arraySize; i++) {
        fscanf_s(f, "%d", &arrayOfDigits[i]);
        modificatedArray[i] = arrayOfDigits[i];
    }
    

   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

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
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
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
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...

            //DrawColumn(hdc, 100, 100);
            
            if (!bSourceDiagramDrawed || true)
            {
                // Draw diagram with normal values
                DrawDiagram(hdc, arraySize, arrayOfDigits, 150);
                bSourceDiagramDrawed = true;
            }
            
            if (!bModifiedDiagramDrawed || true)
            {
                bModifiedDiagramDrawed = true;
                // Modifying array here below
                int minIndex, maxIndex, minValue, maxValue = 0;
                FindMinAndMax(arraySize, arrayOfDigits, &maxValue, &minValue, &maxIndex, &minIndex);

                int leftBorder;
                int rightBorder;
                if (maxIndex > minIndex)
                {
                    rightBorder = maxIndex;
                    leftBorder = minIndex;
                }
                else
                {
                    rightBorder = minIndex;
                    leftBorder = maxIndex;
                }

                int newSize = 0;
                for (int i = 0; i < arraySize; i++)
                {
                    // row not in [leftBorder;rightBorder] -> saving all elements
                    if (i <= leftBorder || i >= rightBorder)
                    {
                        modificatedArray[newSize] = arrayOfDigits[i];
                        newSize++;
                    }
                    else
                    {
                        if (arrayOfDigits[i] % 2 != 0)
                        {
                            modificatedArray[newSize] = arrayOfDigits[i];
                            newSize++;
                        }
                    }
                }


                // Draw diagram with modified values below normal diagram
                DrawDiagram(hdc, newSize, modificatedArray, 400);
                EndPaint(hWnd, &ps);
            }

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

// Обработчик сообщений для окна "О программе".
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
