#include "IntroScene.h"
#include "SceneManager.h"

IntroScene::IntroScene()
{
	time = 0;
	LoadContent();
}

IntroScene::~IntroScene()
{
}

void IntroScene::LoadContent()
{
	auto texs = Textures::GetInstance();
	texs->Add(5500, "Resources/Scene/title.png", D3DCOLOR_XRGB(255, 0, 255));
	title = new Sprites(texs->GetTexture(5500), BoxCollider());
	posTitle = D3DXVECTOR3(50, 35, 0);

	//texs->Add(5501, "Resources/Scene/title.png", D3DCOLOR_XRGB(255, 0, 255));
	//title = new Sprites(texs->GetTexture(5500), BoxCollider());

}

void IntroScene::Update(float dt)
{
	ProcessInput();
	auto sceneM = SceneManager::GetInstance();
	if (time >= 10.0f && sceneM->GetSceneLv() == 1)
	{
		sceneM->LoadScene(SCENE_1);
		//.... text scene1
	}
	time += dt;
}

void IntroScene::Render()
{
	title->NormalDraw(posTitle);
}

void IntroScene::ProcessInput()
{
	auto sceneM = SceneManager::GetInstance();
	KeyBoard* keyboard = KeyBoard::GetInstance();
	if (keyboard->GetKey(PRESS_KEY) && sceneM->GetSceneLv() == 1)
	{
		sceneM->LoadScene(SCENE_1);
		//.... text scene1
	}
}

int IntroScene::GetSceneID()
{
	return ID_INTRO_SCENE;
}
