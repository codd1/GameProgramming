#include "pch.h"
#include "SpriteActor.h"
#include "Sprite.h"

SpriteActor::SpriteActor()
{
}

SpriteActor::~SpriteActor()
{
}

// Ȥ�ö� �߿��� �ڵ尡 �θ� Ŭ������ ���� �� ������,
// (override��) �ڽ� Ŭ���� �Լ����� �θ� Ŭ������ �Լ��� �� ���� ȣ�����ִ°� ����.
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
	//	(int32)_pos.x - size.x / 2,		// �÷��̾� ��ġ�� �������� ��Ʈ�� �׸� ����
	//	(int32)_pos.y - size.y / 2,
	//	size.x,
	//	size.y,
	//	_sprite->GetDC(),
	//	_sprite->GetPos().x,
	//	_sprite->GetPos().y,
	//	SRCCOPY);

	::TransparentBlt(hdc,
		(int32)_pos.x - size.x / 2,		// �÷��̾� ��ġ�� �������� ��Ʈ�� �׸� ����
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
