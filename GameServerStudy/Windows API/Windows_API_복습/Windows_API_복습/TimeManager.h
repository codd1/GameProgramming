#pragma once
// 5. TimeManager 생성
class TimeManager
{
public:
	// TimeManager가 싱클톤으로 동작하게 된다.
	DECLARE_SINGLE(TimeManager);

public:
	void Init();
	void Update();

private:
	uint64 _frequency = 0;
	uint64 _prevCount = 0;
};

