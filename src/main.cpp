#include "Game.h"
#include "GameAPI.Internal.h"

#include <chrono>
#include <windows.h>

namespace {
constexpr wchar_t WindowClassName[] = L"EngineTrainingWindow";
constexpr wchar_t WindowTitle[] = L"Unreal Engine Developer Training";
constexpr int ClientWidth = 800;
constexpr int ClientHeight = 600;

LRESULT CALLBACK WindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam) {
    switch (Message) {
    case WM_KEYDOWN:
        GameAPIInternal::SetKeyState(WParam, true);
        return 0;
    case WM_KEYUP:
        GameAPIInternal::SetKeyState(WParam, false);
        return 0;
    case WM_KILLFOCUS:
        for (WPARAM Key : {VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN, VK_SPACE}) {
            GameAPIInternal::SetKeyState(Key, false);
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(Window, Message, WParam, LParam);
}
}

int WINAPI wWinMain(HINSTANCE Instance, HINSTANCE, PWSTR, int ShowCommand) {
    WNDCLASSEXW WindowClass{};
    WindowClass.cbSize = sizeof(WindowClass);
    WindowClass.lpfnWndProc = WindowProc;
    WindowClass.hInstance = Instance;
    WindowClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    WindowClass.lpszClassName = WindowClassName;
    if (!RegisterClassExW(&WindowClass)) return 1;

    const DWORD WindowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
    RECT WindowRect{0, 0, ClientWidth, ClientHeight};
    AdjustWindowRect(&WindowRect, WindowStyle, FALSE);

    HWND Window = CreateWindowExW(
        0, WindowClassName, WindowTitle, WindowStyle,
        CW_USEDEFAULT, CW_USEDEFAULT,
        WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top,
        nullptr, nullptr, Instance, nullptr);
    if (!Window) return 1;

    ShowWindow(Window, ShowCommand);
    HDC WindowCanvas = GetDC(Window);
    HDC BackBuffer = CreateCompatibleDC(WindowCanvas);
    HBITMAP BackBitmap = CreateCompatibleBitmap(WindowCanvas, ClientWidth, ClientHeight);
    HGDIOBJ OldBitmap = SelectObject(BackBuffer, BackBitmap);
    GameAPIInternal::SetCanvas(BackBuffer, ClientWidth, ClientHeight);

    Game::BeginPlay();
    auto PreviousTime = std::chrono::steady_clock::now();
    bool bIsRunning = true;

    while (bIsRunning) {
        MSG Message{};
        while (PeekMessageW(&Message, nullptr, 0, 0, PM_REMOVE)) {
            if (Message.message == WM_QUIT) bIsRunning = false;
            TranslateMessage(&Message);
            DispatchMessageW(&Message);
        }
        if (!bIsRunning) break;

        const auto CurrentTime = std::chrono::steady_clock::now();
        const float DeltaTime = std::chrono::duration<float>(CurrentTime - PreviousTime).count();
        PreviousTime = CurrentTime;

        Game::Tick(DeltaTime);
        Game::DrawHUD();
        BitBlt(WindowCanvas, 0, 0, ClientWidth, ClientHeight, BackBuffer, 0, 0, SRCCOPY);
        Sleep(1);
    }

    SelectObject(BackBuffer, OldBitmap);
    DeleteObject(BackBitmap);
    DeleteDC(BackBuffer);
    ReleaseDC(Window, WindowCanvas);
    return 0;
}
