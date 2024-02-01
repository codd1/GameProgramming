#pragma once

enum class KeyType {
	// VK = Virtual Key Code
	// �� ���� �ַ� Windows�� �޽��� ó�� �Լ����� Ű �̺�Ʈ�� �ٷ� �� ���ȴ�.
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

// enum�� enum class�� ����?
// ����ϸ�, enum�� �����ϰ� enum class�� ����ϴ�. ������ ����� ���п� ���� �߻��� �� (����)
enum {
	KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX) +1,		// = 256
	KEY_STATE_COUNT = static_cast<int32>(KeyState::End)		// = 4
};

class InputManager
{
	// InputManager�� ��Ŭ������ �����ϰ� �ȴ�.
	DECLARE_SINGLE(InputManager);

public:
	void Init(HWND hwnd);
	void Update();

private:
	KeyState GetState(KeyType key) {
		return _states[static_cast<uint8>(key)];
	}

public:
	// Ű�� �����ִ� ���� (�Է� ��)
	bool GetButton(KeyType key) { return GetState(key) == KeyState::Press; }

	// Ű�� ���� �Է� ���̸鼭 ���� �����ӿ��� �Էµ��� �ʾҴ� ����
	bool GetButtonDown(KeyType key) { return GetState(key) == KeyState::Down; }

	// �� Ű�� ���� �Էµ��� ���� �����̸鼭 ���� �����ӿ��� �ԷµǾ��� ����
	bool GetButtonUp(KeyType key) { return GetState(key) == KeyState::Up; }

	POINT GetMousePos() { return _mousePos; }

private:
	HWND _hwnd = {};
	vector<KeyState> _states;

	POINT _mousePos;
};

