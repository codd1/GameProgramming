#include "pch.h"
#include "ResourceManager.h"

ResourceManager::~ResourceManager()
{
    Clear();
}

void ResourceManager::Init()
{
   
}

// _lineMeshes�� ����� LineMesh ��ü���� �����ϰ� unordered_map ��ü�� ��� (delete)
void ResourceManager::Clear()
{
    for (auto mesh : _lineMeshes) {
        SAFE_DELETE(mesh.second);
    }

    _lineMeshes.clear();
}

const LineMesh* ResourceManager::GetLineMesh(wstring key)
{
    auto findIter = _lineMeshes.find(key);
    if (findIter == _lineMeshes.end()) {    // �ش� key�� _lineMeshes�� ���� ���
        return nullptr;
    }

    // �ش� key�� �ش��ϴ� ���Ҹ� ã�� ��� ���� ���� (���⼭�� LineMesh ��ü�� ���� ������)
    return findIter->second;
}
