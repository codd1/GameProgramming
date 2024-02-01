#pragma once

enum class KeyType {
	// VK = Virtual Key Code
	// 이 값은 주로 Windows의 메시지 처리 함수에서 키 이벤트를 다룰 때 사용된다.
	LeftMouse = VK_LBUTTON,
	RightMouse = VK_RBUTTON,

	Up = VK_UP,
	Down = VK_DOWN,
	Left = VK_LEFT,
	Right = VK_RIGHT,
	SpaceBar = VK_SPACE,

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',

	Q = 'Q',
	E = 'E'
};

enum class KeyState {
	None,
	Press,
	Down,
	Up,
	End
};

// enum과 enum class의 차이?
// 요약하면, enum은 간단하고 enum class는 깐깐하다. 하지만 깐깐한 덕분에 오류 발생률 ↓ (안전)
enum {
	KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX) +1,		// = 256
	KEY_STATE_COUNT = static_cast<int32>(KeyState::End)		// = 4
};

class InputManager
{
	// InputManager가 싱클톤으로 동작하게 된다.
	DECLARE_SINGLE(InputManager);

public:
	void Init(HWND hwnd);
	void Update();

private:
	KeyState GetState(KeyType key) {
		return _states[static_cast<uint8>(key)];
	}

public:
	// 키가 눌려있는 상태 (입력 중)
	bool GetButton(KeyType key) { return GetState(key) == KeyState::Press; }

	// 키가 현재 입력 중이면서 이전 프레임에는 입력되지 않았던 상태
	bool GetButtonDown(KeyType key) { return GetState(key) == KeyState::Down; }

	// 이 키가 현재 입력되지 않은 상태이면서 이전 프레임에는 입력되었던 상태
	bool GetButtonUp(KeyType key) { return GetState(key) == KeyState::Up; }

	POINT GetMousePos() { return _mousePos; }

private:
	HWND _hwnd = {};
	vector<KeyState> _states;

	POINT _mousePos;
};

