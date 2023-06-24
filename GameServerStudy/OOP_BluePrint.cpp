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
	// 기본적으로 언리얼에서 만드는 함수들은 모두 가상함수라고 생각하면 된다.
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