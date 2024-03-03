#pragma once
#include "Scene.h"

// 60. MenuScene 클래스 생성
class MenuScene : public Scene
{
public:
	MenuScene();
	virtual ~MenuScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};

