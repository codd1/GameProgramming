#include "pch.h"
#include "Game.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"

Game::Game()
{
	int* p = new int();
}

Game::~Game()
{
	GET_SINGLE(SceneManager)->Clear();
	GET_SINGLE(ResourceManager)->Clear();

	// Detected memory leaks! << 메모리 누수가 있다면 이렇게 출력된다.
	// 사실 마지막에 불러야 의미가 있긴 하다.
	_CrtDumpMemoryLeaks();
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_hdc = ::GetDC(hwnd);

	::GetClientRect(hwnd, &_rect);

	// _hdc와 호환되는 우리만의 또 다른 도화지 생성 (더블 버퍼링을 위함)
	_hdcBack = ::CreateCompatibleDC(_hdc);		// _hdc와 호환되는 DC를 생성
	_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);	// _hdc와 호환되는 비트맵 생성
	HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _bmpBack);		// DC와 BMP를 연결
	::DeleteObject(prev);

	GET_SINGLE(TimeManager)->Init();		// = TimeManager::GetInstance()->Init();
	GET_SINGLE(InputManager)->Init(hwnd);
	GET_SINGLE(SceneManager)->Init();
	GET_SINGLE(ResourceManager)->Init();

	GET_SINGLE(SceneManager)->ChangeScene(SceneType::GameScene);
}

void Game::Update()
{
	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(SceneManager)->Update();
}

void Game::Render()
{
	uint32 fps = GET_SINGLE(TimeManager)->GetFps();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		::TextOut(_hdcBack, 20, 10, str.c_str(), str.size());
	}

	{
		// format을 이용해서 아래 형태의 문자열을 만든다. (인자 순서대로 들어감)
		wstring str = std::format(L"FPS({0}), DT({1} ms)", fps, static_cast<int32>(deltaTime * 1000));
		::TextOut(_hdcBack, 650, 10, str.c_str(), str.size());
	}

	GET_SINGLE(SceneManager)->Render(_hdcBack);


	// 더블 버퍼링
	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY);		// 비트 블릿: 고속 복사
	::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}
