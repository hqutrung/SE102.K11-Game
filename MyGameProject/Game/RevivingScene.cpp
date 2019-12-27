
#include "RevivingScene.h"
#include "SceneManager.h"

RevivingScene::RevivingScene()
{
	SceneManager::GetInstance()->GetPlayScene()->SetIsTransition(false);

	LoadContent();
}

RevivingScene::~RevivingScene()
{
	delete monkey;
	monkey = NULL;
	delete player;
	player = NULL;
}

void RevivingScene::LoadContent()
{
	auto texs = Textures::GetInstance();
	texs->Add(5000, "Resources/PlayerState/death_after.png", D3DCOLOR_XRGB(255, 0, 255));
	player = new Animation();
	player->AddFramesA(texs->GetTexture(5000), 1, 1, 3, 8, 10, 3, 10, 0.11f, D3DCOLOR_XRGB(255, 0, 255));

	texs->Add(5001, "Resources/Monkey/monkey.png", D3DCOLOR_XRGB(255, 0, 255));
	monkey = new Animation();
	monkey->AddFrames(texs->GetTexture(5001), 1, 6, 0.07f, D3DCOLOR_XRGB(255, 0, 255));


	posPlayer = D3DXVECTOR3(SCREEN_WIDTH / 2 - player->GetWidthCurrentFrame() / 2, SCREEN_HEIGHT / 2 - player->GetWidthCurrentFrame() / 2, 0);
	posMonkey = D3DXVECTOR3(posPlayer.x + 60, posPlayer.y + 40, 0);

}

void RevivingScene::Update(float dt)
{

	if (player->IsLastFrame(dt))
	{
		if (player->countLoopFrame >= 70)
			isEndScene = true;
		else player->countLoopFrame++;
	}
	else player->Update(dt);
	monkey->Update(dt);
	
	if (player->GetCurrentFrameID() == 15)
	{
		Sound::GetInstance()->PlayFX(REVIVING);
	}

	if (isEndScene)
	{
		auto sceneM = SceneManager::GetInstance();
		auto player = Player::GetInstance();
		if (player->isDied)
		{
			sceneM->LoadScene(ID_CONTINUE_SCENE);
			return;
		}
		if (player->posRevival != sceneM->GetStartPos())
			Sound::GetInstance()->PlayFX(COMING_OUT);
		sceneM->LoadScene(sceneM->GetPlayScene()->GetSceneID());
		return;
	}

}

void RevivingScene::Render()
{

	player->NormalRender(posPlayer);
	monkey->NormalRender(posMonkey);
}

int RevivingScene::GetSceneID()
{
	return ID_RIVIVING_SCENE;
}
