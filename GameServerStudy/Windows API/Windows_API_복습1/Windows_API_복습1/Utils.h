#pragma once

// 23. DevScene::Render() 함수 구현 전 Utils 클래스 구현
// 만들고 pch.h에 추가
class Utils
{
public:
	static void DrawText(HDC hdc, Pos pos, const wstring& str);

	static void DrawRect(HDC hdc, Pos pos, int32 width, int32 height);

	static void DrawCircle(HDC hdc, Pos pos, int32 radius);

	static void DrawLine(HDC hdc, Pos from, Pos to);
};

