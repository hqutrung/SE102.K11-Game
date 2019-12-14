#pragma once
#include "Scene.h"
#include "Textures.h"
#include "Animation.h"
#include "GameMap.h"
#include "Camera.h"
#include "Debug.h"
#include "GameMap.h"
#include "Player.h"

class LevelComplele : public Scene
{

	Sprites* title;
	Animation* monkey;
	Animation* player;

	D3DXVECTOR3 posTitle;
	D3DXVECTOR3 posPlayer;
	D3DXVECTOR3 posMonkey;


public:
	LevelComplele();
	~LevelComplele();
	void LoadContent() override;
	void Update(float dt) override;
	void Render() override;
	void ProcessInput() override;
	int GetSceneID() override;
};
