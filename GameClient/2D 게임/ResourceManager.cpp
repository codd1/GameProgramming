#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"

ResourceManager::~ResourceManager()
{
	Clear();
}

void ResourceManager::Init(HWND hwnd, fs::path resourcePath)
{
	_hwnd = hwnd;
	_resourcePath = resourcePath;

	//fs::current_path();
	//_resourcePath.relative_path();
	//fs::absolute(_resourcePath);

}

void ResourceManager::Clear()
{
	for (auto& item : _textures) {
		SAFE_DELETE(item.second);
	}

	_textures.clear();
}

Texture* ResourceManager::LoadTexture(const wstring& key, const wstring& path, uint32 transparent)
{
	// 찾은 값이 있는 경우
	if (_textures.find(key) != _textures.end()) {
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

Flipbook* ResourceManager::CreateFlipbook(const wstring& key)
{
	if (_flipbooks.find(key) != _flipbooks.end()) {
		return _flipbooks[key];
	}

	Flipbook* flipbook = new Flipbook();
	_flipbooks[key] = flipbook;

	return flipbook;
}
