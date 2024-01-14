#include "pch.h"
#include "DevScene.h"
#include "Utils.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Actor.h"
#include "SpriteActor.h"
#include "Player.h"

DevScene::DevScene()
{
}

DevScene::~DevScene()
{
}

void DevScene::Init()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"Stage01", L"Sprite\\Map\\Stage01.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Sword", L"Sprite\\Item\\Sword.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Potion", L"Sprite\\UI\\Mp.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerDown", L"Sprite\\Player\\PlayerDown.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerUp", L"Sprite\\Player\\PlayerUp.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerLeft", L"Sprite\\Player\\PlayerLeft.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerRight", L"Sprite\\Player\\PlayerRight.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Start", L"Sprite\\UI\\Start.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Edit", L"Sprite\\UI\\Edit.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Exit", L"Sprite\\UI\\Exit.bmp");

	GET_SINGLE(ResourceManager)->CreateSprite(L"Stage01", GET_SINGLE(ResourceManager)->GetTexture(L"Stage01"));
	GET_SINGLE(ResourceManager)->CreateSprite(L"TileO", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 0, 0, 48, 48);
	GET_SINGLE(ResourceManager)->CreateSprite(L"TileX", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 48, 0, 48, 48);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Start_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Start_On", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 150, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Edit_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Edit"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Edit_On", GET_SINGLE(ResourceManager)->GetTexture(L"Edit"), 150, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Exit_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Exit"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Exit_On", GET_SINGLE(ResourceManager)->GetTexture(L"Exit"), 150, 0, 150, 150);

	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Stage01");

		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		background->SetPos(Vec2(0, 0));
		_actors.push_back(background);
	}

	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Stage01");

		Player* player = new Player();
		player->SetSprite(sprite);
		player->SetPos(Vec2(0, 0));
		_actors.push_back(player);
	}

	// 모든 Actor들을 순회하면서 실행
	for (Actor* actor : _actors) {
		actor->BeginPlay();
	}
}

void DevScene::Update()
{
	// deltaTime은 이전 프레임에서 현재 시간까지 경과된 시간이다.
	// 이것과 물리 공식을 이용하여 (거리 = 시간 * 속도) 실행 환경이 다르더라도 같은 속도로 실행되도록 한다.
	// 컴퓨터가 아무리 빨라도 실행 속도 차이 X
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	
	for (Actor* actor : _actors) {
		actor->Tick();
	}
}

void DevScene::Render(HDC hdc)
{
	// 비트맵 그림 복사
	/*Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Start_On");
	::BitBlt(hdc, 0, 0, GWinSizeX, GWinSizeY, sprite->GetDC(), sprite->GetPos().x, sprite->GetPos().y, SRCCOPY);*/

	// 이제 SpriteActor를 통해 Render를 할 수 있다.
	for (Actor* actor : _actors) {
		actor->Render(hdc);
	}
}
