#include <iostream>
using namespace std;

// 객체지향 (Object Oriented Programming)
// 데이터 + 로직

/*
	OOP 3대 요소
	- 상속성 (Inheritance)
	- 은닉성 (Data hiding / encapsulation)
	- 다형성
*/

/*
	은닉성 (접근 지정자)
	접근 지정자 - public / protected / private
	접근 지정자를 사용하는 이유? - 정말 위험하고, 건드리면 안 되는 경우, 다른 경로로 접근하길 원하는 경우

	자동차 - 핸들/페달/엔진/문/전기선/휘발유
	구매자 입장에서 알아야하는 내용: 핸들, 페달, 문
	구매자 입장에서 몰라도 되는 내용: 엔진, 전기선, 휘발유
*/

class Car {
public:
	// 정말 필요한 것들만 공개
	void MoveHandle() { }
	void PushPedal() { }
	void OpenDoor() { }
	void TurnKey() {
		// ...
		PutFuelInEngine();
		// ...
	}

protected:
	// 몰라도 되는 부분(=언제 어디서든 사용하려는 함수X)
	void Disassemble() { }	// 차량 분해
	void PutFuelInEngine() { }
	void ConnectCircuit() { }
public:
	// 핸들
	// 페달
	// 엔진
	// 문
	// 전기선
};

// 상속 접근 지정자: 다음 세대한테 부모님의 유산을 어떻게 물려줄지?
// public: 부모님이 물려준걸 그대로 상속 받는다.
// protected: 내 자식들한테만 물려줄거야. (public -> protected)
// private: 나까지만 꿀빤다. 물려주지 않을거야. (public, protected -> private)
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
		//MoveHandle();	// SuperCar(부모)에서는 public이지만 여기(자식)에서는 private 상태로 물려받음.
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

	//c.Disassemble();	// 접근불가

	Knight k1;
	//k1.m_hp = 200;		// 이런식으로 멤버변수를 멋대로 밖에서 접근해서 변경하는 것은 매우 위험하다. 어디서 값이 변경됐는지 찾기 어렵다. -> private + Get,Set함수
	k1.SetHP(100);
}