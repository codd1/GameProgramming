#include "pch.h"
#include "InputManager.h"

void InputManager::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_states.resize(KEY_TYPE_COUNT, KeyState::None);		// 벡터의 크기 변경
}

// 17. InputManager::Update() 구현
// 키보드에 대한 정보를 업데이트하고 각 키의 상태를 _states 벡터에 기록
void InputManager::Update()
{
	BYTE asciiKeys[KEY_TYPE_COUNT] = {};	// 키보드의 모든 키를 나타내는 배열
	if (::GetKeyboardState(asciiKeys) == false) {
		return;
	}

	// 키보드의 모든 키를 다 도는 루프
	for (uint32 key = 0; key < KEY_TYPE_COUNT; key++) {
		if (asciiKeys[key] & 0x80) {	// 0x80 = 해당 비트가 설정되어 있는지 확인하는 비트 마스크. (설정되어있다 = 해당 키가 눌려져있다)
			KeyState& state = _states[key];

			// 키가 눌려져있었거나 또는 키가 여전히 눌려져 있는 경우
			if (state == KeyState::Press || state == KeyState::Down) {
				state = KeyState::Press;
			}
			else {	// 현재 키가 눌려지지 않은 경우
				state = KeyState::Down;
			}
		}
		else {		// 해당 키가 눌려져 있지 않은 경우
			KeyState& state = _states[key];

			// 이전에 눌려져있었을 경우
			if (state == KeyState::Press || state == KeyState::Down) {
				state = KeyState::Up;
			}
			else {	// 여전히 눌려져 있지 않은 경우
				state = KeyState::None;
			}
		}
	}

	// Mouse
	::GetCursorPos(&_mousePos);		// 커서의 좌표
	::ScreenToClient(_hwnd, &_mousePos);	// 창 기준으로 한 마우스 Pos로 바꿔줌
}
