#include "GameAPI.h"
#include "GameAPI.Internal.h"

#include <algorithm>
#include <array>
#include <windows.h>

namespace {
HDC CurrentCanvas = nullptr;
int CanvasWidth = 0;
int CanvasHeight = 0;
std::array<bool, 256> KeyStates{};

int ToVirtualKey(EKey Key) {
    switch (Key) {
    case EKey::Left:  return VK_LEFT;
    case EKey::Right: return VK_RIGHT;
    case EKey::Up:    return VK_UP;
    case EKey::Down:  return VK_DOWN;
    case EKey::Space: return VK_SPACE;
    }
    return 0;
}

COLORREF ToColorRef(FColor Color) {
    return RGB(std::clamp(Color.R, 0, 255),
               std::clamp(Color.G, 0, 255),
               std::clamp(Color.B, 0, 255));
}

void Fill(int Left, int Top, int Right, int Bottom, FColor Color) {
    RECT Rectangle{Left, Top, Right, Bottom};
    HBRUSH Brush = CreateSolidBrush(ToColorRef(Color));
    FillRect(CurrentCanvas, &Rectangle, Brush);
    DeleteObject(Brush);
}
}

bool IsInputKeyDown(EKey Key) {
    return KeyStates[ToVirtualKey(Key)];
}

void ClearCanvas(FColor Color) {
    Fill(0, 0, CanvasWidth, CanvasHeight, Color);
}

void DrawRect(FColor Color, float X, float Y, float Width, float Height) {
    Fill(static_cast<int>(X), static_cast<int>(Y),
         static_cast<int>(X + Width), static_cast<int>(Y + Height), Color);
}

void DrawCircle(FColor Color, float CenterX, float CenterY, float Radius) {
    if (Radius <= 0.0f) {
        return;
    }

    const COLORREF NativeColor = ToColorRef(Color);
    HBRUSH Brush = CreateSolidBrush(NativeColor);
    HPEN Pen = CreatePen(PS_SOLID, 1, NativeColor);
    HGDIOBJ PreviousBrush = SelectObject(CurrentCanvas, Brush);
    HGDIOBJ PreviousPen = SelectObject(CurrentCanvas, Pen);

    Ellipse(
        CurrentCanvas,
        static_cast<int>(CenterX - Radius),
        static_cast<int>(CenterY - Radius),
        static_cast<int>(CenterX + Radius),
        static_cast<int>(CenterY + Radius));

    SelectObject(CurrentCanvas, PreviousPen);
    SelectObject(CurrentCanvas, PreviousBrush);
    DeleteObject(Pen);
    DeleteObject(Brush);
}

namespace GameAPIInternal {
void SetCanvas(HDC Canvas, int Width, int Height) {
    CurrentCanvas = Canvas;
    CanvasWidth = Width;
    CanvasHeight = Height;
}

void SetKeyState(WPARAM VirtualKey, bool bIsDown) {
    if (VirtualKey < KeyStates.size()) KeyStates[VirtualKey] = bIsDown;
}
}
