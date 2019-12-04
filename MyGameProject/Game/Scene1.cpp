#include "Scene1.h"

Scene1::Scene1()
{
	LoadContent();
}

Scene1::~Scene1()
{
}

void Scene1::LoadContent()
{
	map = new GameMap((char*)"Resources/tilesetnew.png", (char*)"Resources/tilemap16.txt", (char*)"Resources/gridBuilt.txt", 16, 16);

	int width = Graphic::GetInstance()->GetBackBufferWidth();
	int height = Graphic::GetInstance()->GetBackBufferHeight();


	camera = new Camera(width, height);
	camera = new Camera(318, 230);

	map->SetCamera(camera);

	// Player
	player = new Player();
	player->SetPosition(100, 65);
	player->lastposition = player->GetPosition();
	//player->SetPosition(32,32);
	(new Unit(map->GetGrid(), player))->SetActive(true);

	camera->SetPosition(player->GetPosition());
	CheckCamera();
}

void Scene1::Update(float dt)
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
	if (playerPos.x < 16)
		player->SetPosition(16, playerPos.y);
	if (playerPos.x > map->GetWidth() - 16)
		player->SetPosition(map->GetWidth() - 16, playerPos.y);

	if (playerPos.y < 16)
		player->SetPosition(playerPos.x, 16);
	if (playerPos.y > map->GetHeight() - 16)
		player->SetPosition(playerPos.x, map->GetHeight() - 16);
	//



}

void Scene1::Render()
{
	map->Draw();

	map->GetGrid()->Render();
}

int Scene1::GetSceneID()
{
	return SCENE_1;
}

void Scene1::ProcessInput()
{
	KeyBoard* input = KeyBoard::GetInstance();
	player->HandleInput();
}

void Scene1::CheckCamera()
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

void Scene1::CheckActive()
{
	Entity::MoveDirection camDirection = player->GetVelocity().x > 0 ? Entity::LeftToRight : Entity::RightToLeft;
	map->GetGrid()->HandleActive(camera->GetRect(), camDirection);
}

void Scene1::CheckCollision(float dt)
{
	map->GetGrid()->HandMelee(dt);
}