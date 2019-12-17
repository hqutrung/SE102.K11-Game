
#include "RevivingScene.h"
#include "SceneManager.h"

RevivingScene::RevivingScene()
{
	SceneManager::GetInstance()->GetPlayScene()->SetIsTransition(false);

	LoadContent();
}

RevivingScene::~RevivingScene()
{
}

void RevivingScene::LoadContent()
{
	auto texs = Textures::GetInstance();
	texs->Add(5000, "Resources/PlayerState/death_after.png", D3DCOLOR_XRGB(255, 0, 255));
	player = new Animation();
	player->AddFramesA(texs->GetTexture(5000), 1, 1, 3, 8, 10, 3, 10, 0.07f, D3DCOLOR_XRGB(255, 0, 255));

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
		auto sceneM = SceneManager::GetInstance();
		sceneM->LoadScene(sceneM->GetPlayScene()->GetSceneID());
		Sound::GetInstance()->PlayFX(COMING_OUT);
		return;
	}
	player->Update(dt);
	monkey->Update(dt);

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
