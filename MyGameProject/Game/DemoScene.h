#pragma once
#include "Scene.h"
#include "Textures.h"
#include "Animation.h"
#include "DemoObject.h"

class DemoScene: public Scene
{
protected:
	LPANIMATION marioAni;
	LPANIMATION spartaAni;
	float mTimeCounter;
	DemoObject* demoObject;

public:
	DemoScene();
	~DemoScene();
	void Update(float dt) override;
	void LoadContent() override;
	void Render() override;
	int GetSceneID() override;
	void ProcessInput() override;

};

