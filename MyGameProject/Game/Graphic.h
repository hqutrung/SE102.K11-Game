#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "GameConfig.h"

class Graphic {
protected:
	static Graphic* instance;
	HWND hWnd;

	LPDIRECT3D9 d3d = NULL;
	LPDIRECT3DDEVICE9 d3ddv = NULL;

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;

	int bufferWidth;
	int bufferHeight;

public:

	static Graphic* GetInstance();
	void Init(HWND hWnd);
	~Graphic();

	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture);

	HWND GetCurrentHWND();
	void SetCurrentHWND(HWND hWnd);

	LPDIRECT3DDEVICE9 GetCurrentDirect3DDevice();
	void SetCurrentDirect3DDevice(LPDIRECT3DDEVICE9 d3dvv);

	LPD3DXSPRITE GetCurrentSpriteHandler();
	void SetCurrentSpriteHandler(LPD3DXSPRITE spriteHandler);

	LPDIRECT3DSURFACE9 GetBackBuffer();
	void SetBackBuffer(LPDIRECT3DSURFACE9 backBuffer);

	int GetBackBufferWidth() { return SCREEN_WIDTH; }
	int GetBackBufferHeight() { return SCREEN_HEIGHT; }

};