#include <iostream>
using namespace std;

class Actor {

};

class Pawn : public Actor {

};

class Character :public Pawn {

};

class StaticMeshComponent {

};

class BP_Player : public Actor {
public:
	// �⺻������ �𸮾󿡼� ����� �Լ����� ��� �����Լ���� �����ϸ� �ȴ�.
	virtual void Test() {

	}

public:
	int hp;
	StaticMeshComponent StatMesh;
};

class IFlyable {
public:
	virtual void Fly() = 0;
};

class BP_Knight :public BP_Player, public IFlyable {
public:
	virtual void Fly() override {

	}

	virtual void Test() override {
		BP_Player::Test();

		// ...
	}
};

int main() {
	BP_Knight k;

	BP_Player* p = &k;
}