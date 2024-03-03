#pragma once

#define DECLARE_SINGLE(classname)			\
private:									\
	classname() { }							\
public:										\
	static classname* GetInstance() {		\
		static classname s_instance;		\
		return &s_instance;					\
	}
// static은 객체에 종속적인게 아니라 클래스에 종속적이다.


#define GET_SINGLE(classname)	classname::GetInstance()


#define SAFE_DELETE(ptr)	\
if(ptr)						\
{							\
	delete ptr;				\
	ptr = nullptr;			\
}							\
// (1) ptr 존재 확인 후, (2) delete, (3) null 넣기 --> Delete 3형제