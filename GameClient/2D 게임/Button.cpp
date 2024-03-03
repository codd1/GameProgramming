#include "pch.h"
#include "Button.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Sprite.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::BeginPlay()
{
	Super::BeginPlay();

	SetButtonState(BS_Default);

	// = 내 자신과 Button::OnClickButton을 연결해주세요
	AddOnClickDelegate(this, &Button::OnClickButton);
}

void Button::Tick()
{
	Super::Tick();

	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 클릭 상태로 바뀐 다음 다시 원래대로 바뀌어야 하니까
	// 0.1초 뒤에 다시 돌아오도록 처리
	if (_state == BS_Clicked) {
		_sumTime += deltaTime;
		if (_sumTime >= 0.2f) {
			_sumTime = 0.f;
			SetButtonState(BS_Default);
		}
	}

	if (IsMouseInRect()) {	// 마우스 위치가 삼각형 안에 있는 경우
		if (GET_SINGLE(InputManager)->GetButton(KeyType::LeftMouse)) {
			SetButtonState(BS_Pressed);
			// OnPressed
		}
		else {
			if (_state == BS_Pressed) {
				SetButtonState(BS_Clicked);
				// OnClicked
				if (_onClick) {
					_onClick();
				}
			}
		}
	}
	else {
		// 사각형 안에서 클릭 후 마우스를 떼고 있지 않다가 사각형 바깥에서 떼게 되면
		// 사각형 범위 안에서 클릭한게 아니라고 처리
		SetButtonState(BS_Default);
	}
}

void Button::Render(HDC hdc)
{
	Super::Render(hdc);

	// sprite가 있다면 그리고 아니라면 임의로 사각형을 그려준다.
	if (_currentSprite) {
		// 카메라 영향을 받으면 안된다.
		::TransparentBlt(hdc,
			(int32)_pos.x - _size.y / 2,
			(int32)_pos.y - _size.y / 2,
			_size.x,
			_size.y,
			_currentSprite->GetDC(),
			_currentSprite->GetPos().x,
			_currentSprite->GetPos().y,
			_currentSprite->GetSize().x,
			_currentSprite->GetSize().y,
			_currentSprite->GetTransparent()
		);
	}
	else {
		Utils::DrawRect(hdc, _pos, _size.x, _size.y);
	}
}

void Button::SetButtonState(ButtonState state)
{
	_state = state;

	if (_sprites[state]) {
		SetCurrentSprite(_sprites[state]);
	}
}
