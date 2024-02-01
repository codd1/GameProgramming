#pragma once

// 3. Game 클래스 생성
class Game
{
public:
	Game();
	~Game();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();

private:
	HWND _hwnd = {};
	HDC _hdc = {};

	RECT _rect = {};

private:
	HDC _hdcBack = {};
	HBITMAP _bmpBack = {};
};

