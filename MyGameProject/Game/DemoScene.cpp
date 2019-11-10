#include "DemoScene.h"
#include"Player.h"
DemoScene::DemoScene()
{
	LoadContent();
}

DemoScene::~DemoScene()
{
}

void DemoScene::LoadContent()
{
	map = new GameMap((char*)"Resources/tileset16.png",(char*)"Resources/tilemap16.txt");

	int width = Graphic::GetInstance()->GetBackBufferWidth();
	int height = Graphic::GetInstance()->GetBackBufferHeight();

	camera = new Camera(width, height);
	camera->SetPosition(D3DXVECTOR3(width / 2, height / 2, 0));

	map->SetCamera(camera);

	// Player
	player = new Player();
	player->SetPosition(32, 30 + player->GetBigHeight() / 2.0f);
	(new Unit(map->GetGrid(), player))->SetActive(true);

	camera->FollowPlayer(player->GetPosition().x, player->GetPosition().y);
	CheckCamera();
}

void DemoScene::Update(float dt)
{
	CheckActive();
	ProcessInput(); 
	map->GetGrid()->Update(dt);
	//player->Update(dt);

	// Camera follow player
	D3DXVECTOR3 playerPos = player->GetPosition();
	camera->FollowPlayer(playerPos.x, playerPos.y);
	CheckCamera();

	// 
	if (playerPos.x < 16)
		player->SetPosition(16, playerPos.y);
	if (playerPos.x > map->GetWidth() - 16)
		player->SetPosition(map->GetWidth() - 16, playerPos.y);
	
	if (playerPos.y < 16)
		player->SetPosition(playerPos.x, 16);
	if (playerPos.y > map->GetHeight() - 16)
		player->SetPosition(playerPos.x, map->GetHeight() - 16);
}

void DemoScene::Render()
{
	map->Draw();

	map->GetGrid()->Render();

	//player->Render();
}

int DemoScene::GetSceneID()
{
	return DEMO_SCENE;
}

void DemoScene::ProcessInput()
{
	KeyBoard* input = KeyBoard::GetInstance();
	player->HandleInput();
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

void DemoScene::CheckActive()
{
	Entity::MoveDirection camDirection = player->GetVelocity().x > 0 ? Entity::LeftToRight : Entity::RightToLeft;
	map->GetGrid()->HandleActive(camera->GetRect(), camDirection);
}
