#pragma once
#include "ResourceBase.h"

// 31. LineMesh Ŭ���� ���� + Save, Load �Լ� ����
class LineMesh : public ResourceBase
{
public:
	void Save(wstring path);
	void Load(wstring path);

	// 75. UI ũ�� ������ ���� �Ű����� �߰� + �Լ� ���� ����
	void Render(HDC hdc, Pos pos, float ratioX = 1.f, float ratioY = 1.f) const;

protected:
	vector<pair<POINT, POINT>> _lines;

	int32 _width = 0;
	int32 _height = 0;
};

