#include "pch.h"
#include "FlipbookActor.h"
#include "Flipbook.h"
#include "Sprite.h"
#include "TimeManager.h"
#include "SceneManager.h"

FlipbookActor::FlipbookActor()
{
}

FlipbookActor::~FlipbookActor()
{
}

void FlipbookActor::BeginPlay()
{
	Super::BeginPlay();
}

void FlipbookActor::Tick()
{
	Super::Tick();

	if (_flipbook == nullptr) {
		return;
	}

	const FlipbookInfo& info = _flipbook->GetInfo();
	// �ݺ����� �ʴ� �ִϸ��̼��̰ų� ���̻� �����Ұ� ������ return
	if (info.loop == false && _index == info.end) {
		return;
	}

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	int32 frameCount = (info.end - info.start + 1);		// ���� ���� ���� �ִϸ��̼��� �� ������ ����
	float delta = info.duration / frameCount;	// �� �ִϸ��̼� ������ �ð�
	
	if (_sumTime >= delta) {
		_sumTime = 0.f;
		_index = (_index + 1) % frameCount;
	}
}

void FlipbookActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_flipbook == nullptr) {
		return;
	}

	const FlipbookInfo& info = _flipbook->GetInfo();

	::TransparentBlt(hdc,
		(int32)_pos.x - info.size.x / 2,
		(int32)_pos.y - info.size.y / 2,
		info.size.x,
		info.size.y,
		info.texture->GetDC(),
		(info.start + _index) * info.size.x,	// info�� start���� ��ŭ ����ƴ���
		info.line * info.size.y,
		info.size.x,
		info.size.y,
		info.texture->GetTransparent());
}

void FlipbookActor::SetFlipbook(Flipbook* flipbook)
{
	// ���� �ָ� �� ����Ϸ��� �ϸ�(�ݺ�) ���� ��Ȳ���� �ν�
	if (flipbook && _flipbook == flipbook) {
		return;
	}
	_flipbook = flipbook;
	Reset();
}

void FlipbookActor::Reset()
{
	_sumTime = 0.f;
	_index = 0;
}
