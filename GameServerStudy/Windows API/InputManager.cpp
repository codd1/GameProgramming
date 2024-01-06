#include "pch.h"
#include "inputManager.h"

void InputManager::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_states.resize(KEY_TYPE_COUNT, KeyState::None);
}

void InputManager::Update()
{
	BYTE asciiKeys[KEY_TYPE_COUNT] = {};
	if (::GetKeyboardState(asciiKeys) == false) {
		return;
	}

	for (uint32 key = 0; key < KEY_TYPE_COUNT; key++) {
		// Ű�� ���������� true
		if (asciiKeys[key] & 0x80) {		// ::GetKeyboardState() �Լ� ������ �ǰ�
			KeyState& state = _states[key];

			// ���� �����ӿ� Ű�� ���� ���¶�� PRESS
			if (state == KeyState::Press || state == KeyState::Down) {
				state = KeyState::Press;
			}
			else {	// ó���̶�� DOWN
				state = KeyState::Down;
			}
		}
		// Ű���带 �� ���
		else {
			KeyState& state = _states[key];

			// ���� �����ӿ� Ű�� ���� ���¶�� UP (= �����ٰ� �� ���)
			if (state == KeyState::Press || state == KeyState::Down) {
				state = KeyState::Up;
			}
			else {
				state = KeyState::None;
			}
		}
	}

	// Mouse
	::GetCursorPos(&_mousePos);		// Ŀ���� ��ǥ�� �˾ƿ´�.
	::ScreenToClient(_hwnd, &_mousePos);	// â �������� �� ���콺 Pos�� �ٲ���
}
