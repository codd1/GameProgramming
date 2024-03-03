#include <iostream>
using namespace std;

// ��ü���� (Object Oriented Programming)
// ������ + ����

/*
	OOP 3�� ���
	- ��Ӽ� (Inheritance)
	- ���м� (Data hiding / encapsulation)
	- ������ (Polymorphism)
*/

// �����ε�(overloading) = �Լ� �̸��� ����
// �������̵�(overriding) = �θ� Ŭ������ �Լ��� �ڽ� Ŭ�������� ������

// �����ε�
void Test() { }
void Test(int a) { }
void Test(float a) { }

// �߻� Ŭ����
class Player {
public:
	//virtual void Move() { cout << "Player Move()" << endl; }
	virtual void Move() = 0;	// ���� ���� �Լ�: ���� �Լ��ε� �����ΰ� ����, ������ ����� �޴� Ŭ������ �ؾ��Ѵ�. -> �߻� Ŭ������ �з�

	// ���� Ŭ���� �Ҹ��ڿ� virtual�� �ٿ�����Ѵ�. ���� Ŭ������ �Ҹ��ڰ� ȣ����� ���� �� �ֱ� �����̴�.
	virtual ~Player() { }
public:
	int m_hp = 100;
};

class Knight :public Player {
public:
	virtual void Move() override { cout << "Knight Move()" << endl; }	// = ���� �����Լ��ε�, �θ� Ŭ�������� ��� ���� ���� �Լ��� override�Ͽ� �������ϰڴ�.
public:
	int m_stamina = 200;
};

void MovePlayer(Player* player) {
	player->Move();
}

int main() {
	//Player p1;	// �߻� Ŭ������ ��ü ��� �Ұ�

	Knight k1;
	MovePlayer(&k1);
}