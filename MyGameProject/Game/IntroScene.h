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
	Animation* intro;
	Animation* introJafar;

	Sprites* titleJafar;
	D3DXVECTOR3	posTitleJafarPalace;

public:
	IntroScene();
	~IntroScene();
	void LoadContent() override;
	void Update(float dt) override;
	void Render() override;
	void ProcessInput() override;
	int GetSceneID() override;
};
