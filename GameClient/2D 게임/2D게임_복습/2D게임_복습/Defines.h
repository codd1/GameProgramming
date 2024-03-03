#pragma once

/*
	C++�� Ư�� Ŭ������ �̱���(Singleton) ������ �������� �����ϱ� ���� ��ũ��

	�̱����� � Ŭ������ "�ν��Ͻ��� ���� �ϳ��� ����"�ϵ��� �ϴ� ������ ��������, �ַ� ���� ���³� ���� ���ҽ��� ������ �� ���ȴ�.
	�ش� Ŭ������ �����ڴ� private�� ����Ǿ� �־� �ܺο��� ���� ��ü�� ������ �� ����.
	���, GetInstance��� ���� �޼��带 ���� ������ �ν��Ͻ��� ������ �� �ִ�. �� �޼��� �������� �������� ����� Ŭ������ �ν��Ͻ��� ��ȯ.
	�������� ����� �ν��Ͻ��� �ش� Ŭ������ ������ �ν��Ͻ��� �Ǿ� �̱��� ������ �����Ѵ�.

	�̷��� �����ν� ��𼭵��� Ex) TimeManager::GetInstance()�� ȣ���Ͽ� ������ �ν��Ͻ��� ������ �� �ְ� �ȴ�.
*/
#define DECLARE_SINGLE(classname)			\
private:									\
	classname() { }							\
public:										\
	static classname* GetInstance() {		\
		static classname s_instance;		\
		return &s_instance;					\
	}

#define GET_SINGLE(classname)	classname::GetInstance()

#define SAFE_DELETE(ptr)	\
if (ptr)					\
{							\
	delete ptr;				\
	ptr = nullptr;			\
}