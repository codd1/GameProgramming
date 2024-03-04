#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void HelloThread(int i) {
    while (true) {
        cout << "Hello Thread" << i << endl;
    }
}
int main()
{
    vector<thread> threads;

    for (int i = 0; i < 10; i++) {
        threads.push_back(thread(HelloThread, i));
    }

    cout << "Hello Main" << endl;

    for (thread& t : threads) {
        t.join();
    }
    
}