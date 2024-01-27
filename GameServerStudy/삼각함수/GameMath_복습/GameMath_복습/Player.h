#pragma once
#include "Object.h"

// 13~14. Player, Monster 클래스 생성
class Player : public Object
{
public:
	Player();
	virtual ~Player() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

// 66. 필요한 멤버변수, 메소드 선언
private:
	int32 _playerId = 0;
	PlayerType _playerType = PlayerType::CanonTank;
	bool _playerTurn = false;
	float _fireAngle = 0.f;

public:
	void SetPlayerId(int32 playerId) { _playerId = playerId; }
	void SetPlayerType(PlayerType playerType) { _playerType = playerType; }
	void SetPlayerTurn(bool playerTurn) { _playerTurn = playerTurn; }

	int32 GetPlayerId() { return _playerId; }
	PlayerType GetPlayerType() { return _playerType; }
	bool GetPlayerTurn() { return _playerTurn; }

	wstring GetMeshKey();

	void UpdateFireAngle();
};

