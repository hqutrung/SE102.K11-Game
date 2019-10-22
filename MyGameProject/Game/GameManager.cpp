#include "GameManager.h"
#include "Textures.h"
#include  "Sprites.h"

GameManager::GameManager(HWND hWnd, HINSTANCE hInstance)
{
	graphic = Graphic::GetInstance();
	//sceneManager = SceneManager::GetInstance();
	//keyboard = KeyBoard::GetInstance();

	graphic->Init(hWnd);
	//keyboard->InitKeyboard(hWnd, hInstance);
	//gnhpSound::GetInstance()->LoadSound(hWnd);

	//////--DEBUG
	//DataManager::SetCurrentStage(2);
	//sceneManager->LoadScene(DataManager::GetCurrentStage(), SceneManager::TransitionType::Next);

	Textures* textures = Textures::GetInstance();
	textures->Add(1, L"Resources/player.png", D3DCOLOR_XRGB(255, 163, 177));
	textures->Add(2, L"Resources/paddle.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(3, L"Resources/spartaspritesheet.png", D3DCOLOR_XRGB(255, 255, 255));

	this->hWnd = hWnd;
	this->hInstance = hInstance;
	isPause = false;
}

GameManager::~GameManager()
{
	//delete graphic;
	//graphic = NULL;
	//delete keyboard;
	//keyboard = NULL;
	//delete sceneManager;
	//sceneManager = NULL;
}

void GameManager::Update(DWORD dt)
{
	if (isPause)
		return;

	/*bool otherScene = sceneManager->GetSceneID() != DataManager::GetCurrentStage();
	bool playerDead = DataManager::IsDeath();

	if (otherScene && DataManager::GetCurrentStage() == GAMEOVER_SCENE)
		sceneManager->LoadScene(DataManager::GetCurrentStage(), SceneManager::TransitionType::ToGameOverTo);
	else if (playerDead)
		sceneManager->LoadScene(DataManager::GetCurrentStage(), SceneManager::TransitionType::Reload);
	else if (otherScene)
		sceneManager->LoadScene(DataManager::GetCurrentStage(), SceneManager::TransitionType::Next);

	if (!sceneManager->IsTransitioning())
		sceneManager->GetCurrentScene()->Update(dt);
	else
		sceneManager->UpdateTransition(dt);*/
}

void GameManager::Render()
{
	auto device = Graphic::GetInstance()->GetCurrentDirect3DDevice();
	auto spriteHandler = Graphic::GetInstance()->GetCurrentSpriteHandler();
	//auto scene = SceneManager::GetInstance()->GetCurrentScene();
	device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(200, 200, 255), 0.0f, 0);
	/*if (!SceneManager::GetInstance()->isSceneTransitioning())
	SceneManager::GetInstance()->GetCurrentScene()->Render();*/
	//RENDER
	{
		device->BeginScene();

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		//scene->Render();


		Sprites sprite(BoxCollider(), Textures::GetInstance()->GetTexture(1));

		Sprites sprite1(BoxCollider(), Textures::GetInstance()->GetTexture(2));
		
		Sprites sprite2(BoxCollider(), Textures::GetInstance()->GetTexture(3));

		D3DXVECTOR3 position = D3DXVECTOR3(SCREEN_WIDTH / 2.0f - sprite.GetWidth() / 2.0f, SCREEN_HEIGHT / 2.0f - sprite.GetHeight() / 2.0f, 0.0f);
		D3DXVECTOR3 position1 = D3DXVECTOR3(0, SCREEN_HEIGHT / 2.0f - sprite1.GetHeight() / 2.0f, 0.0f);
		D3DXVECTOR3 position2 = D3DXVECTOR3(SCREEN_WIDTH - sprite2.GetWidth(), SCREEN_HEIGHT / 2.0f - sprite2.GetHeight() / 2.0f, 0.0f);
		
		D3DXVECTOR3 position4 = D3DXVECTOR3(0 , SCREEN_HEIGHT / 2.0f, 0.0f);
		D3DXVECTOR3 position5 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 position6 = D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);

		D3DXVECTOR3 position3 = D3DXVECTOR3(sprite2.GetWidth() / 8.0f, sprite2.GetHeight() / 2.0f, 0.0f);
		BoxCollider box(position3, sprite2.GetWidth() / 4, sprite2.GetHeight());

		//sprite.NormalDraw(position5);

		//sprite.Draw(position, BoxCollider(), NULL, true);

		//sprite1.NormalDraw(position1);
		sprite2.NormalDraw(position2);

		sprite.Draw(position6, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), true);

		sprite2.Draw(position2, box, D3DCOLOR_XRGB(255, 255, 255), true);

		spriteHandler->End();

		device->EndScene();
	}
	device->Present(NULL, NULL, NULL, NULL);
}

void GameManager::ProcessInput()
{
	/*auto input = KeyBoard::GetInstance();
	KeyBoard::GetInstance()->ProcessKeyboard();
	if ((input->GetKey(DIK_LSHIFT) || input->GetKey(DIK_RSHIFT)) && input->GetKeyDown(DIK_P))
		isPause = !isPause;*/
}
