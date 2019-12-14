#pragma once
#include "Scene.h"
#include "Textures.h"
#include "Animation.h"
#include "GameMap.h"
#include "Camera.h"
#include "Debug.h"
#include "GameMap.h"
#include "Player.h"
class IntroScene : public Scene
{

	Sprites* title;
	Sprites* a;


	D3DXVECTOR3 posTitle;
	D3DXVECTOR3 posA;

	float time ;

public:
	IntroScene();
	~IntroScene();
	void LoadContent() override;
	void Update(float dt) override;
	void Render() override;
	void ProcessInput() override;
	int GetSceneID() override;
};
