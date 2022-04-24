#include "windows.h"
#include "bits/stdc++.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, PSTR iCmdLine, int iCmdShow){
    HWND hwnd;
    WNDCLASS wndclass;
    MSG msg;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor (nullptr, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszClassName = TEXT("Doraemon");
    wndclass.lpszMenuName = nullptr;

    if (!RegisterClass(&wndclass)){
        MessageBoxA(nullptr, "error box", TEXT("can't register wndclass"), MB_OKCANCEL);
    }

    hwnd = CreateWindow(TEXT("Doraemon"), TEXT("Doraemon"), WS_OVERLAPPEDWINDOW | WS_VSCROLL,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        nullptr, nullptr, hInstance, nullptr);

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&msg, nullptr, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam){
    HDC hdc;
    PAINTSTRUCT ps;
    static int cxClient, cyClient;
    HBRUSH hBrush, hOldBrush;
    HPEN hPen, hOldPen;

    // limit a square area，default the length of client is longer than height.
    POINT edge[] = {
            (cxClient - cyClient)/2, 0,
            (cxClient + cyClient)/2, 0,
            (cxClient - cyClient)/2, cyClient,
            (cxClient + cyClient)/2, cyClient,
    };

    // right : (430, 250) -> (500, 230)  (430, 270) -> (510, 270)  (430, 290) -> (500, 310)
    // left  : (370, 250) -> (300, 230)  (370, 270) -> (290, 270)  (370, 290) -> (300, 310)
    POINT whiskers[] = {
            cxClient / 2 - cyClient * 3 / 80, cyClient * 5 / 16,
            cxClient / 2 - cyClient / 8, cyClient * 23 / 80,

            cxClient / 2 - cyClient * 3 / 80, cyClient * 27 / 80,
            cxClient / 2 - cyClient * 11 /80, cyClient * 27 / 80,

            cxClient / 2 - cyClient * 3 / 80, cyClient * 29 / 80,
            cxClient / 2 - cyClient / 8, cyClient * 31 / 80,

            cxClient / 2 + cyClient * 3 / 80, cyClient * 5 / 16,
            cxClient / 2 + cyClient / 8, cyClient * 23 / 80,

            cxClient / 2 + cyClient * 3 / 80, cyClient * 27 / 80,
            cxClient / 2 + cyClient * 11 /80, cyClient * 27 / 80,

            cxClient / 2 + cyClient * 3 / 80, cyClient * 29 / 80,
            cxClient / 2 + cyClient / 8, cyClient * 31 / 80,
            };

    // (520, 400) -> (590, 480) -> (570, 500) -> (530, 485) -> (530, 465) -> (530, 615) ->
    // (270, 615) -> (270, 465) -> (270, 485) -> (230, 500) -> (210, 480) -> (280, 400) ->
    POINT body[] = {
            cxClient / 2 + cyClient * 3 / 20, cyClient /2,
            cxClient / 2 + cyClient * 19 / 80, cyClient * 3 / 5,
            cxClient / 2 + cyClient * 17 / 80, cyClient * 5 / 8,
            cxClient / 2 + cyClient * 13 / 80, cyClient * 97 / 160,
            cxClient / 2 + cyClient * 13 / 80, cyClient * 93 / 160,
            cxClient / 2 + cyClient * 13 / 80, cyClient * 123 / 160,
            cxClient / 2 - cyClient * 13 / 80, cyClient * 123 / 160,
            cxClient / 2 - cyClient * 13 / 80, cyClient * 93 / 160,
            cxClient / 2 - cyClient * 13 / 80, cyClient * 97 / 160,
            cxClient / 2 - cyClient * 17 / 80, cyClient * 5 / 8,
            cxClient / 2 - cyClient * 19 / 80, cyClient * 3 / 5,
            cxClient / 2 - cyClient * 3 / 20, cyClient /2,
            };

    switch (message) {
        case WM_SIZE:
            cxClient = LOWORD(lparam);
            cyClient = HIWORD(lparam);
            return 0;
        case WM_PAINT:

            hdc = BeginPaint(hwnd, &ps);
            SetROP2(hdc, R2_COPYPEN);

            /*************************************** head ****************************************/

            hBrush = CreateSolidBrush(RGB(9,156,199));
            hOldBrush = static_cast<HBRUSH>(SelectObject(hdc, hBrush));
            Ellipse(hdc,
                    edge[0].x + cyClient * 11 / 40, edge[0].y + cyClient / 8,
                    edge[1].x - cyClient * 11 / 40, edge[1].y + cyClient * 23 / 40);
            SelectObject(hdc, hOldBrush);

            /*************************************** face ****************************************/

            Ellipse(hdc,
                    edge[0].x + cyClient * 5 / 16, edge[0].y + cyClient / 5,
                    edge[1].x - cyClient * 5 / 16, edge[1].y + cyClient * 23 / 40);

            /*************************************** eyes ****************************************/

            // left
            Ellipse(hdc,
                    cxClient / 2 - cyClient / 10, edge[0].y + cyClient * 7 / 40,
                    cxClient / 2, edge[1].y + cyClient * 3 / 10);
            // right
            Ellipse(hdc,
                    cxClient / 2 , edge[0].y + cyClient * 7 / 40,
                    cxClient / 2 + cyClient / 10, edge[1].y + cyClient * 3 / 10);

            /*************************************** irises ****************************************/

            hBrush = CreateSolidBrush(RGB( 0, 0, 0));
            hOldBrush = static_cast<HBRUSH>(SelectObject(hdc, hBrush));
            // left
            Ellipse(hdc,
                    cxClient / 2 - cyClient / 25, edge[0].y + cyClient * 17 / 80,
                    cxClient / 2 - cyClient / 100, edge[1].y + cyClient * 21 / 80);
            // right
            Ellipse(hdc,
                    cxClient / 2 + cyClient / 100, edge[0].y + cyClient * 17 / 80,
                    cxClient / 2 + cyClient / 25, edge[1].y + cyClient * 21 / 80);
            SelectObject(hdc, hOldBrush);

            /*************************************** pupils ****************************************/

            // left
            Ellipse(hdc,
                    cxClient / 2 - cyClient * 3 / 100, edge[0].y + cyClient * 9 / 40,
                    cxClient / 2 - cyClient / 50, edge[1].y + cyClient / 4);
            // right
            Ellipse(hdc,
                    cxClient / 2 + cyClient / 50, edge[0].y + cyClient * 9 / 40,
                    cxClient / 2 + cyClient *3 / 100, edge[1].y + cyClient / 4);

            /*************************************** nose ****************************************/

            hBrush = CreateSolidBrush(RGB( 255, 30, 35));
            hOldBrush = static_cast<HBRUSH>(SelectObject(hdc, hBrush));
            Ellipse(hdc,
                    cxClient / 2 - cyClient * 3 / 160, cyClient * 43 / 160,
                    cxClient / 2 + cyClient * 3 / 160, cyClient * 49 / 160
                    );
            SelectObject(hdc, hOldBrush);

            /*************************************** mouth ****************************************/

            MoveToEx(hdc, cxClient/2, cyClient * 49 / 160, nullptr);
            LineTo(hdc, cxClient/2, cyClient * 7 / 16);
            // (320, 310) (400, 350) (480, 310) ======> R = 100
            POINT lt, rb;
            lt.x = cxClient / 2 - cyClient / 8;
            lt.y = cyClient * 3 / 16;
            rb.x = cxClient / 2 + cyClient / 8;
            rb.y = cyClient * 7 / 16;
            Arc(hdc,
                lt.x, lt.y,
                rb.x, rb.y,
                cxClient/2 - cyClient/10, cyClient * 31 / 80,
                cxClient/2 + cyClient/10, cyClient * 31 / 80
                );

            /*************************************** whiskers ****************************************/
            // right : (430, 250) -> (500, 230)  (430, 270) -> (510, 270)  (430, 290) -> (500, 310)
            // left  : (370, 250) -> (300, 230)  (370, 270) -> (290, 270)  (370, 290) -> (300, 310)
            LPPOINT pp;
            for (int i = 0; i < 12; i += 2){
                GetCurrentPositionEx(hdc, pp);
                MoveToEx(hdc, whiskers[i].x, whiskers[i].y, pp);
                LineTo(hdc, whiskers[i+1].x, whiskers[i+1].y);
            }

            /*************************************** body ****************************************/
            // (280, 400) -> (520, 400) -> (590, 480) -> (570, 500) -> (530, 485) -> (530, 465) -> (530, 615) ->
            // (270, 615) -> (270, 465) -> (270, 485) -> (230, 500) -> (210, 480) -> /*(280, 400)*/

            hBrush = CreateSolidBrush(RGB( 9,156,199));
            hOldBrush = static_cast<HBRUSH>(SelectObject(hdc, hBrush));
            Polygon(hdc, body, 12);
            SelectObject(hdc, hOldBrush);

            /*************************************** abdomen ****************************************/
            // R = 100

            Chord(hdc,
                    cxClient / 2 - cyClient / 8, cyClient * 15 / 32,
                    cxClient / 2 + cyClient / 8, cyClient * 23 / 32,
                    cxClient / 2 - cyClient * 33 / 400, cyClient / 2,
                    cxClient / 2 + cyClient * 33 / 400, cyClient / 2
                    );

            /*************************************** pocket ****************************************/

            Chord(hdc,
                  cxClient / 2 - cyClient * 3 / 32, cyClient * 39 / 80,
                  cxClient / 2 + cyClient * 3 / 32, cyClient * 27 / 40,
                  0, cyClient * 93 / 160,
                  cxClient, cyClient * 93 / 160
                  );

            /*************************************** necklace ****************************************/
                                        /* Doraemon doesn't have neck */
            // (535, 410) (265, 390)
            hBrush = CreateSolidBrush(RGB( 255, 30, 35));
            hOldBrush = static_cast<HBRUSH>(SelectObject(hdc, hBrush));
            hPen = CreatePen(PS_SOLID, 0, RGB(255, 30, 35));
            hOldPen = static_cast<HPEN>(SelectObject(hdc, hPen));
            Rectangle(hdc, cxClient / 2 - cyClient * 27 / 160, cyClient * 39 / 80,
                           cxClient / 2 + cyClient * 27 / 160, cyClient * 41 / 80);
            Pie(hdc,
                cxClient / 2 - cyClient * 29 / 160, cyClient * 39 / 80,
                cxClient / 2 - cyClient * 5 / 32, cyClient * 41 / 80,
                cxClient / 2 - cyClient * 27 / 160, 0,
                cxClient / 2 - cyClient * 27 / 160, cyClient
                );
            Pie(hdc,
                cxClient / 2 + cyClient * 5 / 32, cyClient * 39 / 80,
                cxClient / 2 + cyClient * 29 / 160, cyClient * 41 / 80,
                cxClient / 2 + cyClient * 27 / 160, cyClient,
                cxClient / 2 + cyClient * 27 / 160, 0
                );
            SelectObject(hdc, hOldPen);
            SelectObject(hdc, hOldBrush);
            // crispening
            LPPOINT nlp;
            GetCurrentPositionEx(hdc, nlp);
            MoveToEx(hdc, cxClient / 2 - cyClient * 27 / 160, cyClient * 39 / 80, nlp);
            LineTo(hdc, cxClient / 2 + cyClient * 27 / 160, cyClient * 39 / 80);
            GetCurrentPositionEx(hdc, nlp);
            MoveToEx(hdc, cxClient / 2 + cyClient * 27 / 160, cyClient * 41 / 80, nlp);
            LineTo(hdc, cxClient / 2 - cyClient * 27 / 160, cyClient * 41 / 80);

            Arc(hdc,
                cxClient / 2 - cyClient * 29 / 160, cyClient * 39 / 80,
                cxClient / 2 - cyClient * 5 / 32, cyClient * 41 / 80,
                cxClient / 2 - cyClient * 27 / 160, 0,
                cxClient / 2 - cyClient * 27 / 160, cyClient
            );
            Arc(hdc,
                cxClient / 2 + cyClient * 5 / 32, cyClient * 39 / 80,
                cxClient / 2 + cyClient * 29 / 160, cyClient * 41 / 80,
                cxClient / 2 + cyClient * 27 / 160, cyClient,
                cxClient / 2 + cyClient * 27 / 160, 0
            );

            /*************************************** the bell of necklace ****************************************/
            // D = 50
            hBrush = CreateSolidBrush(RGB( 255, 241, 67));
            hOldBrush = static_cast<HBRUSH>(SelectObject(hdc, hBrush));
            Ellipse(hdc,
                    cxClient / 2 - cyClient / 32, cyClient / 2,
                    cxClient / 2 + cyClient / 32, cyClient * 9 / 16
                    );
            SelectObject(hdc, hOldBrush);

            MoveToEx(hdc, cxClient / 2 - cyClient / 32, cyClient * 17 / 32, nullptr);
            LineTo(hdc, cxClient / 2 + cyClient / 32, cyClient *17 / 32);
            MoveToEx(hdc, cxClient / 2 - cyClient * 49 / 1600, cyClient * 21 / 40, nullptr);
            LineTo(hdc, cxClient / 2 + cyClient * 49 / 1600, cyClient *21 / 40);

            hBrush = CreateSolidBrush(RGB( 255, 30, 35));
            hOldBrush = static_cast<HBRUSH>(SelectObject(hdc, hBrush));
            Ellipse(hdc,
                    cxClient / 2 - cyClient / 160, cyClient * 173 / 320,
                    cxClient / 2 + cyClient / 160, cyClient * 177 / 320
                    );
            SelectObject(hdc, hOldBrush);
            MoveToEx(hdc, cxClient / 2 , cyClient * 177 / 320, nullptr);
            LineTo(hdc, cxClient / 2 , cyClient * 9 / 16);

            /*************************************** hands ****************************************/
            // left
            Ellipse(hdc,
                    cxClient / 2 - cyClient * 21 / 80, cyClient * 23 / 40,
                    cxClient / 2 - cyClient * 3 / 16, cyClient * 13 / 20
                    );
            // right
            Ellipse(hdc,
                    cxClient / 2 + cyClient * 21 / 80, cyClient * 23 / 40,
                    cxClient / 2 + cyClient * 3 / 16, cyClient * 13 / 20
                    );

            /*************************************** legs ****************************************/
            // between (400, 615)

            Ellipse(hdc,
                    cxClient / 2 - cyClient * 3 / 80, cyClient * 117 / 160,
                    cxClient / 2 + cyClient * 3 / 80, cyClient * 129 / 160
                    );
            hPen = CreatePen(PS_SOLID, 0, RGB(255, 255, 255));
            hOldPen = static_cast<HPEN>(SelectObject(hdc, hPen));
            Arc(hdc,
                cxClient / 2 - cyClient * 3 / 80, cyClient * 117 / 160,
                cxClient / 2 + cyClient * 3 / 80, cyClient * 129 / 160,
                0, cyClient * 123 / 160,
                cxClient, cyClient * 123 / 160
                );
            SelectObject(hdc, hOldPen);
            // left
            Ellipse(hdc,
                    cxClient / 2 - cyClient * 3 / 16, cyClient * 29 / 40,
                    cxClient / 2 - cyClient / 40, cyClient * 4 / 5
                    );

            // right
            Ellipse(hdc,
                    cxClient / 2 + cyClient / 40, cyClient * 29 / 40,
                    cxClient / 2 + cyClient * 3 / 16, cyClient * 4 / 5
            );

            EndPaint(hwnd, &ps);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, message, wparam, lparam);
}

