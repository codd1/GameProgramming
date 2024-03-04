#include <iostream>
#include <thread>
#include <vector>
#include <windows.h>
#include <atomic>

using namespace std;

//int sum = 0;
atomic<int>sum = 0;

void Add() {
	for (int i = 0; i < 1000000; i++) {		// 100만 번
		sum++;	// atomic 사용 이후 -> All or Nothing (실행이 되거나 안되거나 둘 중 하나. 중간에 다른게 끼어들 수 X)
		
		//// 어셈블리어로 확인해보면 sum++;은 3단계로 이루어짐 (atomic 사용 전)
		//int eax = sum;		// 0
		//eax = sum + 1;		// 0 -> 1
		//sum = eax;			// sum <- 1
	}
}

void Sub() {
	for (int i = 0; i < 1000000; i++) {
		sum--;

		//int eax = sum;		// 0
		//eax = sum - 1;		// 0 -> -1
		//sum = eax;			// sum <- -1
	}
}

int main()
{
	thread t1(Add);
	thread t2(Sub);

	t1.join();
	t2.join();

	cout << sum << endl;
}