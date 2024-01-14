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
	// 반복하지 않는 애니메이션이거나 더이상 실행할게 없으면 return
	if (info.loop == false && _index == info.end) {
		return;
	}

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	int32 frameCount = (info.end - info.start + 1);		// 현재 실행 중인 애니메이션의 총 프레임 갯수
	float delta = info.duration / frameCount;	// 총 애니메이션 움직임 시간
	
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
		(info.start + _index) * info.size.x,	// info의 start에서 얼만큼 경과됐는지
		info.line * info.size.y,
		info.size.x,
		info.size.y,
		info.texture->GetTransparent());
}

void FlipbookActor::SetFlipbook(Flipbook* flipbook)
{
	// 같은 애를 또 사용하려고 하면(반복) 문제 상황으로 인식
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
