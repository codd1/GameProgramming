#include <iostream>
using namespace std;

class Player {
public:
	Player() {
		cout << "Player()" << endl;
	}

	~Player() {
		cout << "~Player()" << endl;
	}
};

// Has-A
class Inventory {
public:
	Inventory() {
		cout << "Inventory()" << endl;
	}
	Inventory(int a) {
		m_a = a;
		cout << "Inventory(int)" << endl;
	}
	~Inventory() {
		cout << "~Inventory()" << endl;
	}

public:
	int m_a =0;
};

class Knight :public Player {
public:
	Knight() :m_hp(0), m_inventory(100), m_hpRef(m_hp), m_hpConst(m_hp)		// �̰� �� ȿ�����̴�.
	/*
		��ó�� ����
		Player()
		m_inventory = Inventory()
	*/ {
		// ���⼭ �ʱ�ȭ�ϴ� ����� ���� ���δ�.
		//m_hp = 0;
		//m_inventory = Inventory(100);		// �̷��� �����ڰ� 2�� ȣ��� �� �ִ�. (���� �ٸ� �����ڱ�������) -> ��ȿ����

		//m_hpRef = m_hp;
		//m_hpConst = m_hp;		// �̷� �ֵ��� ��ó�� �������� �ʱ�ȭ������Ѵ�. (���⼭ �ʱ�ȭ�ϸ� ���� �߻�)

		cout << "Knight()" << endl;
	}

	~Knight() {
		cout << "~Knight()" << endl;
	}
public:
	int m_hp;
	int m_defence = 20;

	// �ʱ�ȭ �ʿ�
	int& m_hpRef;
	const int m_hpConst;

	Inventory m_inventory;
};

int main() {
	// C# vs C++
	// C# Knight k1 = new Knight();
	// C++ Knight* k1 = new Knight();	// �����Ҵ�

	Knight k1;	// ����Ǵ� ���� ������ ȣ��


	// �������� Ư���� �߰�ȣ �ȿ����� ��ȿ�ϱ� ������ �߰�ȣ�� ������ ��ü�� �Ҹ�ȴ�. (=�Ҹ��� ȣ��) -> ���� �Ҹ��Ű�� ������ ���� ����
	{
		Knight k2;
	}

	/*
		�Ʒ� ù ��° ���� ��ü ������ for�� �ȿ��� �ϴ� ���̰�,
		�Ʒ� �� ��° ���� ��ü ������ for�� �ۿ��� �� �� �� ���̴�.

		ù ��° ���� for������ �ݺ��� ������ �Ź� ��ü�� ���� �����ϱ� ������ ������, �Ҹ��ڰ� ��� ȣ��Ǳ� ������
		�� ���� ���� �̹��ϰ� �������̰� ���Եȴ�.
	*/

	// ù ��° ���
	for (int i = 0; i < 10; i++) {
		Knight k3;
		cout << "k3: " << i << endl;
	}

	// �� ��° ���
	Knight k4;
	for (int i = 0; i < 10; i++) {
		cout << "k4: " << i << endl;
	}
}