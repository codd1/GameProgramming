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

	// â Ŭ���̾�Ʈ ������ ��ǥ�� �˻��Ѵ�. Ŭ���̾�Ʈ ��ǥ�� ���� ���� ������ �Ʒ� �𼭸��� ����. ���� �� �𼭸��� ��ǥ�� (0,0)
	::GetClientRect(hwnd, &_rect);

}

void Game::Update()
{
}

void Game::Render()
{
}
