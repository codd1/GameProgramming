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
	// deltaTime은 이전 프레임에서 현재 시간까지 경과된 시간이다.
	// 이것은 물리 공식을 이용하여 (거리 = 시간*속도) 실행 환경이 다르더라도 같은 속도로 실행되게 한다.
	// 컴퓨터가 아무리 빨라도 실행 속도에 차이 X
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 누르고 있는동안 계속 True여야 함. (A, D, W, S 중 하나를 계속 누르고 있는 경우)
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
	// Game::Init(HWND hwnd) 내에서 ChangeScene(SceneType::DevScene);로 바꿔야 확인 가능
	Utils::DrawCircle(hdc, _playerPos, 50);
}
