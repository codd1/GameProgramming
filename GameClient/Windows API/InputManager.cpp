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
		// 키가 눌려있으면 true
		if (asciiKeys[key] & 0x80) {		// ::GetKeyboardState() 함수 문서에 의거
			KeyState& state = _states[key];

			// 이전 프레임에 키를 누른 상태라면 PRESS
			if (state == KeyState::Press || state == KeyState::Down) {
				state = KeyState::Press;
			}
			else {	// 처음이라면 DOWN
				state = KeyState::Down;
			}
		}
		// 키보드를 뗀 경우
		else {
			KeyState& state = _states[key];

			// 이전 프레임에 키를 누른 상태라면 UP (= 누르다가 뗀 경우)
			if (state == KeyState::Press || state == KeyState::Down) {
				state = KeyState::Up;
			}
			else {
				state = KeyState::None;
			}
		}
	}

	// Mouse
	::GetCursorPos(&_mousePos);		// 커서의 좌표를 알아온다.
	::ScreenToClient(_hwnd, &_mousePos);	// 창 기준으로 한 마우스 Pos로 바꿔줌
}
