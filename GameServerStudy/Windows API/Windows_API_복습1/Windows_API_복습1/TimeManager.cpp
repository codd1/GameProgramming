#include "pch.h"
#include "TimeManager.h"

void TimeManager::Init()
{
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency));		// ���� ī������ ��
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount));	// �ð� ���� ������ ����� �� �ִ� ���ػ�(<1us) Ÿ�ӽ������� ��Ÿ���� ���� ī������ ���� ��
}

void TimeManager::Update()
{
}
