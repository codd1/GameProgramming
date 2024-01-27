#include "pch.h"
#include "ResourceManager.h"
#include "LineMesh.h"

ResourceManager::~ResourceManager()
{
    Clear();
}

// 63. UI, Menu, CanonTank, MissileTank.txt �߰�
void ResourceManager::Init()
{
    {
        LineMesh* mesh = new LineMesh();    // new�� ������ delete �ʿ� -> Clear()
        mesh->Load(L"UI.txt");      // UI.txt ���� �ε�
        _lineMeshes[L"UI"] = mesh;  // "UI"��� �̸����� mesh(������)�� map�� ���
                                    // ���� "UI"��� �̸��� Ű�� ����� �ش� ��ü(LineMesh)�� ���� ����
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
