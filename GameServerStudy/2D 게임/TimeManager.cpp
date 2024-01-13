#include "pch.h"
#include "TimeManager.h"

void TimeManager::Init()
{
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount));	// CPU Ŭ��
}

void TimeManager::Update()
{
	uint64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	// ��� �ð�
	_deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);
	_prevCount = currentCount;

	_frameCount++;
	_frameTime += _deltaTime;

	if (_frameTime >= 1.f) {
		_fps = static_cast<uint32>(_frameCount / _frameTime);

		// �ʱ� �������� �ʱ�ȭ
		_frameTime = 0.f;
		_frameCount = 0;
	}
}

// GameCoding.cpp�� ���η��� ������ �� �� ���� ���ΰ��� ���� ��.
// 1�� ���� 60���� ����Ǿ� 60���� �����ϰ� �Ǹ� (= 1�� ���� 60�� ����) ������ 60 ���������� ����ȴٰ� �� �� �ִ�.
// ���� 60 �������� �����Ǿ�� ȭ���� �ε巴�� ���δ�. (�� ���ϴ� �� ���ٰ� ��)