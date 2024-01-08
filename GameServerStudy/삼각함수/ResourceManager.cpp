#include "pch.h"
#include "ResourceManager.h"
#include "LineMesh.h"

ResourceManager::~ResourceManager()
{
	Clear();
}

void ResourceManager::Init()
{
	LineMesh* mesh = new LineMesh();
	mesh->Load(L"Player.txt");

	_lineMeshes[L"Player"] = mesh;
}

void ResourceManager::Clear()
{
	for (auto mesh : _lineMeshes) {
		SAFE_DELETE(mesh.second);		// unordered_map(키, 값)이므로 second(값)를 이용
	}
	_lineMeshes.clear();
}

const LineMesh* ResourceManager::GetLineMesh(wstring key)
{
	auto findIter = _lineMeshes.find(key);
	if (findIter == _lineMeshes.end()) {
		return nullptr;
	}

	return findIter->second;
}
