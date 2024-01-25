#pragma once

class Object;		// 전방선언: Object라는 클래스가 "존재한다"고"만" 알려주는 것 (클래스 정의는 모름)

// 15. ObjectManager 클래스 생성
class ObjectManager
{
public:
	DECLARE_SINGLE(ObjectManager);
	// 41. ObjectManager 소멸자 추가
	~ObjectManager();

	// 일반적으로 vector를 포인터를 원소로 갖는 멤버 변수로 선언할 때는 Add, Remove와 같은 함수를 같이 선언
	void Add(Object* object);
	void Remove(Object* object);
	
	template <typename T>
	T* CreateObject() {
		T* object = new T();
		object->Init();		// 아직 타입이 뭔지 모르는데 Init 함수가 있다는걸 어떻게 알까?
							// -> 있을거라고 생각하고 일단 실행하고, 없으면 에러를 내면서 종료

		return object;
	}

private:
	vector<Object*> _objects;

public:
	const vector<Object*>& GetObjects() { return _objects; }

	// 40. Clear() 함수 추가
	void Clear();
};

