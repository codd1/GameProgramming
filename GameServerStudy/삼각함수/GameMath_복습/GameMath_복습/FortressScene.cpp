#include "pch.h"
#include "FortressScene.h"
#include "UIManager.h"
#include "Player.h"
#include "ObjectManager.h"
#include "TimeManager.h"

FortressScene::FortressScene()
{
}

FortressScene::~FortressScene()
{
}

// 69. FortressScene::Init() 구현
void FortressScene::Init()
{
	GET_SINGLE(UIManager)->Init();

	{
		Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
		player->SetPlayerId(0);
		player->SetPlayerType(PlayerType::MissileTank);
		player->SetPlayerTurn(true);

		GET_SINGLE(ObjectManager)->Add(player);

		player->SetPos(Vector{ 100,400 });
	}

	{
		Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
		player->SetPlayerId(1);
		player->SetPlayerType(PlayerType::CanonTank);
		player->SetPlayerTurn(false);

		GET_SINGLE(ObjectManager)->Add(player);

		player->SetPos(Vector{ 700,400 });
	}

	// 78. 
	ChangePlayerTurn();
}

// 70. FortressScene::Update() 구현
void FortressScene::Update()
{
	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();

	for (Object* object : objects) {
		object->Update();
	}

	// 79. 턴마다 시간 설정
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= 1.f) {		// 1초마다 확인
		_sumTime = 0.f;

		int32 remainTime = GET_SINGLE(UIManager)->GetRemainTime();
		remainTime = max(0, remainTime - 1);	// 음수 방지

		GET_SINGLE(UIManager)->SetRemainTime(remainTime);

		// 남은 시간이 0이 되면 턴 바꿈
		if (remainTime == 0) {
			ChangePlayerTurn();
		}
	}
}

// 73. FortressScene::Render(HDC hdc) 구현
void FortressScene::Render(HDC hdc)
{
	// 정보 UI 출력 안되는 문제 해결
	// 오타 수정: Init() -> Render(hdc)
	GET_SINGLE(UIManager)->Render(hdc);

	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();

	for (Object* object : objects) {
		object->Render(hdc);
	}
}

void FortressScene::ChangePlayerTurn()
{
	_playerTurn = (_playerTurn + 1) % 2;	// 0이었으면 1이 되고, 1이었으면 0이 된다.

	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects) {
		if (object->GetObjectType() != ObjectType::Player) {
			continue;		// 오타수정: return -> continue;
		}

		Player* player = static_cast<Player*>(object);
		if (player->GetPlayerId() == _playerTurn) {
			player->SetPlayerTurn(true);
		}
		else {
			player->SetPlayerTurn(false);
		}
	}

	// Player turn이 바뀌었으므로 나머지 요소들도 초기화 (아래 내용들은 몰라도될듯?)
	GET_SINGLE(UIManager)->SetRemainTime(10);
	GET_SINGLE(UIManager)->SetStaminaPercent(100.f);
	GET_SINGLE(UIManager)->SetPowerPercent(0.f);
	GET_SINGLE(UIManager)->SetWindPercent(static_cast<float>(-100 + rand() % 200));
}
