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
// volatile bool ready = false;

void Thread_1() {
	ready = false;

	while (ready == false) {

	}

	cout << "Yeah!!!" << endl;
}

int main()
{
	thread t1(Thread_1);

	this_thread::sleep_for(1s);

	ready = true;

	t1.join();
}