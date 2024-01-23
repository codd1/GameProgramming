#include "pch.h"
#include "Game.h"

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

	// 창 클라이언트 영역의 좌표를 검색한다. 클라이언트 좌표는 왼쪽 위와 오른쪽 아래 모서리를 지정. 왼쪽 위 모서리의 좌표는 (0,0)
	::GetClientRect(hwnd, &_rect);

}

void Game::Update()
{
}

void Game::Render()
{
}
