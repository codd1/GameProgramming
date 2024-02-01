#pragma once

/*
	C++의 특정 클래스를 싱글톤(Singleton) 디자인 패턴으로 구현하기 위한 매크로

	싱글톤은 어떤 클래스의 "인스턴스가 오직 하나만 존재"하도록 하는 디자인 패턴으로, 주로 전역 상태나 공유 리소스에 접근할 때 사용된다.
	해당 클래스의 생성자는 private로 선언되어 있어 외부에서 직접 객체를 생성할 수 없다.
	대신, GetInstance라는 정적 메서드를 통해 유일한 인스턴스에 접근할 수 있다. 이 메서드 내에서는 정적으로 선언된 클래스의 인스턴스를 반환.
	정적으로 선언된 인스턴스는 해당 클래스의 유일한 인스턴스가 되어 싱글톤 패턴을 구현한다.

	이렇게 함으로써 어디서든지 Ex) TimeManager::GetInstance()를 호출하여 유일한 인스턴스에 접근할 수 있게 된다.
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