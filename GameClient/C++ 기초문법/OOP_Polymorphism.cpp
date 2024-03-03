#include <iostream>
using namespace std;

// 객체지향 (Object Oriented Programming)
// 데이터 + 로직

/*
	OOP 3대 요소
	- 상속성 (Inheritance)
	- 은닉성 (Data hiding / encapsulation)
	- 다형성 (Polymorphism)
*/

// 오버로딩(overloading) = 함수 이름의 재사용
// 오버라이딩(overriding) = 부모 클래스의 함수를 자식 클래스에서 재정의

// 오버로딩
void Test() { }
void Test(int a) { }
void Test(float a) { }

// 추상 클래스
class Player {
public:
	//virtual void Move() { cout << "Player Move()" << endl; }
	virtual void Move() = 0;	// 순수 가상 함수: 가상 함수인데 구현부가 없고, 구현은 상속을 받는 클래스가 해야한다. -> 추상 클래스로 분류

	// 상위 클래스 소멸자에 virtual을 붙여줘야한다. 하위 클래스의 소멸자가 호출되지 않을 수 있기 때문이다.
	virtual ~Player() { }
public:
	int m_hp = 100;
};

class Knight :public Player {
public:
	virtual void Move() override { cout << "Knight Move()" << endl; }	// = 내가 가상함수인데, 부모 클래스에서 상속 받은 가상 함수를 override하여 재정의하겠다.
public:
	int m_stamina = 200;
};

void MovePlayer(Player* player) {
	player->Move();
}

int main() {
	//Player p1;	// 추상 클래스의 개체 사용 불가

	Knight k1;
	MovePlayer(&k1);
}