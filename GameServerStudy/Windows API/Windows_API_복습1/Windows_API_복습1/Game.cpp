#include "pch.h"
#include "Game.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_hdc = ::GetDC(hwnd);

	// â Ŭ���̾�Ʈ ������ ��ǥ�� �˻��Ѵ�. Ŭ���̾�Ʈ ��ǥ�� ���� ���� ������ �Ʒ� �𼭸��� ����. ���� �� �𼭸��� ��ǥ�� (0,0)
	::GetClientRect(hwnd, &_rect);

	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(InputManager)->Init(hwnd);
	GET_SINGLE(SceneManager)->Init();
	GET_SINGLE(ResourceManager)->Init();

	GET_SINGLE(SceneManager)->ChangeScene(SceneType::EditScene);
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
		::TextOut(_hdc, 20, 10, str.c_str(), str.size());	// ȭ�鿡 �ؽ�Ʈ ���
	}
	{	// Fps, DT(��ŸŸ��) ���
		wstring str = format(L"FPS({0}), DT({1} ms)", fps, static_cast<int32>(deltaTime * 1000));
		::TextOut(_hdc, 650, 10, str.c_str(), str.size());
	}

	GET_SINGLE(SceneManager)->Render(_hdc);

	// TODO: ������۸�
}
