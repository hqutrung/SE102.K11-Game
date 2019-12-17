
#pragma once
#include "Scene.h"
#include "Textures.h"
#include "Animation.h"
#include "GameMap.h"
#include "Camera.h"
#include "Debug.h"
#include "GameMap.h"
#include "Player.h"
class ContinueScene : public Scene
{
	Sprites* backGround;
	D3DXVECTOR3	posBackGround;

public:
	ContinueScene();
	~ContinueScene();
	void LoadContent() override;
	void Update(float dt) override;
	void Render() override;
	void ProcessInput() override;
	int GetSceneID() override;
};

