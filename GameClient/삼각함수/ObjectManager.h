#pragma once

class Object;

class ObjectManager
{
public:
	DECLARE_SINGLE(ObjectManager);

	~ObjectManager();

	void Add(Object* object);		// ���Ϳ� ���ο� object �߰�
	void Remove(Object* object);
	void Clear();

	const vector<Object*>& GetObjects() { return _objects; }

	// �ѱ����� �����ؼ� ����(new)�ϴ°� ����. �׷��� ���⿡ ���ø����� ����
	template <typename T>
	T* CreateObject() {
		T* object = new T();
		object->Init();			// ���� Ÿ���� ���� �𸣴µ� Init �Լ��� �ִٴ°� ��� �˱�?
								// �����Ŷ�� �����ϰ� �ϴ� �����ϰ�, ������ ������ ���鼭 ����

		return object;
	}

private:
	vector<Object*> _objects;
};

