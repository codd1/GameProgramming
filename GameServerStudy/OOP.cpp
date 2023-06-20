#include <iostream>
using namespace std;

// ��ü���� (Object Oriented Programming)
// ������ + ����

// �÷��̾�, ����, GameRoom, Lobby(���) � ��ü�� �ȴ�.
class Knight {
public:
	// �⺻ ������ (Constructor)
	Knight() {
		m_hp = 0;
		m_attack = 0;
		m_defence = 0;
		cout << "Knight()" << endl;
	}
	// ��Ÿ ������
	Knight(int hp, int attack, int defence) {
		m_hp = hp;
		m_attack = attack;
		m_defence = defence;
		cout << "Knight()" << endl;
	}
	// ���� ������
	Knight(const Knight& other) {
		m_hp = other.m_hp;
		m_attack = other.m_attack;
		m_defence = other.m_defence;
		cout << "Knight(const Knight& other)" << endl;
	}
	// �Ҹ��� (Destructor) - �� 1���� ����
	~Knight() {
		cout << "~Knight()" << endl;
	}

public:
	// ��� �Լ�
	void Attack() {
		cout << "Attack" << endl;
	}
	void Die() {
		cout << "Die" << endl;
	}
	void HealMe(int value) {
		m_hp += value;
	}

public:
	// ��� ����
	int m_hp;
	int m_attack;
	int m_defence;
};

int main() {
	Knight k1(100,10,1);
	Knight k2(k1);	// k1�� �����͸� ����

	cout << k1.m_hp << endl;
}