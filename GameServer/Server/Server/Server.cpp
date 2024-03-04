#include <iostream>
#include <thread>
#include <vector>
#include <windows.h>

using namespace std;

int x = 0;
int y = 0;
int r1 = 0;
int r2 = 0;

bool ready = false;

void Thread_1() {
	while (ready == false){ }

	y = 1;	// Store y
	// --------------------
	r1 = x;	// Load x

	// 위에서 y = 1; 과 r1 = x; 는 아예 독립적인 명령이다.
	// 그렇기 때문에 CPU 마음대로 r1 = x; 명령이 더 연산이 빨리 될 것 같으면 r1 = x; y = 1; 순서로 실행할 수 있게 된다.
	// CPU가 명령어를 받을 때 무조건 순서대로 처리하지 XXX
}

void Thread_2() {
	while (ready == false) { }

	x = 1;	// Store x
	// --------------------
	r2 = y;	// Load y
}

int main()
{
	int count = 0;

	while (true) {
		ready = false;
		count++;

		x = y = r1 = r2 = 0;

		thread t1(Thread_1);
		thread t2(Thread_2);

		ready = true;

		t1.join();
		t2.join();

		if (r1 == 0 && r2 == 0) {
			break;
		}
	}

	cout << count << endl;
}