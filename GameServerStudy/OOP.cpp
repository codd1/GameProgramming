#include <iostream>
using namespace std;

// 객체지향 (Object Oriented Programming)
// 데이터 + 로직

// 플레이어, 몬스터, GameRoom, Lobby(장소) 등도 객체가 된다.
class Knight {
public:
	// 기본 생성자 (Constructor)
	Knight() {
		m_hp = 0;
		m_attack = 0;
		m_defence = 0;
		cout << "Knight()" << endl;
	}
	// 기타 생성자
	Knight(int hp, int attack, int defence) {
		m_hp = hp;
		m_attack = attack;
		m_defence = defence;
		cout << "Knight()" << endl;
	}
	// 복사 생성자
	Knight(const Knight& other) {
		m_hp = other.m_hp;
		m_attack = other.m_attack;
		m_defence = other.m_defence;
		cout << "Knight(const Knight& other)" << endl;
	}
	// 소멸자 (Destructor) - 딱 1개만 존재
	~Knight() {
		cout << "~Knight()" << endl;
	}

public:
	// 멤버 함수
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
	// 멤버 변수
	int m_hp;
	int m_attack;
	int m_defence;
};

int main() {
	Knight k1(100,10,1);
	Knight k2(k1);	// k1의 데이터를 복사

	cout << k1.m_hp << endl;
}