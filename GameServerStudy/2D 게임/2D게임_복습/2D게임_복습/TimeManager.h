#pragma once

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
	float _deltaTime = 0.f;

	uint32 _frameCount = 0;
	float _frameTime = 0.f;
	uint32 _fps = 0;

public:
	float GetDeltaTime() { return _deltaTime; }
	
	uint32 GetFps() { return _fps; }
};

