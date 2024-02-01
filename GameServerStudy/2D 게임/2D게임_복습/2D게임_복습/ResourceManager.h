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
	// ���⼭�� Update() �Լ� X --> �׻� �Ȱ��� ����� �� X

	const LineMesh* GetLineMesh(wstring key);

private:
	unordered_map<wstring, LineMesh*> _lineMeshes;
};

