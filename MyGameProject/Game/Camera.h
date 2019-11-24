#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "Support.h"
#include "Entity.h"

class Camera
{
	D3DXVECTOR3 position;
	float width;
	float height;
	static Camera* instance;
	bool isLookLeft, isLookRight;
	int index;
public:
	static Camera* GetInstance();
	Camera(int width, int height);
	~Camera();
	
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition();
	int GetWidth();
	int GetHeight();

	BoxCollider GetRect();

	void Update(float dt);
	//void FollowPlayer(Entity*);
	bool IsHalfContaint(BoxCollider r);
	bool IsCollide(BoxCollider r);
	bool IsContaint(BoxCollider r);

};
