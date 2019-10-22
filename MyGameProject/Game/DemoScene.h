#pragma once
#include"Scene.h"
#include"Sprites.h"
#include"Textures.h"

class DemoScene:public Scene
{
public:
	DemoScene();
	~DemoScene();
	void Update(float dt);
	void LoadContent();
	void Render() override;
private:
	

	float mTimeCounter;
};

