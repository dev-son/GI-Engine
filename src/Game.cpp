#include "Game.h"
#include "GameAPI.h"

namespace {
	float PlayerX = 375.0f;
	float PlayerY = 275.0f;
	constexpr float PlayerSize = 50.0f;
	constexpr float MoveSpeed = 250.0f;
	constexpr float BoostMultiplier = 2.0f;
	constexpr float ScreenWidth = 800.0f;
	constexpr float ScreenHeight = 600.0f;
}

namespace Game {

	// Unreal의 AActor::BeginPlay처럼 시작할 때 한 번 호출됩니다.
	void BeginPlay() {}

	// Unreal의 AActor::Tick처럼 매 프레임 호출됩니다.
	void Tick(float DeltaTime) {
		float CurrentSpeed = MoveSpeed;

		if (IsInputKeyDown(EKey::Space))
		{
			CurrentSpeed *= BoostMultiplier;
		}
		if (IsInputKeyDown(EKey::Left))  PlayerX -= CurrentSpeed * DeltaTime;
		if (IsInputKeyDown(EKey::Right)) PlayerX += CurrentSpeed * DeltaTime;
		if (IsInputKeyDown(EKey::Up))    PlayerY -= CurrentSpeed * DeltaTime;
		if (IsInputKeyDown(EKey::Down))  PlayerY += CurrentSpeed * DeltaTime;
		if (PlayerX <= 0.0f)
		{
			PlayerX = 0.0f;
		}
		if (PlayerX >= ScreenWidth - PlayerSize)
		{
			PlayerX = ScreenWidth - PlayerSize;
		}
		if (PlayerY <= 0.0f)
		{
			PlayerY = 0.0f;
		}
		if (PlayerY >= ScreenHeight - PlayerSize)
		{
			PlayerY = ScreenHeight - PlayerSize;
		}
	}

	// Unreal의 AHUD::DrawHUD와 같은 역할로, 매 프레임 화면을 그립니다.
	void DrawHUD() {
		ClearCanvas({ 0, 0, 0 });
		FColor PlayerColor = { 255, 110, 80 };

		if (IsInputKeyDown(EKey::Space))
		{
			PlayerColor = { 255, 0, 0 };
		}

		DrawRect(PlayerColor, PlayerX, PlayerY, PlayerSize, PlayerSize);
	}

}
