#include <iostream>
using namespace std;

//const int GBB_SCISSORS = 0;
//const int GBB_ROCK = 1;
//const int GBB_PAPER = 2;

enum ENUM_GBB {
	GBB_SCISSORS,
	GBB_ROCK,
	GBB_PAPER
};

int main()
{
	// 가위바위보 (연습 문제)

	srand(time(0));

	while (true) {
		cout << "가위(0) 바위(1) 보(2) 중에 골라주세요!" << endl;

		int value;  // 사용자 입력 값
		cin >> value;

		int computerValue = rand() % 3;     // 컴퓨터 입력 값

		if (value == GBB_SCISSORS) {   // 가위
			switch (computerValue) {
			case GBB_SCISSORS: // 가위
				cout << "가위(Player) vs 가위(Computer): 비겼습니다!" << endl;
				break;
			case GBB_ROCK: // 바위
				cout << "가위(Player) vs 바위(Computer): 졌습니다!" << endl;
				break;
			case GBB_PAPER: // 보
				cout << "가위(Player) vs 보(Computer): 비겼습니다!" << endl;
				break;
			default:
				break;
			}
		}
		else if (value == GBB_ROCK) {  // 바위
			switch (computerValue) {
			case GBB_SCISSORS: // 가위
				cout << "바위(Player) vs 가위(Computer): 이겼습니다!" << endl;
				break;
			case GBB_ROCK: // 바위
				cout << "바위(Player) vs 바위(Computer): 비겼습니다!" << endl;
				break;
			case GBB_PAPER: // 보
				cout << "바위(Player) vs 보(Computer): 졌습니다!" << endl;
				break;
			default:
				break;
			}
		}
		else {  // 보
			switch (computerValue) {
			case GBB_SCISSORS: // 가위
				cout << "보(Player) vs 가위(Computer): 졌습니다!" << endl;
				break;
			case GBB_ROCK: // 바위
				cout << "보(Player) vs 바위(Computer): 이겼습니다!" << endl;
				break;
			case GBB_PAPER: // 보
				cout << "보(Player) vs 보(Computer): 비겼습니다!" << endl;
				break;
			default:
				break;
			}
		}
	}

}
