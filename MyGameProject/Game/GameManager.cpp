#include "GameManager.h"
#include "DemoScene.h"

GameManager::GameManager(HWND hWnd, HINSTANCE hInstance)
{
	Graphic::GetInstance()->Init(hWnd);

	KeyBoard::GetInstance()->InitKeyboard(hWnd, hInstance);

	SceneManager::GetInstance()->LoadScene(DEMO_SCENE);

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

void GameManager::Update(float dt)
{
	if (isPause)
		return;
	SceneManager::GetInstance()->GetCurrentScene()->Update(dt);
}

void GameManager::Render()
{
	auto device = Graphic::GetInstance()->GetCurrentDirect3DDevice();
	auto spriteHandler = Graphic::GetInstance()->GetCurrentSpriteHandler();
	auto scene = SceneManager::GetInstance()->GetCurrentScene();

	device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(200, 200, 255), 0.0f, 0);

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
	KeyBoard::GetInstance()->ProcessKeyboard();
	if ((input->GetKey(DIK_LSHIFT) || input->GetKey(DIK_RSHIFT)) && input->GetKeyDown(DIK_P))
		isPause = !isPause;
}
