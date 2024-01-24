#pragma once

class LineMesh;

// 8. ResourceManager ����
class ResourceManager
{
public:
	DECLARE_SINGLE(ResourceManager);
	~ResourceManager();

public:
	void Init();
	void Clear();
	// ���⼭�� Update() �Լ� X --> �׻� �Ȱ��� ����� �� X

	// 32. GetLineMesh �Լ� ���� + Init() �Լ� ���� ä���
	const LineMesh* GetLineMesh(wstring key);

private:
	unordered_map<wstring, LineMesh*> _lineMeshes;
};

