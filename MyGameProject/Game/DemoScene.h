#pragma once
#include "Scene.h"
#include "Textures.h"
#include "Animation.h"

class DemoScene: public Scene
{
public:
	DemoScene();
	~DemoScene();
	void Update(float dt) override;
	void LoadContent() override;
	void Render() override;
	int GetSceneID() override;

protected:
	LPANIMATION marioAni;
	float mTimeCounter;
};

