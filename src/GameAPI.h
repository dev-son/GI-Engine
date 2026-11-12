#pragma once

// 지금은 이 파일에 있는 기능만 사용하면 됩니다.
// 내부 구현은 나중에 GameAPI.cpp에서 차근차근 분석합니다.

struct FColor {
    int R;
    int G;
    int B;
};

enum class EKey {
    Left,
    Right,
    Up,
    Down,
    Space
};

bool IsInputKeyDown(EKey Key);
void ClearCanvas(FColor Color);
void DrawRect(FColor Color, float X, float Y, float Width, float Height);
