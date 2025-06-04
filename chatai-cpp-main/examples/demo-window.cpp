#define _CRT_SECURE_NO_WARNINGS

#include "openai_chat.hpp"
#include <string>
#include <Windows.h>

#define IDC_EDIT 101
#define IDC_STATIC 102
#define IDC_BUTTON 103
std::string api_key = "YOUR_API_KEY";
std::string url = "YOUR_URL";
std::string model = "gpt-3.5-turbo";
// 窗口过程函数 (Window process function)
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
    static HWND hEdit, hStatic, hButton;

    switch (message) 
    {
    case WM_CREATE: 
    {
        // 创建一个EDIT控件 (Create an edit box)
        hEdit = CreateWindowEx(0, L"EDIT", NULL,
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            10, 10, 600, 150,
            hwnd, (HMENU)IDC_EDIT, NULL, NULL);

        // 创建一个用于展示回复的窗口(Create a text display box)
        hStatic = CreateWindowEx(0, L"Static", NULL,
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            10, 180, 600, 220,
            hwnd, (HMENU)IDC_STATIC, NULL, NULL);

        // 创建一个按钮(create button)
        hButton = CreateWindowEx(0, L"BUTTON", L"询问（ASK）",
            WS_CHILD | WS_VISIBLE,
            630, 10, 100, 25,
            hwnd, (HMENU)IDC_BUTTON, NULL, NULL);
        break;
    }
    case WM_COMMAND: 
    {
        if (LOWORD(wParam) == IDC_BUTTON) 
        {
            // 获取询问文本 (Retrieve text from EDIT)
            wchar_t buffer[256];
            GetWindowText(hEdit, buffer, sizeof(buffer) / sizeof(wchar_t));
            ChatAI::ChatAI ai(api_key, url, model);
            std::wstring buf = buffer;
            std::wstring ans = ai.askW(buf);
            // 将回复显示在STATIC上 (Set the text to MATIC)
            SetWindowText(hStatic, ans.c_str());
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // 注册窗口类 (Register window class)
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"Class_ChatAI";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    // 创建主窗口 (Create window)
    HWND hwnd = CreateWindowEx(
        0, L"Class_ChatAI", L"ChatAI - Window",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 750, 450,
        NULL, NULL, hInstance, NULL);

    // 消息循环 (Message loop)
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) 
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}
