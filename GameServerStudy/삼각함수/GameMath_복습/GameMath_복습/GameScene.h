#pragma once
#include "Scene.h"

// 9~11. DevScene, EditScene, GameScene »ý¼º
class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

};

