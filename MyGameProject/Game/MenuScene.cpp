#include "MenuScene.h"
#include "SceneManager.h"

MenuScene::MenuScene()
{
	LoadContent();
}

MenuScene::~MenuScene()
{
}

void MenuScene::LoadContent()
{
	auto texs = Textures::GetInstance();

	play = new Animation();
	texs->Add(5580, "Resources/Scene/menu.png", D3DCOLOR_XRGB(255, 0, 255));
	play->AddFramesA(texs->GetTexture(5580), 1, 1, 2, 8, 8, 2, 8, 0.05f);

	start = new Animation();
	texs->Add(5583, "Resources/Scene/start.png", D3DCOLOR_XRGB(255, 0, 255));
	start->AddFramesA(texs->GetTexture(5583), 1, 1, 4, 10, 10, 4, 10, 0.032f);


	texs->Add(5581, "Resources/Scene/exitText.png", D3DCOLOR_XRGB(255, 0, 255));
	exit1 = new Sprites(texs->GetTexture(5581), BoxCollider());

	posExit = D3DXVECTOR3(113, 151, 0);
}

void MenuScene::Update(float dt)
{
	if (isStart == true)
	{
		if (start->GetCurrentFrameID() == 2)
			Sound::GetInstance()->PlayFX(GUN);
		if (start->GetCurrentFrameID() == 16)
			Sound::GetInstance()->PlayFX(LAGO);
		if (start->GetCurrentFrameID() >= 34) start->SetDefaultTime(0.1f);
		if (start->IsLastFrame(dt))
			start->SetCurrentFrame(34);
		if (KeyBoard::GetInstance()->GetKeyDown(DIK_RETURN))
		{
			isStart = false;
			Sound::GetInstance()->PlayMusic(MENU);
		}
		start->Update(dt);
	}
	else {
		ProcessInput();
		if (play->IsLastFrame(dt))
			play->SetCurrentFrame(8);
		else 	if (play->IsEndFrame(7, dt))
			play->SetCurrentFrame(0);
		play->Update(dt);
	}
}

void MenuScene::Render()
{
	if (isStart == true)
		start->NormalRender(D3DXVECTOR3(0, 0, 0));
	else
	{
		play->NormalRender(D3DXVECTOR3(0, 0, 0));
		exit1->NormalDraw(posExit);
	}
}

void MenuScene::ProcessInput()
{
	auto k = KeyBoard::GetInstance();
	if (k->GetKeyDown(DOWN_ARROW))
	{
		Sound::GetInstance()->PlayFX(MENUCHANGE);
		if (x == 1)
		{
			play->SetCurrentFrame(8);
			x = 2;
		}
	}
	if (k->GetKeyDown(UP_ARROW))
	{
		Sound::GetInstance()->PlayFX(MENUCHANGE);
		if (x == 2)
		{
			play->SetCurrentFrame(0);
			x = 1;
		}
	}
	if (k->GetKeyDown(DIK_RETURN))
	{
		Sound::GetInstance()->PlayFX(MENUSELECT);
		if (play->GetCurrentFrameID() <= 7)
		{
			SceneManager::GetInstance()->LoadScene(ID_INTRO_SCENE);
		}
		else exit(0);
	}

}

int MenuScene::GetSceneID()
{
	return ID_MENU_SCENE;
}
