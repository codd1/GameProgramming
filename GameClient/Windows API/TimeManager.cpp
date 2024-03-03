#include "pch.h"
#include "TimeManager.h"

void TimeManager::Init()
{
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount));	// CPU 클럭
}

void TimeManager::Update()
{
	uint64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	// 경과 시간
	_deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);
	_prevCount = currentCount;

	_frameCount++;
	_frameTime += _deltaTime;

	if (_frameTime >= 1.f) {
		_fps = static_cast<uint32>(_frameCount / _frameTime);

		// 초기 세팅으로 초기화
		_frameTime = 0.f;
		_frameCount = 0;
	}
}

// GameCoding.cpp의 메인루프 안으로 몇 번 들어올 것인가에 대한 것.
// 1초 동안 60번씩 실행되어 60번씩 갱신하게 되면 (= 1초 동안 60번 갱신) 게임이 60 프레임으로 실행된다고 볼 수 있다.
// 보통 60 프레임은 유지되어야 화면이 부드럽게 보인다. (그 이하는 안 좋다고 봄)