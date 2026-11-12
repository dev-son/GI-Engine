#pragma once
#include <windows.h>

namespace GameAPIInternal {
void SetCanvas(HDC Canvas, int Width, int Height);
void SetKeyState(WPARAM VirtualKey, bool bIsDown);
}
