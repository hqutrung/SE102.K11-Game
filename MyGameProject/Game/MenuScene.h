#pragma once
#include "Scene.h"
#include "Textures.h"
#include "Animation.h"
#include "GameMap.h"
#include "Camera.h"
#include "Debug.h"
#include "GameMap.h"
#include "Player.h"
class MenuScene : public Scene
{
	Animation* start;
	Animation* play;
	Sprites* exit1;
	int x = 1;
	bool isStart=true;
	D3DXVECTOR3	posExit;

public:
	MenuScene();
	~MenuScene();
	void LoadContent() override;
	void Update(float dt) override;
	void Render() override;
	void ProcessInput() override;
	int GetSceneID() override;
};
