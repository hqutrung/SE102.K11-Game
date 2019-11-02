#pragma once
#include "Scene.h"
#include "Textures.h"
#include "Animation.h"
#include "GameMap.h"
#include "Camera.h"
#include "DemoObject.h"
#include "Debug.h"

class DemoScene: public Scene
{
protected:
	LPANIMATION marioAni;
	LPANIMATION spartaAni;
	float mTimeCounter;
	GameMap* map;
	Camera* camera;
	DemoObject* demoObject;

public:
	DemoScene();
	~DemoScene();
	void Update(float dt) override;
	void LoadContent() override;
	void Render() override;
	int GetSceneID() override;
	void ProcessInput() override;
	void CheckCamera();

	void CheckCamera();

};

