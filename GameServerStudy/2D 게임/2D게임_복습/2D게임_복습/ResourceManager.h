#pragma once

class LineMesh;

class ResourceManager
{
public:
	DECLARE_SINGLE(ResourceManager);
	~ResourceManager();

public:
	void Init();
	void Clear();
	// 여기서는 Update() 함수 X --> 항상 똑같이 만드는 것 X

	const LineMesh* GetLineMesh(wstring key);

private:
	unordered_map<wstring, LineMesh*> _lineMeshes;
};

