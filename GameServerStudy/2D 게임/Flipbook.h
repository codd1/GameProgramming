#pragma once
#include "ResourceBase.h"
#include "Texture.h"

struct FlipbookInfo {
	Texture* texture = nullptr;
	wstring name;
	Vec2Int size = {};		// ���ҽ�(��Ʈ�� �̹���)���� �� ĭ�� ũ��
	int32 start = 0;	// ���ҽ�(��Ʈ�� �̹���)���� ���� ��ġ
	int32 end = 0;		// ���ҽ�(��Ʈ�� �̹���)���� �� ��° �ٿ� ��ġ�ϴ���
	int32 line = 0;		// �� ������ ������
	float duration = 1.f;	// �ִϸ��̼� �ӵ�
	bool loop = true;		// �ִϸ��̼� �ݺ� ����
};
class Flipbook : public ResourceBase
{
public:
	Flipbook();
	virtual ~Flipbook();

	void SetInfo(const FlipbookInfo& info) { _info = info; }
	const FlipbookInfo& GetInfo() { return _info; }

private:
	FlipbookInfo _info;

};

