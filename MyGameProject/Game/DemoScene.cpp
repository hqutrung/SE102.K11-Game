#include "DemoScene.h"

DemoScene::DemoScene()
{
	LoadContent();
}

DemoScene::~DemoScene()
{
}

void DemoScene::LoadContent()
{
	mMap = new GameMap((char*)"Resources/testmap.tmx");
	mCamera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);


	int width = Graphic::GetInstance()->GetBackBufferWidth();
	int height = Graphic::GetInstance()->GetBackBufferHeight();

	camera = new Camera(width, height);
	camera->SetPosition(D3DXVECTOR3(width / 2, height / 2, 0));

	map->SetCamera(camera);

	demoObject = new DemoObject();
	demoObject->SetPosition(32, 30 + demoObject->GetBigHeight() / 2.0f);

	camera->FollowPlayer(demoObject->GetPosition().x, demoObject->GetPosition().y);

	CheckCamera();
}

void DemoScene::Update(float dt)
{
	ProcessInput();
	demoObject->Update(dt);

	D3DXVECTOR3 playerPos = demoObject->GetPosition();
	camera->FollowPlayer(playerPos.x, playerPos.y);
	CheckCamera();


	if (playerPos.x < 16)
		demoObject->SetPosition(16, playerPos.y);
	if (playerPos.x > map->GetWidth() - 16)
		demoObject->SetPosition(map->GetWidth() - 16, playerPos.y);
	
	if (playerPos.y < 16)
		demoObject->SetPosition(playerPos.x, 16);
	if (playerPos.y > map->GetHeight() - 16)
		demoObject->SetPosition(playerPos.x, map->GetHeight() - 16);
}

void DemoScene::Render()
{
	mMap->Draw();

	demoObject->Render();
}

int DemoScene::GetSceneID()
{
	return DEMO_SCENE;
}

void DemoScene::ProcessInput()
{
	KeyBoard* input = KeyBoard::GetInstance();
	demoObject->HandleInput();
}

void DemoScene::CheckCamera()
{
	D3DXVECTOR3 camPos = camera->GetPosition();
	float halfWidth = (float)camera->GetWidth() / 2;
	float halfHeight = (float)camera->GetHeight() / 2;
	auto worldWidth = map->GetWidth();
	auto worldHeight = map->GetHeight();
	if (camPos.x - halfWidth < 0)
		camPos.x = halfWidth;
	if (camPos.x + halfWidth > worldWidth)
		camPos.x = worldWidth - halfWidth;

	if (camPos.y - halfHeight < 0)
		camPos.y = halfHeight;
	if (camPos.y + halfHeight > worldHeight)
		camPos.y = worldHeight - halfHeight;

	camera->SetPosition(camPos);
}
