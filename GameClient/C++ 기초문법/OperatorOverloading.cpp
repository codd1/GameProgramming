#include <iostream>
using namespace std;

/*
	������ �����ε�
	1. ��� ������ �Լ� ����
		- a op b ���¿��� ������ �������� ����

	2. ���� ������ �Լ� ����
*/
class Pos {
public:
	Pos() {

	}
	explicit Pos(int b) {
		x = b;
		y = b;
	}
	Pos operator+(const Pos& b) {
		Pos pos;
		pos.x = x + b.x;
		pos.y = y + b.y;
		return pos;
	}
	Pos operator+(int b) {
		Pos pos;
		pos.x = x + b;
		pos.y = y + b;
		return pos;
	}

	bool operator==(const Pos& b) {
		return x == b.x && y == b.x;
	}

	// ���� ������
	void operator=(int b) {
		x = b;
		y = b;
	}

public:
	int x = 0;
	int y = 0;
};

Pos operator+(int a, const Pos& b) {
	Pos pos;
	pos.x = a + b.x;
	pos.y = a + b.y;
	return pos;
}

int main() {
	int a = 10;
	int b = 20;
	int c = a + b;

	// �̷��� �ʱ�ȭ�ϴ� ��쿡�� ���� �����ڴ� ���� ������� �ʰ� �����ڰ� ����ȴ�. -> �̰��� ���� �ʹٸ� explicit (���� ����)
	Pos pos1 = 10;		// ��, Pos pos1(10); �� �����ϰ� ����
	Pos pos2 = 20;		// ��, Pos pos2(20); �� �����ϰ� ����

	// explicit�� ����� ��� �̷��� ����ؾ��Ѵ�.
	Pos pos1(10);
	Pos pos2(20);

	// �� ���� ����
	pos1 = 10;
	pos2 = 20;

	Pos pos3 = pos1 + pos2;
	//pos3 = pos1.operator+(pos2);	// �� ����� ����
	pos3 = 10 + pos1;	// Pos operator+(int a, const Pos& b) �Լ� ���п� ����

	cout << pos3.x;
}