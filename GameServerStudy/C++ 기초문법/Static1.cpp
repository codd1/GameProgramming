#include <iostream>
using namespace std;

// static은 class 밖에 있는 것처럼 생각해도 될듯.
class Marine {
public:
	// 특정 마린 객체와 연관
	void TakeDamage(int damage) {
		hp -= damage;
	}

	// 특정 마린 객체와 무관
	static void SetAttack(int value) {
		//hp = 40;		// Error!
		attack = value;		// static끼리는 건드릴 수 있다.
	}

public:
	// 특정 마린 객체와 연관
	int hp = 40;
	
	// 특정 마린 객체와 무관
	static int attack;
};

int Marine::attack = 10;

int main() {
	Marine::SetAttack(20);
}