#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>

#include "Graphic.h"
#include "BoxCollider.h"
#include "Support.h"

#include <unordered_map>

class Sprites {
protected:
	int id; //id cua sprite 
	D3DXVECTOR3 position;			// toa do cua Sprite, co goc la chinh giua hinh anh Texture
	D3DXVECTOR2 translation;		// tinh tien sprite them 1 doan bang vector(x,y)
	int width, height;				// kich thuoc cua texture
	BoxCollider box;


	LPDIRECT3DTEXTURE9 texture;		// load hinh anh vao day
	LPD3DXSPRITE spriteHandler;			// dùng để lấy device và vẽ sprite lên màn hình

public:

	Sprites(LPDIRECT3DTEXTURE9 texture, BoxCollider box);
	~Sprites();

	int GetWidth();
	void SetWidth(int width);

	int GetHeight();
	void SetHeight(int height);

	LPDIRECT3DTEXTURE9 GetTexture();

	bool IsRect(BoxCollider r);

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), BoxCollider box = BoxCollider(), D3DCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255), bool reverse = false);
	void NormalDraw(D3DXVECTOR3 position);
};
typedef Sprites* LPSPRITE;


//// list sprites ////

//
//class ListSprites {
//	static ListSprites* instance;
//
//	std::unordered_map<int, LPSPRITE> lSprites;
//
//public:
//	void Add(int id, BoxCollider rect, LPDIRECT3DTEXTURE9 tex);
//	LPSPRITE Get(int id);
//	static ListSprites* GetInstance();
//};