#include "IntroScene.h"
#include "SceneManager.h"

IntroScene::IntroScene()
{
	LoadContent();
}

IntroScene::~IntroScene()
{
	delete intro;
	intro = NULL;
	delete titleJafar;
	titleJafar = NULL;
	delete introJafar;
	introJafar = NULL;
	delete a;
	a = NULL;
}

void IntroScene::LoadContent()
{
	auto texs = Textures::GetInstance();
	intro = new Animation();
	texs->Add(5550, "Resources/Scene/intro2.png", D3DCOLOR_XRGB(255, 0, 255));
	intro->AddFramesA(texs->GetTexture(5550), 1, 1, 2, 8, 8, 2, 8, 0.08f);

	introJafar = new Animation();
	texs->Add(5551, "Resources/Scene/intro_jafar.png", D3DCOLOR_XRGB(255, 0, 255));
	introJafar->AddFrames(texs->GetTexture(5551), 1, 3, 0.08f);

	a = new Animation();
	texs->Add(55599, "Resources/Scene/superintro.png", D3DCOLOR_XRGB(255, 0, 255));
	a->AddFramesA(texs->GetTexture(55599), 1, 1, 3, 10, 10, 3, 10, 0.05f);

	texs->Add(5552, "Resources/Scene/title_jafar.png", D3DCOLOR_XRGB(255, 0, 255));
	titleJafar = new Sprites(texs->GetTexture(5552), BoxCollider());

	posTitleJafarPalace = D3DXVECTOR3(16, 161, 0);
}

void IntroScene::Update(float dt)
{
	ProcessInput();
	if (isA == true)
	{
		if (a->IsLastFrame(dt))
		{
			isA = false;
			Sound::GetInstance()->PlayMusic(INTRO);
		}
		a->Update(dt);
	}
	else {
		auto sceneM = SceneManager::GetInstance();
		


		if (intro->IsEndFrame(13, dt))
		{
			if (intro->countLoopFrame <= 5)
			{
				intro->SetCurrentFrame(0);
				intro->countLoopFrame++;
			}
			else
				if (sceneM->GetSceneLv() == 2)
					intro = introJafar;
		}

		intro->Update(dt);

		if (intro->IsLastFrame(dt))
		{
			isEndScene = true;
		}



		if (isEndScene == true)
		{
			if (sceneM->GetSceneLv() == 1)
			{
				sceneM->LoadScene(ID_SULTAN_DUNGEON);
				return;
			}
			else if (sceneM->GetSceneLv() == 2)
			{
				sceneM->LoadScene(SCENE_JAFAR_PALACE);
				return;
			}
		}
	}
}

void IntroScene::Render()
{
	if (isA == true)
	{
		a->NormalRender(D3DXVECTOR3(0, 0, 0));
	}
	else {
		auto sceneM = SceneManager::GetInstance();
		intro->NormalRender(D3DXVECTOR3(0, 0, 0));
		if (sceneM->GetSceneLv() == 2)
		{
			if (intro != introJafar)
				titleJafar->NormalDraw(posTitleJafarPalace);
		}
	}
}
void IntroScene::ProcessInput()
{
	auto sceneM = SceneManager::GetInstance();
	KeyBoard* keyboard = KeyBoard::GetInstance();
	if (isA == true)
	{
		if (keyboard->GetKeyDown(PRESS_KEY))
		{
			isA = false;
			Sound::GetInstance()->PlayMusic(INTRO);
		}
	}
	else
	{
		if (keyboard->GetKeyDown(PRESS_KEY))
		{
			isEndScene = true;
		}
	}
}

int IntroScene::GetSceneID()
{
	return ID_INTRO_SCENE;
}
