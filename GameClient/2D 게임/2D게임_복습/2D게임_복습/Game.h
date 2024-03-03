#pragma once

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

