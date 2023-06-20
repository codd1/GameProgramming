#include <iostream>
using namespace std;

int main()
{
    // 간단한 전투 (연습 문제)

    int round = 1;
    int hp = 100;   // 몬스터HP
    int damage = 10;    // 플레이어 데미지

    while (true) {
        // 전투 진행
        hp -= damage;
        if (hp < 0) {
            hp = 0;
        }
        cout << "Round: " << round << " 몬스터 체력: " << hp << endl;

        if (hp == 0) {
            cout << "몬스터 처치!" << endl;
            break;
        }

        if (round == 5) {
            cout << "제한 라운드 종료" << endl;
            break;
        }

        round++;
    }
    
}
