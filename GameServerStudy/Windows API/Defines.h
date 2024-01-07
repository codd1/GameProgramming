#pragma once

#define DECLARE_SINGLE(classname)			\
private:									\
	classname() { }							\
public:										\
	static classname* GetInstance() {		\
		static classname s_instance;		\
		return &s_instance;					\
	}
// static�� ��ü�� �������ΰ� �ƴ϶� Ŭ������ �������̴�.


#define GET_SINGLE(classname)	classname::GetInstance()


#define SAFE_DELETE(ptr)	\
if(ptr)						\
{							\
	delete ptr;				\
	ptr = nullptr;			\
}							\
// (1) ptr ���� Ȯ�� ��, (2) delete, (3) null �ֱ� --> Delete 3����