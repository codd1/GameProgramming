#pragma once

class Object;

class ObjectManager
{
public:
	DECLARE_SINGLE(ObjectManager);

	~ObjectManager();

	void Add(Object* object);		// 벡터에 새로운 object 추가
	void Remove(Object* object);
	void Clear();

	const vector<Object*>& GetObjects() { return _objects; }

	// 한군데에 몰빵해서 생성(new)하는게 좋다. 그래서 여기에 템플릿으로 생성
	template <typename T>
	T* CreateObject() {
		T* object = new T();
		object->Init();			// 아직 타입이 뭔지 모르는데 Init 함수가 있다는걸 어떻게 알까?
								// 있을거라고 생각하고 일단 실행하고, 없으면 에러를 내면서 종료

		return object;
	}

private:
	vector<Object*> _objects;
};

