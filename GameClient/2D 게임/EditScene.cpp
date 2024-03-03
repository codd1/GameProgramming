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

void EditScene::Update()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse)) {
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();

		if (_isFirst) {
			// 처음이어서 기준이 되는 Pos를 설정해줘야 함.
			_lastPos = mousePos;
			_isFirst = false;
		}
		else {
			_lines.push_back(make_pair(_lastPos, mousePos));
			_lastPos = mousePos;
		}
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::RightMouse)) {
		_isFirst = true;
	}

	// Save
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::S)) {
		wofstream file;
		file.open(L"Unit.txt");

		// 선으로 그린 그림의 중앙을 구하기 위함
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


		// 라인 갯수
		file << static_cast<int32>(_lines.size()) << endl;

		for (auto& line : _lines) {
			// 0,0 위치에서 그림이 만들어짐 (0,0이 그림의 중앙)
			POINT from = line.first;
			from.x -= midX;
			from.y -= midY;

			POINT to = line.second;
			to.x -= midX;
			to.y -= midY;

			// 형식을 만들어서 파일 입력
			wstring str = std::format(L"({0},{1})->({2},{3})", from.x, from.y, to.x, to.y);
			file << str << endl;
		}

		file.close();
	}

	// Load
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::D)) {
		// Save 파일 가져오기
		wifstream file;
		file.open(L"Unit.txt");

		// 라인 갯수
		int32 count;
		file >> count;
		
		_lines.clear();

		// 그림 위치 설정
		int32 midX = 400;
		int32 midY = 300;

		// Save 파일 복원
		for (int32 i = 0; i < count; i++) {
			POINT pt1;
			POINT pt2;

			wstring str;
			file >> str;
			::swscanf_s(str.c_str(), L"(%d,%d)->(%d,%d)", &pt1.x, &pt1.y, &pt2.x, &pt2.y);

			// 그림 위치를 화면 가운데로 잡아줌 (기존엔 0,0)
			pt1.x += midX;
			pt1.y += midY;
			pt2.x += midX;
			pt2.y += midY;

			_lines.push_back(make_pair(pt1, pt2));
			_isFirst = true;
		}
	}

}

void EditScene::Render(HDC hdc)
{
	for (auto& line : _lines) {
		POINT pt1 = line.first;
		POINT pt2 = line.second;

		Pos pos1;
		pos1.x = (float)pt1.x;
		pos1.y = (float)pt1.y;

		Pos pos2;
		pos2.x = (float)pt2.x;
		pos2.y = (float)pt2.y;

		Utils::DrawLine(hdc, pos1, pos2);
	}
}
