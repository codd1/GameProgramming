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

	// = �� �ڽŰ� Button::OnClickButton�� �������ּ���
	AddOnClickDelegate(this, &Button::OnClickButton);
}

void Button::Tick()
{
	Super::Tick();

	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// Ŭ�� ���·� �ٲ� ���� �ٽ� ������� �ٲ��� �ϴϱ�
	// 0.1�� �ڿ� �ٽ� ���ƿ����� ó��
	if (_state == BS_Clicked) {
		_sumTime += deltaTime;
		if (_sumTime >= 0.2f) {
			_sumTime = 0.f;
			SetButtonState(BS_Default);
		}
	}

	if (IsMouseInRect()) {	// ���콺 ��ġ�� �ﰢ�� �ȿ� �ִ� ���
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
		// �簢�� �ȿ��� Ŭ�� �� ���콺�� ���� ���� �ʴٰ� �簢�� �ٱ����� ���� �Ǹ�
		// �簢�� ���� �ȿ��� Ŭ���Ѱ� �ƴ϶�� ó��
		SetButtonState(BS_Default);
	}
}

void Button::Render(HDC hdc)
{
	Super::Render(hdc);

	// sprite�� �ִٸ� �׸��� �ƴ϶�� ���Ƿ� �簢���� �׷��ش�.
	if (_currentSprite) {
		// ī�޶� ������ ������ �ȵȴ�.
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
