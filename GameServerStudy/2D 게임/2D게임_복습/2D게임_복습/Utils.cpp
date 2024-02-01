#include "pch.h"
#include "Utils.h"

void Utils::DrawText(HDC hdc, Pos pos, const wstring& str)
{
	::TextOut(hdc, pos.x, pos.y, str.c_str(), static_cast<int32>(str.size()));
}

void Utils::DrawRect(HDC hdc, Pos pos, int32 width, int32 height)
{
	// Rectangle(hdc, left, top, right, bottom);
	// left: 왼쪽 상단 모서리의 x 좌표, top: y좌표
	// right 오른쪽 하단 모서리의 x좌표, bottom: y좌표
	::Rectangle(hdc, pos.x - width / 2, pos.y - height / 2, pos.x + width / 2, pos.y + height / 2);
}

void Utils::DrawCircle(HDC hdc, Pos pos, int32 radius)
{
	::Ellipse(hdc, pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius);
}

void Utils::DrawLine(HDC hdc, Pos from, Pos to)
{
	// 두 함수가 같이 쓰임
	::MoveToEx(hdc, from.x, from.y, nullptr);	// 선을 그리기 전에 시작점 지정
	::LineTo(hdc, to.x, to.y);					// ::MoveToEx에서 지정한 시작점부터 새로운 지점인 to까지 선을 그림
}
