#include <iostream>
using namespace std;

// static�� class �ۿ� �ִ� ��ó�� �����ص� �ɵ�.
class Marine {
public:
	// Ư�� ���� ��ü�� ����
	void TakeDamage(int damage) {
		hp -= damage;
	}

	// Ư�� ���� ��ü�� ����
	static void SetAttack(int value) {
		//hp = 40;		// Error!
		attack = value;		// static������ �ǵ帱 �� �ִ�.
	}

public:
	// Ư�� ���� ��ü�� ����
	int hp = 40;
	
	// Ư�� ���� ��ü�� ����
	static int attack;
};

int Marine::attack = 10;

int main() {
	Marine::SetAttack(20);
}