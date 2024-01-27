#pragma once
enum class SceneType {
	None,
	DevScene,
	GameScene,
	EditScene,
	MenuScene,
	FortressScene
};

// 58. 포트리스 모작
// GameScene, Monster, Missile 제거
// UIManager.h, .cpp + UI, Menu, CanonTank, MissileTank.txt 추가

// PlayerType enum class 선언
enum class PlayerType {
	CanonTank,
	MissileTank
};

// 67. Dir 추가 (Object.h)
enum class Dir {
	Left,
	Right
};