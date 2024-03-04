#include <iostream>
#include <thread>
#include <vector>
#include <windows.h>
#include <atomic>

using namespace std;

atomic<int>sum = 0;

void Add() {
	for (int i = 0; i < 1000000; i++) {		// 100만 번
		sum++;	// atomic 사용 이후 -> All or Nothing
	}
}

void Sub() {
	for (int i = 0; i < 1000000; i++) {
		sum--;
	}
}

int main()
{
	//int temp = sum;
	int temp = sum.load();	// 위와 같은 의미인데, load함수를 쓰면 atomic하게 가져온다는 의미가 직관적으로 보임.

	//sum = 10;
	sum.store(10);	// 위와 같은 의미, 직관적

	int temp = sum.exchange(10);	// sum에 10을 저장하기 전, sum의 값. 단순히 temp라고 생각할 수 있지만 저장되기 전에 다른 값이 들어올 수 있다는 것도 항상 염두에 둬야 함.

	int prev = sum.fetch_add(10);	// sum에 10을 저장한 후, 10을 저장하기 전의 값

	thread t1(Add);
	thread t2(Sub);

	t1.join();
	t2.join();

	cout << sum << endl;
}