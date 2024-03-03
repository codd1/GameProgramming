#include <iostream>
using namespace std;

// 디자인 패턴 - 싱글톤, 옵저버, 컴포넌트 등..

/*
	Singleton
	- 정말 딱 1개만 존재하고 어디서든 사용할 수 있는 [매니저] 클래스
*/

class UserManager {
public:
	static UserManager* GetInstance() {
		static UserManager um;
		return &um;
	}

public:
	void AddUser() { userCount++; }
	int GetUserCount() { return userCount; }

private:
	int userCount = 0;
};

#define GET_MANAGER (UserManager::GetInstance())	//GET_MANAGER->AddUser();		// 이렇게 쓰는 경우도 있다.

int main() {
	for (int i = 0; i < 10; i++) {
		UserManager::GetInstance()->AddUser();
	}

	cout << UserManager::GetInstance()->GetUserCount() << endl;
}