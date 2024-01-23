#pragma once

class Object;		// ���漱��: Object��� Ŭ������ "�����Ѵ�"��"��" �˷��ִ� �� (Ŭ���� ���Ǵ� ��)

// 15. ObjectManager Ŭ���� ����
class ObjectManager
{
public:
	DECLARE_SINGLE(ObjectManager);

	// �Ϲ������� vector�� �����͸� ���ҷ� ���� ��� ������ ������ ���� Add, Remove�� ���� �Լ��� ���� ����
	void Add(Object* object);
	void Remove(Object* object);
	
	template <typename T>
	T* CreateObject() {
		T* object = new T();
		object->Init();		// ���� Ÿ���� ���� �𸣴µ� Init �Լ��� �ִٴ°� ��� �˱�?
							// -> �����Ŷ�� �����ϰ� �ϴ� �����ϰ�, ������ ������ ���鼭 ����

		return object;
	}

private:
	vector<Object*> _objects;
};

