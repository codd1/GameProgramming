#include <iostream>
#include <thread>
#include <vector>
#include <Windows.h>

using namespace std;

int buffer[10000][10000];

int main()
{
    ::memset(buffer, 0, sizeof(buffer));

    {
        auto start = GetTickCount64();

        __int64 sum = 0;

        for (int i = 0; i < 10000; i++) {
            for (int j = 0; j < 10000; j++) {
                sum += buffer[i][j];
            }
        }

        auto end = GetTickCount64();

        cout << "Elapsed Tick " << (end - start) << endl;
    }

    {
        auto start = GetTickCount64();

        __int64 sum = 0;

        for (int i = 0; i < 10000; i++) {
            for (int j = 0; j < 10000; j++) {
                sum += buffer[j][i];
            }
        }

        auto end = GetTickCount64();

        cout << "Elapsed Tick " << (end - start) << endl;
    }
}