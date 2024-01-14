#include "pch.h"
#include "SpriteActor.h"
#include "Sprite.h"

SpriteActor::SpriteActor()
{
}

SpriteActor::~SpriteActor()
{
}

// 혹시라도 중요한 코드가 부모 클래스에 있을 수 있으니,
// (override한) 자식 클래스 함수에서 부모 클래스의 함수를 한 번씩 호출해주는게 좋다.
void SpriteActor::BeginPlay()
{
	Super::BeginPlay();
}

void SpriteActor::Tick()
{
	Super::Tick();
}

void SpriteActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_sprite == nullptr) {
		return;
	}

	Vec2Int size = _sprite->GetSize();

	//::BitBlt(hdc,
	//	(int32)_pos.x - size.x / 2,		// 플레이어 위치를 기준으로 비트맵 그림 복사
	//	(int32)_pos.y - size.y / 2,
	//	size.x,
	//	size.y,
	//	_sprite->GetDC(),
	//	_sprite->GetPos().x,
	//	_sprite->GetPos().y,
	//	SRCCOPY);

	::TransparentBlt(hdc,
		(int32)_pos.x - size.x / 2,		// 플레이어 위치를 기준으로 비트맵 그림 복사
		(int32)_pos.y - size.y / 2,
		size.x,
		size.y,
		_sprite->GetDC(),
		_sprite->GetPos().x,
		_sprite->GetPos().y,
		_sprite->GetSize().x,
		_sprite->GetSize().y,
		_sprite->GetTransparent());
}
