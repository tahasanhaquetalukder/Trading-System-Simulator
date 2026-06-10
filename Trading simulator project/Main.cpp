#include <windows.h>
#include <string>

#define IDC_BUY_BUTTON  101
#define IDC_SELL_BUTTON 102

HWND hPriceLabel, hStatusLabel;
double currentPrice = 150.75;

// রঙের জন্য ব্রাশ (Brushes) তৈরি
HBRUSH hDarkBackgroundBrush;
HBRUSH hGreenBrush;
HBRUSH hRedBrush;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_BUY_BUTTON) {
            currentPrice += 1.25;
            std::wstring priceStr = L"AAPL - Live Price: $" + std::to_wstring(currentPrice).substr(0, 6);
            SetWindowText(hPriceLabel, priceStr.c_str());
            SetWindowText(hStatusLabel, L"Status: BUY Order Executed Successfully!");
        }
        else if (LOWORD(wParam) == IDC_SELL_BUTTON) {
            currentPrice -= 1.15;
            std::wstring priceStr = L"AAPL - Live Price: $" + std::to_wstring(currentPrice).substr(0, 6);
            SetWindowText(hPriceLabel, priceStr.c_str());
            SetWindowText(hStatusLabel, L"Status: SELL Order Executed Successfully!");
        }
        return 0;

    case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        // টেক্সটের পেছনের ব্যাকগ্রাউন্ড কালার ডার্ক করা
        SetBkColor(hdcStatic, RGB(30, 30, 30));

        // লাইভ প্রাইস টেক্সটের কালার হালকা সবুজ/হলুদ করা
        if ((HWND)lParam == hPriceLabel) {
            SetTextColor(hdcStatic, RGB(0, 255, 128));
        }
        else {
            SetTextColor(hdcStatic, RGB(200, 200, 200)); // সাধারণ টেক্সট সাদাটে হবে
        }
        return (INT_PTR)hDarkBackgroundBrush;
    }

    case WM_DRAWITEM:
    {
        LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
        if (pDIS->CtlID == IDC_BUY_BUTTON) {
            // BUY বাটনটি সবুজ রঙে আঁকা হচ্ছে
            FillRect(pDIS->hDC, &pDIS->rcItem, hGreenBrush);
            SetTextColor(pDIS->hDC, RGB(255, 255, 255)); // লেখার রঙ সাদা
            SetBkMode(pDIS->hDC, TRANSPARENT);
            DrawText(pDIS->hDC, L"BUY", -1, &pDIS->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
        else if (pDIS->CtlID == IDC_SELL_BUTTON) {
            // SELL বাটনটি লাল রঙে আঁকা হচ্ছে
            FillRect(pDIS->hDC, &pDIS->rcItem, hRedBrush);
            SetTextColor(pDIS->hDC, RGB(255, 255, 255)); // লেখার রঙ সাদা
            SetBkMode(pDIS->hDC, TRANSPARENT);
            DrawText(pDIS->hDC, L"SELL", -1, &pDIS->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
        return TRUE;
    }

    case WM_DESTROY:
        // মেমোরি খালি করার জন্য ব্রাশগুলো ডিলিট করা
        DeleteObject(hDarkBackgroundBrush);
        DeleteObject(hGreenBrush);
        DeleteObject(hRedBrush);
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    // রঙগুলোর মান ঠিক করা (RGB: Red, Green, Blue)
    hDarkBackgroundBrush = CreateSolidBrush(RGB(30, 30, 30)); // ডার্ক থিম
    hGreenBrush = CreateSolidBrush(RGB(46, 204, 113));        // সুন্দর সবুজ
    hRedBrush = CreateSolidBrush(RGB(231, 76, 60));           // সুন্দর লাল

    const wchar_t CLASS_NAME[] = L"TradingSimulatorWindow";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = hDarkBackgroundBrush; // মূল উইন্ডো ডার্ক হবে

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, L"Pro Trading Dashboard",
        WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, // সাইজ ফিক্সড রাখার জন্য
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 400, NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) return 0;

    hPriceLabel = CreateWindowEx(
        0, L"STATIC", L"AAPL - Live Price: $150.75",
        WS_VISIBLE | WS_CHILD | SS_CENTER,
        50, 50, 380, 40, hwnd, NULL, hInstance, NULL
    );

    HFONT hFont = CreateFont(28, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
    SendMessage(hPriceLabel, WM_SETFONT, (WPARAM)hFont, TRUE);

    // BS_OWNERDRAW দেওয়া হয়েছে যাতে আমরা নিজেদের মতো বাটনটি কালার (WM_DRAWITEM) করতে পারি
    HWND hBuyButton = CreateWindowEx(
        0, L"BUTTON", L"BUY",
        WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
        80, 150, 140, 50, hwnd, (HMENU)IDC_BUY_BUTTON, hInstance, NULL
    );

    HWND hSellButton = CreateWindowEx(
        0, L"BUTTON", L"SELL",
        WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
        260, 150, 140, 50, hwnd, (HMENU)IDC_SELL_BUTTON, hInstance, NULL
    );

    hStatusLabel = CreateWindowEx(
        0, L"STATIC", L"Status: Ready to Trade",
        WS_VISIBLE | WS_CHILD | SS_LEFT,
        50, 260, 380, 30, hwnd, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}