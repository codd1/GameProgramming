#pragma once
#include "ResourceBase.h"

// 31. LineMesh 클래스 생성 + Save, Load 함수 구현
class LineMesh : public ResourceBase
{
public:
	void Save(wstring path);
	void Load(wstring path);

	// 75. UI 크기 조정을 위해 매개변수 추가 + 함수 내용 수정
	void Render(HDC hdc, Pos pos, float ratioX = 1.f, float ratioY = 1.f) const;

protected:
	vector<pair<POINT, POINT>> _lines;

	int32 _width = 0;
	int32 _height = 0;
};

