#include "LevelComplete.h"
#include "SceneManager.h"

LevelComplele::LevelComplele()
{
	LoadContent();
}

LevelComplele::~LevelComplele()
{
	delete title;
	title = NULL;
	delete monkey;
	monkey = NULL;
	delete player;
	player = NULL;
}

void LevelComplele::LoadContent()
{
	auto texs = Textures::GetInstance();
	texs->Add(8010, "Resources/Scene/playerLvComplete.png", D3DCOLOR_XRGB(255, 0, 255));
	player = new Animation();
	player->AddFrames(texs->GetTexture(8010), 1, 8, 0.1f, D3DCOLOR_XRGB(255, 0, 255));

	texs->Add(8011, "Resources/Scene/monkeyLvComplete.png", D3DCOLOR_XRGB(255, 0, 255));
	monkey = new Animation();
	monkey->AddFrames(texs->GetTexture(8011), 1, 8, 0.07f, D3DCOLOR_XRGB(255, 0, 255));

	texs->Add(8012, "Resources/Scene/titleLvComplete.png", D3DCOLOR_XRGB(255, 0, 255));
	title = new Sprites(texs->GetTexture(8012), BoxCollider());
	posTitle = D3DXVECTOR3(0, 0, 0);

	posPlayer = D3DXVECTOR3(SCREEN_WIDTH + monkey->GetWidthCurrentFrame() + 20, SCREEN_HEIGHT - monkey->GetHeightCurrentFrame() - 10, 0);
	posMonkey = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT - monkey->GetHeightCurrentFrame(), 0);

}

void LevelComplele::Update(float dt)
{
	auto sceneM = SceneManager::GetInstance();
	ProcessInput();
	posPlayer = D3DXVECTOR3(posPlayer.x - RUN_SPEED * dt, posPlayer.y, 0);
	posMonkey = D3DXVECTOR3(posMonkey.x - RUN_SPEED * dt, posMonkey.y, 0);
	player->Update(dt);
	monkey->Update(dt);
	if (posPlayer.x <= -player->GetWidthCurrentFrame())
		isEndScene = true;

	if (isEndScene == true)
	{
		if (sceneM->isEndScene2 == true)
		{
			exit(0);
		}
		sceneM->LoadScene(ID_INTRO_SCENE);
		return;
	}
}

void LevelComplele::Render()
{
	title->NormalDraw(posTitle);
	player->NormalRender(posPlayer);
	monkey->NormalRender(posMonkey);
}

void LevelComplele::ProcessInput()
{
	//bug
	/*auto sceneM = SceneManager::GetInstance();
	KeyBoard* keyboard = KeyBoard::GetInstance();
	if (keyboard->GetKey(PRESS_KEY) && sceneM->GetSceneLv() == 2)
	{
		isEndScene = true;
	}*/
}

int LevelComplele::GetSceneID()
{
	return ID_COMPLETE_SCENE;
}
