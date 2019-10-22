#include "GameManager.h"
#include "Textures.h"
#include  "Sprites.h"
#include "SceneManager.h"

GameManager::GameManager(HWND hWnd, HINSTANCE hInstance)
{
	graphic = Graphic::GetInstance();
	graphic->Init(hWnd);
	
	SceneManager::GetInstance()->ReplaceScene(new DemoScene());


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

	
}

void GameManager::Render()
{
	auto device = Graphic::GetInstance()->GetCurrentDirect3DDevice();
	auto spriteHandler = Graphic::GetInstance()->GetCurrentSpriteHandler();
	device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(200, 200, 255), 0.0f, 0);
	
	{
		device->BeginScene();

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		SceneManager::GetInstance()->GetCurrentScene()->Render();

		spriteHandler->End();

		device->EndScene();
	}
	device->Present(NULL, NULL, NULL, NULL);
}

void GameManager::ProcessInput()
{
	
}
