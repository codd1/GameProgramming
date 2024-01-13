#include "pch.h"
#include "DevScene.h"
#include "Utils.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"

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

	Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Start");
	GET_SINGLE(ResourceManager)->CreateSprite(L"Start_On", texture, 150, 0, 150, 150);
}

void DevScene::Update()
{
	// deltaTime은 이전 프레임에서 현재 시간까지 경과된 시간이다.
	// 이것과 물리 공식을 이용하여 (거리 = 시간 * 속도) 실행 환경이 다르더라도 같은 속도로 실행되도록 한다.
	// 컴퓨터가 아무리 빨라도 실행 속도 차이 X
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	

}

void DevScene::Render(HDC hdc)
{
	// 비트맵 그림 복사
	//Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Stage01");
	Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Start_On");
	::BitBlt(hdc, 0, 0, GWinSizeX, GWinSizeY, sprite->GetDC(), sprite->GetPos().x, sprite->GetPos().y, SRCCOPY);
}
