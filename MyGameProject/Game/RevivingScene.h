#pragma once
#include "Scene.h"
#include "Textures.h"
#include "Animation.h"
#include "GameMap.h"
#include "Camera.h"
#include "Debug.h"
#include "GameMap.h"
#include "Player.h"
class RevivingScene : public Scene
{
	Animation* player;
	Animation* monkey;
	D3DXVECTOR3 posPlayer;
	D3DXVECTOR3 posMonkey;

public:
	RevivingScene();
	~RevivingScene();
	void LoadContent() override;
	void Update(float dt) override;
	void Render() override;
	int GetSceneID() override;
};
