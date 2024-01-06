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