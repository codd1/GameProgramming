#include <iostream>
using namespace std;

// �Ϲ����� ��� ��

class Player {
public:
	Player() {
		id = idGenerator++;
	}

public:
	int id;
	static int idGenerator;
};

int Player::idGenerator = 1;

int main() {
	Player p1;
	Player p2;
	Player p3;

	cout << p1.id << endl;
	cout << p2.id << endl;
	cout << p3.id << endl;
}