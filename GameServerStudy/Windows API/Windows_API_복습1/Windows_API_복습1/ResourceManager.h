#pragma once

class LineMesh;

// 8. ResourceManager 생성
class ResourceManager
{
public:
	DECLARE_SINGLE(ResourceManager);
	~ResourceManager();

public:
	void Init();
	void Clear();
	// 여기서는 Update() 함수 X --> 항상 똑같이 만드는 것 X

	// 32. GetLineMesh 함수 정의 + Init() 함수 내용 채우기
	const LineMesh* GetLineMesh(wstring key);

private:
	unordered_map<wstring, LineMesh*> _lineMeshes;
};

