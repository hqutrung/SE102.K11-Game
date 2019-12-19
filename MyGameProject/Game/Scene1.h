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
	Sprites* _wish;
	D3DXVECTOR3 posWish;
	Sprites* _wish1;
	D3DXVECTOR3 posWish1;

public:
	Scene1();
	~Scene1();
	bool drawWish = false;
	bool drawWish1 = false;
	void LoadContent() override;
	void Update(float dt) override;
	void Render() override;
	int GetSceneID() override;
	void ProcessInput() override;
	void CheckCamera();
	void CheckActive();
	void CheckCollision(float dt = SPF);
	GameMap* GetGameMap() override { return map; };
	void DrawWish(float dt);
	void RenderPlayerData();
};

