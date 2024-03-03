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
	Knight() :m_hp(0), m_inventory(100), m_hpRef(m_hp), m_hpConst(m_hp)		// 이게 더 효율적이다.
	/*
		선처리 영역
		Player()
		m_inventory = Inventory()
	*/ {
		// 여기서 초기화하는 방식이 제일 별로다.
		//m_hp = 0;
		//m_inventory = Inventory(100);		// 이러면 생성자가 2번 호출될 수 있다. (물론 다른 생성자긴하지만) -> 비효율적

		//m_hpRef = m_hp;
		//m_hpConst = m_hp;		// 이런 애들은 선처리 영역에서 초기화해줘야한다. (여기서 초기화하면 오류 발생)

		cout << "Knight()" << endl;
	}

	~Knight() {
		cout << "~Knight()" << endl;
	}
public:
	int m_hp;
	int m_defence = 20;

	// 초기화 필요
	int& m_hpRef;
	const int m_hpConst;

	Inventory m_inventory;
};

int main() {
	// C# vs C++
	// C# Knight k1 = new Knight();
	// C++ Knight* k1 = new Knight();	// 동적할당

	Knight k1;	// 실행되는 순간 생성자 호출


	// 지역변수 특성상 중괄호 안에서만 유효하기 떄문에 중괄호가 닫히면 객체가 소멸된다. (=소멸자 호출) -> 일찍 소멸시키고 싶으면 범위 적용
	{
		Knight k2;
	}

	/*
		아래 첫 번째 경우는 객체 생성을 for문 안에서 하는 것이고,
		아래 두 번째 경우는 객체 생성을 for문 밖에서 한 번 한 것이다.

		첫 번째 경우는 for문에서 반복될 때마다 매번 객체를 새로 생성하기 때문에 생성자, 소멸자가 계속 호출되기 때문에
		두 가지 경우는 미묘하게 성능차이가 나게된다.
	*/

	// 첫 번째 경우
	for (int i = 0; i < 10; i++) {
		Knight k3;
		cout << "k3: " << i << endl;
	}

	// 두 번째 경우
	Knight k4;
	for (int i = 0; i < 10; i++) {
		cout << "k4: " << i << endl;
	}
}