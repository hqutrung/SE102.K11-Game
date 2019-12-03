#pragma once

#include "Sprites.h"

class AnimationFrame : public Sprites
{
	float time;
public:
	AnimationFrame(LPDIRECT3DTEXTURE9 texture, BoxCollider box, float time = 0.1f) : Sprites(texture, box) { this->time = time; }

	float GetTime() { return time; }
};
typedef AnimationFrame* LPANIMATION_FRAME;

class Animation {
	//DWORD lastFrameTime;
	
	float defaultTime;
	int currentFrame;
	int totalFrame;
	float currentTotalTime;
	std::vector<LPANIMATION_FRAME> frames;
	float time;
	bool startUpdate;

public:
	Animation(float defaultTime = 0.1);
	~Animation();
	int countLoopFrame = 1;
	void AddFrame(LPANIMATION_FRAME frame);
	void AddFrames(LPDIRECT3DTEXTURE9 texture, int rows, int columns, float timePerFrame = 0.1f, D3DCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	void AddFramesA(LPDIRECT3DTEXTURE9 texture, int firstRow, int firstColumn, int finalRow, int finalColumn, int rowNumber, int columnNumber, float timePerFrame = 0.1f, D3DCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));


	int GetWidthCurrentFrame();
	int GetHeightCurrentFrame();
	int GetCurrentFrameID();
	void SetCurrentFrame(int frame);
	void Render(D3DXVECTOR3 position = D3DXVECTOR3(), BoxCollider sourceRect = BoxCollider(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255), bool isReverse = false);
	void NormalRender(D3DXVECTOR3 position);
	void Update(float dt);
	void Update1(float dt);
	void ResetAnimation();
	bool IsLastFrame(float dt);
	bool IsEndFrame(int frame, float dt);
	double GetPercentTime();
	void SetDefaultTime(float x) {
		this->defaultTime = x;
	};
};
typedef Animation* LPANIMATION;


