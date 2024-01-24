#include "pch.h"
#include "EditScene.h"
#include "InputManager.h"
#include <fstream>

EditScene::EditScene()
{
}

EditScene::~EditScene()
{
}

void EditScene::Init()
{
}

// 20. EditScene::Update() ����
void EditScene::Update()
{
	// ��Ŭ��
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse)) {
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();

		if (_isFirst) {		// ó���� ���
			// ������ �Ǵ� Pos ����
			_lastPos = mousePos;
			_isFirst = false;
		}
		else {				// ó���� �ƴ� ���
			_lines.push_back(make_pair(_lastPos, mousePos));	// ������ ���� ��ǥ�� ���� ���� ��ǥ�� ��(pair)���� ��ȯ�ؼ� _lines ���Ϳ� ����
			_lastPos = mousePos;	// ���� �׷����Ƿ� ���� ��ǥ�� ���� ��ǥ�� �ȴ�.
		}
	}

	// ��Ŭ��
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::RightMouse)) {
		_isFirst = true;		// ��Ŭ���� ��� ���� ó�� �׸��°ɷ� ��
	}

	
	// SŰ -> Save
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::S)) {
		wofstream file;		// #include <fstream>
		file.open(L"Unit.txt");

		// ������ �׸� �׸��� �߾��� ���ϱ� ����
		int32 minX = INT32_MAX;
		int32 maxX = INT32_MIN;
		int32 minY = INT32_MAX;
		int32 maxY = INT32_MIN;

		for (auto& line : _lines) {
			POINT from = line.first;
			POINT to = line.second;

			minX = min(min(minX, from.x), to.x);
			maxX = max(max(maxX, from.x), to.x);
			minY = min(min(minY, from.y), to.y);
			maxY = max(max(maxY, from.y), to.y);
		}

		int32 midX = (maxX + minX) / 2;
		int32 midY = (maxY + minY) / 2;

		// ���Ͽ� ���� ���� �Է�
		file << static_cast<int32>(_lines.size()) << endl;

		for (auto& line : _lines) {
			// 0,0 ��ġ���� �׸��� ������� (0,0�� �׸��� �߾�)
			POINT from = line.first;
			from.x -= midX;
			from.y -= midY;

			POINT to = line.second;
			to.x -= midX;
			to.y -= midY;

			// ������ ���� ���Ͽ� �Է�
			wstring str = std::format(L"({0},{1})->({2},{3})", from.x, from.y, to.x, to.y);		// #include <format>
			file << str << endl;
		}

		file.close();
	}

	// DŰ -> Load
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::D)) {
		// Save ���� ��������
		wifstream file;
		file.open(L"Unit.txt");

		// ���� ����
		int32 count;
		file >> count;

		_lines.clear();		// ������ ��� ��� ����

		// �׸� ��ġ ����
		int32 midX = 400;
		int32 midY = 300;

		// Save ���� ���� - Unit.txt���� ���� ���ڿ��� POINT ����ü�� ������ _lines ���Ϳ� �߰�
		for (int32 i = 0; i < count; i++) {
			POINT pt1;
			POINT pt2;

			wstring str;
			file >> str;
			::swscanf_s(str.c_str(), L"(%d,%d)->(%d,%d)", &pt1.x, &pt1.y, &pt2.x, &pt2.y);	// POINT�� �Ľ�

			// �׸� ��ġ�� ȭ�� ����� ����� (������ 0,0)
			pt1.x += midX;
			pt1.y += midY;
			pt2.x += midX;
			pt2.y += midY;

			_lines.push_back(make_pair(pt1, pt2));
			_isFirst = true;
		}

		file.close();
	}
}

// 24. EditScene::Update() ����
void EditScene::Render(HDC hdc)
{
	for (auto& line : _lines) {
		POINT pt1 = line.first;
		POINT pt2 = line.second;

		Pos pos1;	// ������ ù ��° ��ǥ (from)
		pos1.x = (float)pt1.x;		// C���� ĳ����(�� �����ϱ������� ������ ��)
		pos1.y = (float)pt1.y;		// pos1.y = static_cast<float>pt1.y;

		Pos pos2;	// ������ �� ��° ��ǥ (to)
		pos2.x = (float)pt2.x;
		pos2.y = (float)pt2.y;

		Utils::DrawLine(hdc, pos1, pos2);
	}

	// Game::Init(HWND hwnd) ������ ChangeScene(SceneType::EditScene);�� �ٲ�� Ȯ�� ����
}
