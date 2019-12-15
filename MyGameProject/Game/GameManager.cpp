#include "GameManager.h"
#include<time.h>

GameManager::GameManager(HWND hWnd, HINSTANCE hInstance)
{
	Graphic::GetInstance()->Init(hWnd);

	KeyBoard::GetInstance()->Init(hWnd);

	SceneManager::GetInstance()->LoadScene(ID_INTRO_SCENE);
	//SceneManager::GetInstance()->LoadScene(JAFAR_PALACE);
	//SceneManager::GetInstance()->LoadScene(SCENE_1);
	this->hWnd = hWnd;
	this->hInstance = hInstance;
	isPause = false;
	srand(time(NULL));
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

void GameManager::Update(float dt)
{
	if (isPause)
		return;
	KeyBoard::GetInstance()->KeySnapShot(dt);
	auto sceneM = SceneManager::GetInstance();

	sceneM->GetCurrentScene()->Update(dt);

}

void GameManager::Render()
{
	auto device = Graphic::GetInstance()->GetCurrentDirect3DDevice();
	auto spriteHandler = Graphic::GetInstance()->GetCurrentSpriteHandler();
	auto sceneM = SceneManager::GetInstance();
	auto scene = sceneM->GetCurrentScene();

	if (sceneM->GetSceneID() == ID_INTRO_SCENE)
		device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(102, 0, 0), 0.0f, 0);
	else 
		device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0);

	{
		device->BeginScene();

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		scene->Render();

		spriteHandler->End();

		device->EndScene();
	}

	device->Present(NULL, NULL, NULL, NULL);
}

void GameManager::ProcessInput()
{
	auto input = KeyBoard::GetInstance();
	////KeyBoard::GetInstance()->ProcessKeyboard();
	/*if ((input->GetKey(DIK_LSHIFT)))
		isDrawObjectRect = !isDrawObjectRect;*/
}
