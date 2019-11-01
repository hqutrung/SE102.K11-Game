#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include "BoxCollider.h"

class Camera
{
public:
	Camera(int width, int height);
	static Camera* GetInstance();
	//center of camera
	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR3 pos);
	void FollowPlayer(float x, float y);
	int GetWidth();
	int GetHeight();
	bool IsCollide(BoxCollider r);
	BoxCollider GetRect();
	D3DXVECTOR3 GetPosition();
	bool IsHalfContaint(BoxCollider r);
	bool IsContaint(BoxCollider r);
	~Camera();

private:
	int             mWidth,
					mHeight;

	D3DXVECTOR3     mPosition;
	static Camera* instance;
};

