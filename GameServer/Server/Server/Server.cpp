#include <iostream>
#include <thread>
#include <vector>
#include <Windows.h>

using namespace std;

int buffer[10000][10000];

int main()
{
    ::memset(buffer, 0, sizeof(buffer));

    {   // 1. sum을 구하는 코드의 시간 체크
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

    {   // 2. sum을 구하는 코드의 시간 체크
        auto start = GetTickCount64();

        __int64 sum = 0;

        for (int i = 0; i < 10000; i++) {
            for (int j = 0; j < 10000; j++) {
                sum += buffer[j][i];        // 이 부분만 다름
            }
        }

        auto end = GetTickCount64();

        cout << "Elapsed Tick " << (end - start) << endl;
        /*
            실행 결과
            Elapsed Tick 78
            Elapsed Tick 406

            약 5~6배의 시간 차이가 난다. --> 즉, 캐시가 있다!
        */
    }
}