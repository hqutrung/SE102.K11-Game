#include "Textures.h"
#include "Debug.h"

Textures* Textures::instance = NULL;

Textures::Textures()
{
}

Textures::~Textures()
{
}

void Textures::Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor)
{
	if (textures[id])
		return;

	D3DXIMAGE_INFO imageInfo;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &imageInfo);

	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile Failed: %s\n", filePath);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv = Graphic::GetInstance()->GetCurrentDirect3DDevice();
	LPDIRECT3DTEXTURE9 texture;

	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		filePath,							// Path to the image to load
		imageInfo.Width,							// Texture width
		imageInfo.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,
		&imageInfo,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}

	textures[id] = texture;

	DebugOut(L"[INFO] Texture loaded Ok: id=%d, %s \n", id, filePath);
}

bool Textures::hasContained(int id)
{
	return textures.count(id);
}

LPDIRECT3DTEXTURE9 Textures::GetTexture(unsigned int i)
{
	return textures[i];
}

Textures* Textures::GetInstance()
{
	if (instance == NULL)
		instance = new Textures();
	return instance;
}
