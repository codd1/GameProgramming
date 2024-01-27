#pragma once
#include "ResourceBase.h"

// 31. LineMesh Ŭ���� ���� + Save, Load �Լ� ����
class LineMesh : public ResourceBase
{
public:
	void Save(wstring path);
	void Load(wstring path);

	void Render(HDC hdc, Pos pos) const;

protected:
	vector<pair<POINT, POINT>> _lines;

	int32 _width = 0;
	int32 _height = 0;
};

