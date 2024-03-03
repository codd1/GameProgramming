#pragma once
#include "ResourceBase.h"

class Texture;

// ��Ʈ�� �׸��� �߶� ���� �� �� �ְ� �ϴ� Ŭ����
class Sprite : public ResourceBase
{
public:
	Sprite(Texture* texture, int32 x, int32 y, int32 cx, int32 cy);
	virtual ~Sprite() override;

public:
	HDC GetDC();
	int32 GetTransparent();

	Vec2Int GetPos() { return Vec2Int{ _x, _y }; }
	Vec2Int GetSize() { return Vec2Int{ _cx, _cy }; }

private:
	Texture* _texture = nullptr;
	int32 _x = 0;
	int32 _y = 0;
	int32 _cx = 0;
	int32 _cy = 0;
};

