#pragma once
enum class SceneType {
	None,
	DevScene,
	GameScene,
	EditScene,
	MenuScene,
	FortressScene
};

// GameScene, Monster, Missile ����
// UIManager.h, .cpp + UI, Menu, CanonTank, MissileTank.txt �߰�

// PlayerType enum class ����
enum class PlayerType {
	CanonTank,
	MissileTank
};

enum class Dir {
	Left,
	Right
};