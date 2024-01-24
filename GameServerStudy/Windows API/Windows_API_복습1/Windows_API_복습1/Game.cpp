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
	// 43. �Ҹ��ڿ��� Clear() ȣ��
	GET_SINGLE(SceneManager)->Clear();
	GET_SINGLE(ResourceManager)->Clear();

	::_CrtDumpMemoryLeaks();
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_hdc = ::GetDC(hwnd);

	// â Ŭ���̾�Ʈ ������ ��ǥ�� �˻��Ѵ�. Ŭ���̾�Ʈ ��ǥ�� ���� ���� ������ �Ʒ� �𼭸��� ����. ���� �� �𼭸��� ��ǥ�� (0,0)
	::GetClientRect(hwnd, &_rect);

	// 35. Player �̵� �ÿ� �ܻ��� �����ִ� ���� -> ������۸����� �ذ� (Init, Render)
	_hdcBack = ::CreateCompatibleDC(_hdc);		// hdc�� ȣȯ�Ǵ� DC�� ����
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

	{	// ���콺 ��ǥ�� �����ͼ� ȭ�鿡 (format�� ����) ���콺 ��ǥ ���
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		wstring str = format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		::TextOut(_hdcBack, 20, 10, str.c_str(), str.size());	// ȭ�鿡 �ؽ�Ʈ ���
	}
	{	// Fps, DT(��ŸŸ��) ���
		wstring str = format(L"FPS({0}), DT({1} ms)", fps, static_cast<int32>(deltaTime * 1000));
		::TextOut(_hdcBack, 650, 10, str.c_str(), str.size());
	}

	GET_SINGLE(SceneManager)->Render(_hdcBack);

	// 35. Player �̵� �ÿ� �ܻ��� �����ִ� ���� -> ������۸����� �ذ� (Init, Render)
	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY);
	::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}
