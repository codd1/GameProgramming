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

// 69. FortressScene::Init() ����
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

// 70. FortressScene::Update() ����
void FortressScene::Update()
{
	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();

	for (Object* object : objects) {
		object->Update();
	}

	// 79. �ϸ��� �ð� ����
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= 1.f) {		// 1�ʸ��� Ȯ��
		_sumTime = 0.f;

		int32 remainTime = GET_SINGLE(UIManager)->GetRemainTime();
		remainTime = max(0, remainTime - 1);	// ���� ����

		GET_SINGLE(UIManager)->SetRemainTime(remainTime);

		// ���� �ð��� 0�� �Ǹ� �� �ٲ�
		if (remainTime == 0) {
			ChangePlayerTurn();
		}
	}
}

// 73. FortressScene::Render(HDC hdc) ����
void FortressScene::Render(HDC hdc)
{
	// ���� UI ��� �ȵǴ� ���� �ذ�
	// ��Ÿ ����: Init() -> Render(hdc)
	GET_SINGLE(UIManager)->Render(hdc);

	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();

	for (Object* object : objects) {
		object->Render(hdc);
	}
}

void FortressScene::ChangePlayerTurn()
{
	_playerTurn = (_playerTurn + 1) % 2;	// 0�̾����� 1�� �ǰ�, 1�̾����� 0�� �ȴ�.

	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects) {
		if (object->GetObjectType() != ObjectType::Player) {
			continue;		// ��Ÿ����: return -> continue;
		}

		Player* player = static_cast<Player*>(object);
		if (player->GetPlayerId() == _playerTurn) {
			player->SetPlayerTurn(true);
		}
		else {
			player->SetPlayerTurn(false);
		}
	}

	// Player turn�� �ٲ�����Ƿ� ������ ��ҵ鵵 �ʱ�ȭ (�Ʒ� ������� ���󵵵ɵ�?)
	GET_SINGLE(UIManager)->SetRemainTime(10);
	GET_SINGLE(UIManager)->SetStaminaPercent(100.f);
	GET_SINGLE(UIManager)->SetPowerPercent(0.f);
	GET_SINGLE(UIManager)->SetWindPercent(static_cast<float>(-100 + rand() % 200));
}
