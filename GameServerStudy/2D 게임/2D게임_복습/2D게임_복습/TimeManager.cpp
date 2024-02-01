#include "pch.h"
#include "TimeManager.h"

void TimeManager::Init()
{
	// 시간 측정 카운터의 주파수 (= 초당 카운터 값의 변화 횟수)
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency));
	// 시간 간격 측정에 사용할 수 있는 고해상도(<1us) 타임스탬프를 나타내는 성능 카운터의 현재 값
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount));
}

// 초당 프레임 수(FPS)를 유지하게 하는 함수
void TimeManager::Update()
{
	uint64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));		// Windows API 함수
	// currentCount = 시간 측정 카운터의 현재 값

	// 현재 프레임과 이전 프레임 사이의 경과 시간 (프레임 간 시간 간격)
	// 현재 카운터 값에서 이전 카운터 값의 차이를 계산하고, 이를 시간 측정 카운터의 빈도로 나누어서 경과시간 계산
	_deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);
	_prevCount = currentCount;		// 현재 프레임에서 사용된 시간 측정 카운터 값으로 업데이트
	
	_frameCount++;				// 현재까지의 프레임 수 저장 (매 프레임마다 증가)
	_frameTime += _deltaTime;	// 현재까지의 누적 경과 시간 (매 프레임마다 _deltaTime 추가)

	if (_frameTime >= 1.f) {	// 1초가 경과하면 FPS를 계산하고 초기화
		// 초당 프레임 수
		_fps = static_cast<uint32>(_frameCount / _frameTime);	// _fps = 촹 프레임 수

		// 초기 세팅으로 초기화
		_frameTime = 0.f;
		_frameCount = 0;
	}
}
