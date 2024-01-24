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
	// 43. 소멸자에서 Clear() 호출
	GET_SINGLE(SceneManager)->Clear();
	GET_SINGLE(ResourceManager)->Clear();

	::_CrtDumpMemoryLeaks();
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_hdc = ::GetDC(hwnd);

	// 창 클라이언트 영역의 좌표를 검색한다. 클라이언트 좌표는 왼쪽 위와 오른쪽 아래 모서리를 지정. 왼쪽 위 모서리의 좌표는 (0,0)
	::GetClientRect(hwnd, &_rect);

	// 35. Player 이동 시에 잔상이 남아있는 문제 -> 더블버퍼링으로 해결 (Init, Render)
	_hdcBack = ::CreateCompatibleDC(_hdc);		// hdc와 호환되는 DC를 생성
	_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);
	HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _bmpBack);
	::DeleteObject(prev);

	GET_SINGLE(TimeManager)->Init();
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

	{	// 마우스 좌표를 가져와서 화면에 (format에 맞춰) 마우스 좌표 출력
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		wstring str = format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		::TextOut(_hdcBack, 20, 10, str.c_str(), str.size());	// 화면에 텍스트 출력
	}
	{	// Fps, DT(델타타임) 출력
		wstring str = format(L"FPS({0}), DT({1} ms)", fps, static_cast<int32>(deltaTime * 1000));
		::TextOut(_hdcBack, 650, 10, str.c_str(), str.size());
	}

	GET_SINGLE(SceneManager)->Render(_hdcBack);

	// 35. Player 이동 시에 잔상이 남아있는 문제 -> 더블버퍼링으로 해결 (Init, Render)
	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY);
	::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}
