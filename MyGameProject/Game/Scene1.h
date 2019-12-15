#pragma once
#include "Scene.h"
#include "Textures.h"
#include "Animation.h"
#include "GameMap.h"
#include "Camera.h"
#include "Debug.h"
#include "GameMap.h"
#include "Player.h"
#include "Data.h"
class Scene1 : public Scene
{
	GameMap* map;
	Camera* camera;
	Player* player;
	Data* data;

public:
	Scene1();
	~Scene1();

	void LoadContent() override;
	void Update(float dt) override;
	void Render() override;
	int GetSceneID() override;
	void ProcessInput() override;
	void CheckCamera();
	void CheckActive();
	void CheckCollision(float dt = SPF);
	GameMap* GetGameMap() override { return map; };

	void RenderPlayerData();
};

