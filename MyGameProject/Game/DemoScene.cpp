#include "DemoScene.h"
#include"Player.h"
#include"Apple.h"
DemoScene::DemoScene()
{
	LoadContent();
}

DemoScene::~DemoScene()
{
}

void DemoScene::LoadContent()
{
	map = new GameMap((char*)"Resources/tilesetnew.png", (char*)"Resources/tilemap16.txt", (char*)"Resources/gridBuilt1.txt", 16, 16);

	int width = Graphic::GetInstance()->GetBackBufferWidth();
	int height = Graphic::GetInstance()->GetBackBufferHeight();
	 

	camera = new Camera(width, height);
	//camera = new Camera(318, 230);

	map->SetCamera(camera);

	// Player
	player = new Player();
	player->SetPosition(100,65);
	player->lastposition = player->GetPosition();
	//player->SetPosition(32,32);
	(new Unit(map->GetGrid(), player))->SetActive(true);

	camera->SetPosition(player->GetPosition());
	CheckCamera();
}

void DemoScene::Update(float dt)
{
	CheckActive();
	ProcessInput(); 
	CheckCollision(dt);
	map->GetGrid()->Update(dt);
	//player->Update(dt);

	// Camera follow player
	D3DXVECTOR3 playerPos = player->GetPosition();
	camera->Update(dt);
	CheckCamera();

	// 
	if (playerPos.x < 25)
		player->SetPosition(25, playerPos.y);
	if (playerPos.x > map->GetWidth() - 25)
		player->SetPosition(map->GetWidth() - 25, playerPos.y);
	
	if (player->GetRect().top > map->GetHeight() + 10)
		player->SetState(PlayerState::Fall);
}

void DemoScene::Render()
{
	map->Draw();

	map->GetGrid()->Render();
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

void DemoScene::CheckCollision(float dt)
{
	map->GetGrid()->HandMelee(dt);
}
