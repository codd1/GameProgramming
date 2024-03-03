#pragma once
#include "Actor.h"

class Flipbook;

class FlipbookActor : public Actor
{
	using Super = Actor;
public:
	FlipbookActor();
	virtual ~FlipbookActor() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	void SetFlipbook(Flipbook* flipbook);
	void Reset();

protected:
	Flipbook* _flipbook = nullptr;
	// Flipbook에서 FlipbookInfo는 모든 리소스들이 다 공통적으로 활용하는 정보이고,
	// 실질적으로 이 리소스를 사용해서 플레이하는 그 상태 자체는 플레이어마다 다르다.
	// 리소스 = 음반이라고 따지고, 사용하는게 mp3라고 하면 같은 노래라고하더라도 mp3별로 실행 중이던 음반의 시간 같은게 다를 수 있는 것으로 생각하면 된다.
	// 그래서 FlipbookActor에도 관리하는 index 같은 변수를 둔다.
	float _sumTime = 0.f;
	int32 _index = 0;		// 같은 모션의 몇 번째 이미지를 보여줘야하는지 (같은 모션의 리소스가 한 줄로 쭉 있다고 가정)
};

