#pragma once
#include <d3d9.h>
#include <unordered_map>

#include "Graphic.h"

class Textures {
	static Textures* instance;
	std::unordered_map<int, LPDIRECT3DTEXTURE9> textures;
public:
	Textures();
	~Textures();

	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	bool hasContained(int id);
	LPDIRECT3DTEXTURE9 GetTexture(unsigned int i);
	static Textures* GetInstance();
};
