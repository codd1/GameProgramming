#pragma once
#include "UI.h"

class Sprite;

// UI들을 관리하는 UI 시트라고 볼 수 있다
class Panel : public UI
{
	using Super = UI;
public:
	Panel();
	virtual ~Panel();

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	void AddChild(UI* ui);
	bool RemoveChild(UI* ui);

private:
	vector<UI*> _children;
};

