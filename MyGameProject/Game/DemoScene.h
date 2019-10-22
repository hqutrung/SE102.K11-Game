#pragma once
#include"Scene.h"
#include"Sprites.h"
#include"Textures.h"

class DemoScene:public Scene
{
public:
	DemoScene();
	~DemoScene();
	void Update(float dt) override;
	void LoadContent() override;
	void Render() override;
	int GetSceneID() override;
private:
	

	float mTimeCounter;
};

