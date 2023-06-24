#include <iostream>
using namespace std;

/*
	연산자 오버로딩
	1. 멤버 연산자 함수 버전
		- a op b 형태에서 왼쪽을 기준으로 실행

	2. 전역 연산자 함수 버전
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

	// 대입 연산자
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

	// 이렇게 초기화하는 경우에는 대입 연산자는 전혀 실행되지 않고 생성자가 실행된다. -> 이것을 막고 싶다면 explicit (예방 차원)
	Pos pos1 = 10;		// 즉, Pos pos1(10); 과 동일하게 동작
	Pos pos2 = 20;		// 즉, Pos pos2(20); 과 동일하게 동작

	// explicit을 사용한 경우 이렇게 사용해야한다.
	Pos pos1(10);
	Pos pos2(20);

	// 이 경우는 대입
	pos1 = 10;
	pos2 = 20;

	Pos pos3 = pos1 + pos2;
	//pos3 = pos1.operator+(pos2);	// 윗 문장과 동일
	pos3 = 10 + pos1;	// Pos operator+(int a, const Pos& b) 함수 덕분에 가능

	cout << pos3.x;
}