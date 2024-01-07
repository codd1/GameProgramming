#include "pch.h"
#include "Game.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"

Game::Game()
{
	int* p = new int();
}

Game::~Game()
{
	GET_SINGLE(SceneManager)->Clear();

	// Detected memory leaks! << �޸� ������ �ִٸ� �̷��� ��µȴ�.
	// ��� �������� �ҷ��� �ǹ̰� �ֱ� �ϴ�.
	_CrtDumpMemoryLeaks();
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_hdc = ::GetDC(hwnd);

	::GetClientRect(hwnd, &_rect);

	// _hdc�� ȣȯ�Ǵ� �츮���� �� �ٸ� ��ȭ�� ���� (���� ���۸��� ����)
	_hdcBack = ::CreateCompatibleDC(_hdc);		// _hdc�� ȣȯ�Ǵ� DC�� ����
	_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);	// _hdc�� ȣȯ�Ǵ� ��Ʈ�� ����
	HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _bmpBack);		// DC�� BMP�� ����
	::DeleteObject(prev);

	GET_SINGLE(TimeManager)->Init();		// = TimeManager::GetInstance()->Init();
	GET_SINGLE(InputManager)->Init(hwnd);
	GET_SINGLE(SceneManager)->Init();

	GET_SINGLE(SceneManager)->ChangeScene(SceneType::DevScene);
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
		::TextOut(_hdc, 20, 10, str.c_str(), str.size());
	}

	{
		// format�� �̿��ؼ� �Ʒ� ������ ���ڿ��� �����. (���� ������� ��)
		wstring str = std::format(L"FPS({0}), DT({1} ms)", fps, static_cast<int32>(deltaTime * 1000));
		::TextOut(_hdc, 650, 10, str.c_str(), str.size());
	}

	GET_SINGLE(SceneManager)->Render(_hdc);
}
