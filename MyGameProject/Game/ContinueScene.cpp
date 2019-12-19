#include "ContinueScene.h"
#include "SceneManager.h"

ContinueScene::ContinueScene()
{
	LoadContent();
}

ContinueScene::~ContinueScene()
{
}

void ContinueScene::LoadContent()
{
	posBackGround = D3DXVECTOR3(0, 0, 0);
	auto texs = Textures::GetInstance();
	texs->Add(8600, "Resources/Scene/continueScene.png", D3DCOLOR_XRGB(255, 0, 255));
	backGround = new Sprites(texs->GetTexture(8600), BoxCollider());

}

void ContinueScene::Update(float dt)
{
	ProcessInput();

}

void ContinueScene::Render()
{
	backGround->NormalDraw(posBackGround);

}

void ContinueScene::ProcessInput()
{
	auto sceneM = SceneManager::GetInstance();
	KeyBoard* keyboard = KeyBoard::GetInstance();

	if (keyboard->GetKey(RIGHT_ARROW))
	{
		if (!sceneM->isCompleteSultanDungeon)
		{
			sceneM->LoadScene(ID_SULTAN_DUNGEON);
			return;
		}

		if (!sceneM->isCompleteScene2 && sceneM->isCompleteSultanDungeon == true)
		{
			sceneM->LoadScene(SCENE_JAFAR_PALACE);
			return;
		}
	}
	else if (keyboard->GetKey(LEFT_ARROW))
		exit(0);
}

int ContinueScene::GetSceneID()
{
	return ID_CONTINUE_SCENE;
}
