#pragma once
#include "Scene.h"

// 61. FortressScene 클래스 생성
class FortressScene : public Scene
{
public:
	FortressScene();
	virtual ~FortressScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	// 77. 턴 변경 함수 추가/구현 + 필요한 멤버변수 추가
	void ChangePlayerTurn();
private:
	int32 _playerTurn = 1;
	float _sumTime = 0.f;
};

