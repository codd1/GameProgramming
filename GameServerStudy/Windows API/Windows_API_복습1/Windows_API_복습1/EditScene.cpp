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

// 20. EditScene::Update() 구현
void EditScene::Update()
{
	// 좌클릭
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse)) {
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();

		if (_isFirst) {		// 처음일 경우
			// 기준이 되는 Pos 설정
			_lastPos = mousePos;
			_isFirst = false;
		}
		else {				// 처음이 아닌 경우
			_lines.push_back(make_pair(_lastPos, mousePos));	// 이전에 찍은 좌표와 지금 찍은 좌표를 쌍(pair)으로 반환해서 _lines 벡터에 저장
			_lastPos = mousePos;	// 선을 그렸으므로 현재 좌표가 이전 좌표가 된다.
		}
	}

	// 우클릭
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::RightMouse)) {
		_isFirst = true;		// 우클릭할 경우 선을 처음 그리는걸로 됨
	}

	
	// S키 -> Save
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::S)) {
		wofstream file;		// #include <fstream>
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

		// 파일에 라인 갯수 입력
		file << static_cast<int32>(_lines.size()) << endl;

		for (auto& line : _lines) {
			// 0,0 위치에서 그림이 만들어짐 (0,0이 그림의 중앙)
			POINT from = line.first;
			from.x -= midX;
			from.y -= midY;

			POINT to = line.second;
			to.x -= midX;
			to.y -= midY;

			// 형식을 만들어서 파일에 입력
			wstring str = std::format(L"({0},{1})->({2},{3})", from.x, from.y, to.x, to.y);		// #include <format>
			file << str << endl;
		}

		file.close();
	}

	// D키 -> Load
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::D)) {
		// Save 파일 가져오기
		wifstream file;
		file.open(L"Unit.txt");

		// 라인 갯수
		int32 count;
		file >> count;

		_lines.clear();		// 벡터의 모든 요소 제거

		// 그림 위치 설정
		int32 midX = 400;
		int32 midY = 300;

		// Save 파일 복원 - Unit.txt에서 읽은 문자열로 POINT 구조체를 추출해 _lines 벡터에 추가
		for (int32 i = 0; i < count; i++) {
			POINT pt1;
			POINT pt2;

			wstring str;
			file >> str;
			::swscanf_s(str.c_str(), L"(%d,%d)->(%d,%d)", &pt1.x, &pt1.y, &pt2.x, &pt2.y);	// POINT로 파싱

			// 그림 위치를 화면 가운데로 잡아줌 (기존엔 0,0)
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

// 24. EditScene::Update() 구현
void EditScene::Render(HDC hdc)
{
	for (auto& line : _lines) {
		POINT pt1 = line.first;
		POINT pt2 = line.second;

		Pos pos1;	// 선분의 첫 번째 좌표 (from)
		pos1.x = (float)pt1.x;		// C언어식 캐스팅(도 가능하긴하지만 지양할 것)
		pos1.y = (float)pt1.y;		// pos1.y = static_cast<float>pt1.y;

		Pos pos2;	// 선분의 두 번째 좌표 (to)
		pos2.x = (float)pt2.x;
		pos2.y = (float)pt2.y;

		Utils::DrawLine(hdc, pos1, pos2);
	}

	// Game::Init(HWND hwnd) 내에서 ChangeScene(SceneType::EditScene);로 바꿔야 확인 가능
}
