#pragma once
#include "ResourceBase.h"

class Texture;

// 비트맵 그림을 쉽게 잘라서 쓸 수 있게 하는 클래스
class Sprite : public ResourceBase
{
public:
	Sprite(Texture* texture, int32 x, int32 y, int32 cx, int32 cy);
	virtual ~Sprite();

	HDC GetDC();
	int32 GetTransparent();
	Vec2Int GetPos() { return Vec2Int{ _x, _y }; }
	Vec2Int GetSize() { return Vec2Int{ _cx, _cy }; }

private:
	Texture* _texture = nullptr;
	int32 _x;
	int32 _y;
	int32 _cx;
	int32 _cy;
};

