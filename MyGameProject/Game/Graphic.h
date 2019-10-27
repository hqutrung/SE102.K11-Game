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

	////DRAW STRING ON SCREEN BRO
	//ID3DXFont* normalFont;
	//ID3DXFont* narrowFont;
	//ID3DXFont* customFont1;
	//ID3DXFont* customFont2;
	//RECT leftZone;
	//RECT rightZone;
	//RECT iconSpiritZone;
	//RECT playerHealthZone;
	//RECT enemyHealthZone;

	//std::string scoreInfor;
	//std::string timeInfor;
	//std::string lifeInfor;
	//std::string spiritInfor;
	//std::string stageInfor;
	//std::string playerHealthInfor;
	//std::string enemyHealthInfor;
	//std::string iconSpirit;
	//std::string healthIcon;
	//Tag itemTag;

public:

	/*void SetScoreInfo(int score);
	void SetTimeInfo(int time);
	void SetLifeInfo(int life);
	void SetSpiritInfo(int spirit);
	void SetstageInfo(int stage);
	void SetPlayerHealthInfo(int health);
	void SetEnemyHealthInfo(int health);
	void SetItemInfo(Tag item);*/

	//void InitFont();
	//void DrawString();

	//void DrawCustomZone(RECT r, std::string content);
	//void DrawCustomZoneSmall(RECT r, std::string content);

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