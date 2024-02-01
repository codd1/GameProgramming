#include "pch.h"
#include "DevScene.h"
#include "TimeManager.h"
#include "InputManager.h"

DevScene::DevScene()
{
}

DevScene::~DevScene()
{
}

void DevScene::Init()
{
}

void DevScene::Update()
{
	// deltaTime�� ���� �����ӿ��� ���� �ð����� ����� �ð��̴�.
	// �̰��� ���� ������ �̿��Ͽ� (�Ÿ� = �ð�*�ӵ�) ���� ȯ���� �ٸ����� ���� �ӵ��� ����ǰ� �Ѵ�.
	// ��ǻ�Ͱ� �ƹ��� ���� ���� �ӵ��� ���� X
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// ������ �ִµ��� ��� True���� ��. (A, D, W, S �� �ϳ��� ��� ������ �ִ� ���)
	if (GET_SINGLE(InputManager)->GetButton(KeyType::A)) {
		_playerPos.x -= _speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::D)) {
		_playerPos.x += _speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W)) {
		_playerPos.y -= _speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S)) {
		_playerPos.y += _speed * deltaTime;
	}

}

void DevScene::Render(HDC hdc)
{
	// Game::Init(HWND hwnd) ������ ChangeScene(SceneType::DevScene);�� �ٲ�� Ȯ�� ����
	Utils::DrawCircle(hdc, _playerPos, 50);
}
