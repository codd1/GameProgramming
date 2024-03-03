#include "pch.h"
#include "TimeManager.h"

void TimeManager::Init()
{
	// �ð� ���� ī������ ���ļ� (= �ʴ� ī���� ���� ��ȭ Ƚ��)
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency));
	// �ð� ���� ������ ����� �� �ִ� ���ػ�(<1us) Ÿ�ӽ������� ��Ÿ���� ���� ī������ ���� ��
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount));
}

// �ʴ� ������ ��(FPS)�� �����ϰ� �ϴ� �Լ�
void TimeManager::Update()
{
	uint64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));		// Windows API �Լ�
	// currentCount = �ð� ���� ī������ ���� ��

	// ���� �����Ӱ� ���� ������ ������ ��� �ð� (������ �� �ð� ����)
	// ���� ī���� ������ ���� ī���� ���� ���̸� ����ϰ�, �̸� �ð� ���� ī������ �󵵷� ����� ����ð� ���
	_deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);
	_prevCount = currentCount;		// ���� �����ӿ��� ���� �ð� ���� ī���� ������ ������Ʈ
	
	_frameCount++;				// ��������� ������ �� ���� (�� �����Ӹ��� ����)
	_frameTime += _deltaTime;	// ��������� ���� ��� �ð� (�� �����Ӹ��� _deltaTime �߰�)

	if (_frameTime >= 1.f) {	// 1�ʰ� ����ϸ� FPS�� ����ϰ� �ʱ�ȭ
		// �ʴ� ������ ��
		_fps = static_cast<uint32>(_frameCount / _frameTime);	// _fps = �� ������ ��

		// �ʱ� �������� �ʱ�ȭ
		_frameTime = 0.f;
		_frameCount = 0;
	}
}
