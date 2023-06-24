#include <iostream>
using namespace std;

// ������ ���� - �̱���, ������, ������Ʈ ��..

/*
	Singleton
	- ���� �� 1���� �����ϰ� ��𼭵� ����� �� �ִ� [�Ŵ���] Ŭ����
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

#define GET_MANAGER (UserManager::GetInstance())	//GET_MANAGER->AddUser();		// �̷��� ���� ��쵵 �ִ�.

int main() {
	for (int i = 0; i < 10; i++) {
		UserManager::GetInstance()->AddUser();
	}

	cout << UserManager::GetInstance()->GetUserCount() << endl;
}