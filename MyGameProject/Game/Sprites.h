#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>

#include "Graphic.h"
#include "BoxCollider.h"
#include "Support.h"
#include "Camera.h"
#include "Debug.h"

#include <unordered_map>

class Sprites 
{

protected:
	D3DXVECTOR3 position;			// toa do cua Sprite, co goc la chinh giua hinh anh Texture
	D3DXVECTOR2 translation;		// tinh tien sprite them 1 doan bang vector(x,y)
	int width, height;				// size of texture
	BoxCollider box;
	

	LPDIRECT3DTEXTURE9 texture;			// load hinh anh vao day
	LPD3DXSPRITE spriteHandler;			// dùng để lấy device và vẽ sprite lên màn hình

	void InitWithSprite(const char* filePath, BoxCollider box = BoxCollider(), int width = NULL, int height = NULL, D3DCOLOR colorKey = NULL);
	D3DXIMAGE_INFO          mImageInfo; // thong tin thuc cua hinh anh duoc lay
	float                   mRotation; // goc quay cua Sprite tinh theo radian

	D3DXVECTOR2             mScale = D3DXVECTOR2(1, 1); // Vector tuy chinh do phong to / thu nho cua texture
	D3DXMATRIX              mMatrix; // ma tran cua Spite ho tro trong cac phep hinh hoc
	D3DXVECTOR2             mRotationCenter; // diem trung tam trong phep xoay hinh (origin vector)

public:

	Sprites(LPDIRECT3DTEXTURE9 texture, BoxCollider box);

	Sprites(const char* filePath, BoxCollider box = BoxCollider(), int width = NULL, int height = NULL, D3DCOLOR colorKey = NULL);


	~Sprites();

	int GetWidth();
	void SetWidth(int width);
	int GetHeight();
	void SetHeight(int height);

	LPDIRECT3DTEXTURE9 GetTexture();

	bool IsRect(BoxCollider r);

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), BoxCollider box = BoxCollider(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255), bool reverse = false);
	void NormalDraw(D3DXVECTOR3 position);
};
typedef Sprites* LPSPRITE;