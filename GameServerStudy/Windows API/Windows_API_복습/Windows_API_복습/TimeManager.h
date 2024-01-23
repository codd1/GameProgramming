#pragma once
// 5. TimeManager ����
class TimeManager
{
public:
	// TimeManager�� ��Ŭ������ �����ϰ� �ȴ�.
	DECLARE_SINGLE(TimeManager);

public:
	void Init();
	void Update();

private:
	uint64 _frequency = 0;
	uint64 _prevCount = 0;
};

