#include "pch.h"
#include "InputManager.h"

void InputManager::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_states.resize(KEY_TYPE_COUNT, KeyState::None);		// ������ ũ�� ����
}

// 17. InputManager::Update() ����
// Ű���忡 ���� ������ ������Ʈ�ϰ� �� Ű�� ���¸� _states ���Ϳ� ���
void InputManager::Update()
{
	BYTE asciiKeys[KEY_TYPE_COUNT] = {};	// Ű������ ��� Ű�� ��Ÿ���� �迭
	if (::GetKeyboardState(asciiKeys) == false) {
		return;
	}

	// Ű������ ��� Ű�� �� ���� ����
	for (uint32 key = 0; key < KEY_TYPE_COUNT; key++) {
		if (asciiKeys[key] & 0x80) {	// 0x80 = �ش� ��Ʈ�� �����Ǿ� �ִ��� Ȯ���ϴ� ��Ʈ ����ũ. (�����Ǿ��ִ� = �ش� Ű�� �������ִ�)
			KeyState& state = _states[key];

			// Ű�� �������־��ų� �Ǵ� Ű�� ������ ������ �ִ� ���
			if (state == KeyState::Press || state == KeyState::Down) {
				state = KeyState::Press;
			}
			else {	// ���� Ű�� �������� ���� ���
				state = KeyState::Down;
			}
		}
		else {		// �ش� Ű�� ������ ���� ���� ���
			KeyState& state = _states[key];

			// ������ �������־��� ���
			if (state == KeyState::Press || state == KeyState::Down) {
				state = KeyState::Up;
			}
			else {	// ������ ������ ���� ���� ���
				state = KeyState::None;
			}
		}
	}

	// Mouse
	::GetCursorPos(&_mousePos);		// Ŀ���� ��ǥ
	::ScreenToClient(_hwnd, &_mousePos);	// â �������� �� ���콺 Pos�� �ٲ���
}
