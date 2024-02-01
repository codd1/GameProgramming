#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"

ResourceManager::~ResourceManager()
{
    Clear();
}

void ResourceManager::Init(HWND hwnd, fs::path resourcePath)
{
    _hwnd = hwnd;
    _resourcePath = resourcePath;
}

// _lineMeshes에 저장된 LineMesh 객체들을 삭제하고 unordered_map 전체를 비움 (delete)
void ResourceManager::Clear()
{

}

Texture* ResourceManager::LoadTexture(const wstring& key, const wstring& path, uint32 transparent)
{
    if (_textures.find(key) != _textures.end()) {   // 이미 같은 texture가 있는 경우
        return _textures[key];
    }
    
    fs::path fullPath = _resourcePath / path;

    Texture* texture = new Texture();
    texture->LoadBmp(_hwnd, fullPath.c_str());
    texture->SetTransparent(transparent);
    _textures[key] = texture;

    return texture;
}

Sprite* ResourceManager::CreateSprite(const wstring& key, Texture* texture, int32 x, int32 y, int cx, int cy)
{
    if (_sprites.find(key) != _sprites.end()) {
        return _sprites[key];
    }

    if (cx == 0) {
        cx = texture->GetSize().x;
    }

    if (cy == 0) {
        cy = texture->GetSize().y;
    }

    Sprite* sprite = new Sprite(texture, x, y, cx, cy);
    _sprites[key] = sprite;

    return sprite;
}
