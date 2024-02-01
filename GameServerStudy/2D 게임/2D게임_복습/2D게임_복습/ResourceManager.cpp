#include "pch.h"
#include "ResourceManager.h"

ResourceManager::~ResourceManager()
{
    Clear();
}

void ResourceManager::Init()
{
   
}

// _lineMeshes에 저장된 LineMesh 객체들을 삭제하고 unordered_map 전체를 비움 (delete)
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
    if (findIter == _lineMeshes.end()) {    // 해당 key가 _lineMeshes에 없는 경우
        return nullptr;
    }

    // 해당 key에 해당하는 원소를 찾은 경우 값을 리턴 (여기서는 LineMesh 객체에 대한 포인터)
    return findIter->second;
}
