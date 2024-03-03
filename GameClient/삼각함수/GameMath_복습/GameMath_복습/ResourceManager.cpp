#include "pch.h"
#include "ResourceManager.h"
#include "LineMesh.h"

ResourceManager::~ResourceManager()
{
    Clear();
}

// 63. UI, Menu, CanonTank, MissileTank.txt 추가
void ResourceManager::Init()
{
    {
        LineMesh* mesh = new LineMesh();    // new가 있으니 delete 필요 -> Clear()
        mesh->Load(L"UI.txt");      // UI.txt 파일 로드
        _lineMeshes[L"UI"] = mesh;  // "UI"라는 이름으로 mesh(포인터)를 map에 등록
                                    // 이제 "UI"라는 이름을 키로 사용해 해당 객체(LineMesh)에 접근 가능
    }

    {
        LineMesh* mesh = new LineMesh();
        mesh->Load(L"Menu.txt");
        _lineMeshes[L"Menu"] = mesh;
    }

    {
        LineMesh* mesh = new LineMesh();
        mesh->Load(L"CanonTank.txt");
        _lineMeshes[L"CanonTank"] = mesh;
    }

    {
        LineMesh* mesh = new LineMesh();
        mesh->Load(L"MissileTank.txt");
        _lineMeshes[L"MissileTank"] = mesh;
    }   
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
