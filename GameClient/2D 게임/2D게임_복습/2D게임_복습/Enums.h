#pragma once
enum class SceneType {
	None,
	DevScene,
	GameScene,
	EditScene,
	MenuScene,
	FortressScene
};

// GameScene, Monster, Missile 제거
// UIManager.h, .cpp + UI, Menu, CanonTank, MissileTank.txt 추가

// PlayerType enum class 선언
enum class PlayerType {
	CanonTank,
	MissileTank
};

enum class Dir {
	Left,
	Right
};