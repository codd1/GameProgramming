#pragma once
#include "Scene.h"

// 좌표를 하나씩 찍어서 그림을 그린 다음에 그 좌표 그대로 파일로 저장하기 위한 클래스
class EditScene : public Scene
{
public:
	EditScene();
	virtual ~EditScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	// pair인 이유? 선이기 때문에. (어디서부터 어디까지)
	vector<pair<POINT, POINT>> _lines;

	bool _isFirst = true;		// 처음 찍는지? = lastPos가 있는지?
	POINT _lastPos = {};	// 이전에 찍은 좌표
};

