#include <iostream>
using namespace std;

// ��ü���� (Object Oriented Programming)
// ������ + ����

/*
	OOP 3�� ���
	- ��Ӽ� (Inheritance)
	- ���м� (Data hiding / encapsulation)
	- ������
*/

/*
	���м� (���� ������)
	���� ������ - public / protected / private
	���� �����ڸ� ����ϴ� ����? - ���� �����ϰ�, �ǵ帮�� �� �Ǵ� ���, �ٸ� ��η� �����ϱ� ���ϴ� ���

	�ڵ��� - �ڵ�/���/����/��/���⼱/�ֹ���
	������ ���忡�� �˾ƾ��ϴ� ����: �ڵ�, ���, ��
	������ ���忡�� ���� �Ǵ� ����: ����, ���⼱, �ֹ���
*/

class Car {
public:
	// ���� �ʿ��� �͵鸸 ����
	void MoveHandle() { }
	void PushPedal() { }
	void OpenDoor() { }
	void TurnKey() {
		// ...
		PutFuelInEngine();
		// ...
	}

protected:
	// ���� �Ǵ� �κ�(=���� ��𼭵� ����Ϸ��� �Լ�X)
	void Disassemble() { }	// ���� ����
	void PutFuelInEngine() { }
	void ConnectCircuit() { }
public:
	// �ڵ�
	// ���
	// ����
	// ��
	// ���⼱
};

// ��� ���� ������: ���� �������� �θ���� ������ ��� ��������?
// public: �θ���� �����ذ� �״�� ��� �޴´�.
// protected: �� �ڽĵ����׸� �����ٰž�. (public -> protected)
// private: �������� �ܺ���. �������� �����ž�. (public, protected -> private)
class SuperCar : private Car {
public:
	void Test() {
		MoveHandle();
		Disassemble();
	}
};

class UltraSuperCar : public SuperCar {
public:
	void Test() {
		//MoveHandle();	// SuperCar(�θ�)������ public������ ����(�ڽ�)������ private ���·� ��������.
	}
};

class Knight {
public:
	void SetHP(int hp) {
		m_hp = 40;
	}
	int GetHP() { return m_hp; }
private:
	int m_hp = 100;
};

int main() {
	Car c;

	//c.Disassemble();	// ���ٺҰ�

	Knight k1;
	//k1.m_hp = 200;		// �̷������� ��������� �ڴ�� �ۿ��� �����ؼ� �����ϴ� ���� �ſ� �����ϴ�. ��� ���� ����ƴ��� ã�� ��ƴ�. -> private + Get,Set�Լ�
	k1.SetHP(100);
}