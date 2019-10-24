#pragma once
#include "Scene.h"
#include "Textures.h"
#include "Animation.h"
#include "GameMap.h"

class DemoScene: public Scene
{
protected:
	LPANIMATION marioAni;
	LPANIMATION spartaAni;
	float mTimeCounter;
	GameMap* map;

public:
	DemoScene();
	~DemoScene();
	void Update(float dt) override;
	void LoadContent() override;
	void Render() override;
	int GetSceneID() override;

};

