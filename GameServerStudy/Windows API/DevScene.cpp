#include "pch.h"
#include "DevScene.h"
#include "Utils.h"
#include "InputManager.h"
#include "TimeManager.h"

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
	// �̰Ͱ� ���� ������ �̿��Ͽ� (�Ÿ� = �ð� * �ӵ�) ���� ȯ���� �ٸ����� ���� �ӵ��� ����ǵ��� �Ѵ�.
	// ��ǻ�Ͱ� �ƹ��� ���� ���� �ӵ� ���� X
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	
	// ������ �ִ� ���� ��� True���� ��. (��� ������ �ִ� ���)
	if (GET_SINGLE(InputManager)->GetButton(KeyType::A)) {
		//_playerPos.x -= 1;
		_playerPos.x -= _speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::D)) {
		//_playerPos.x += 1;
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
	Utils::DrawCircle(hdc, _playerPos, 50);
}
