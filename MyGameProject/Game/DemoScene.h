#pragma once
#include "Scene.h"
#include "Textures.h"
#include "Animation.h"
#include "GameMap.h"
#include "Camera.h"
#include "DemoObject.h"
#include "Debug.h"
#include "GameMap.h"
#include"Player.h"
class DemoScene: public Scene
{
	GameMap* map;
	Camera* camera;
	Player* player;

public:
	DemoScene();
	~DemoScene();
	void LoadContent() override;
	void Update(float dt) override;
	void Render() override;
	int GetSceneID() override;
	void ProcessInput() override;
	void CheckCamera();
	void CheckActive();
	void CheckCollision(float dt = SPF);
};

