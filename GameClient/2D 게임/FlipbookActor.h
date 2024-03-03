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
	// Flipbook���� FlipbookInfo�� ��� ���ҽ����� �� ���������� Ȱ���ϴ� �����̰�,
	// ���������� �� ���ҽ��� ����ؼ� �÷����ϴ� �� ���� ��ü�� �÷��̾�� �ٸ���.
	// ���ҽ� = �����̶�� ������, ����ϴ°� mp3��� �ϸ� ���� �뷡����ϴ��� mp3���� ���� ���̴� ������ �ð� ������ �ٸ� �� �ִ� ������ �����ϸ� �ȴ�.
	// �׷��� FlipbookActor���� �����ϴ� index ���� ������ �д�.
	float _sumTime = 0.f;
	int32 _index = 0;		// ���� ����� �� ��° �̹����� ��������ϴ��� (���� ����� ���ҽ��� �� �ٷ� �� �ִٰ� ����)
};

