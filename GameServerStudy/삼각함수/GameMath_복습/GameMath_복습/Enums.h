#pragma once
enum class SceneType {
	None,
	DevScene,
	GameScene,
	EditScene,
	MenuScene,
	FortressScene
};

// 58. ��Ʈ���� ����
// GameScene, Monster, Missile ����
// UIManager.h, .cpp + UI, Menu, CanonTank, MissileTank.txt �߰�

// PlayerType enum class ����
enum class PlayerType {
	CanonTank,
	MissileTank
};

// 67. Dir �߰� (Object.h)
enum class Dir {
	Left,
	Right
};