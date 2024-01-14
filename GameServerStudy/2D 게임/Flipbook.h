#pragma once
#include "ResourceBase.h"
#include "Texture.h"

struct FlipbookInfo {
	Texture* texture = nullptr;
	wstring name;
	Vec2Int size = {};		// 리소스(비트맵 이미지)에서 한 칸의 크기
	int32 start = 0;	// 리소스(비트맵 이미지)에서 시작 위치
	int32 end = 0;		// 리소스(비트맵 이미지)에서 몇 번째 줄에 위치하는지
	int32 line = 0;		// 몇 개까지 가는지
	float duration = 1.f;	// 애니메이션 속도
	bool loop = true;		// 애니메이션 반복 여부
};
class Flipbook : public ResourceBase
{
public:
	Flipbook();
	virtual ~Flipbook();

	void SetInfo(const FlipbookInfo& info) { _info = info; }
	const FlipbookInfo& GetInfo() { return _info; }

private:
	FlipbookInfo _info;

};

