#include "Scene1.h"
#include "SceneManager.h"

Scene1::Scene1()
{
	LoadContent();
}

Scene1::~Scene1()
{
}

void Scene1::LoadContent()
{
	auto texs = Textures::GetInstance();
	map = new GameMap(SCENE_1, (char*)"Resources/tileset16.png", (char*)"Resources/tilemap16.txt", (char*)"Resources/gridBuilt.txt", 16, 16);

	int width = Graphic::GetInstance()->GetBackBufferWidth();
	int height = Graphic::GetInstance()->GetBackBufferHeight();

	camera = new Camera(width, height);
	//camera = new Camera(318, 230);

	map->SetCamera(camera);

	// Player

	player = new Player();
	player->SetPosition(100, 100);
	//player->ReloadData();
	player->lastposition = player->GetPosition();
	//player->SetPosition(2100, 1000);
	(new Unit(map->GetGrid(), player))->SetActive(true);

	camera->SetPosition(player->GetPosition());
	CheckCamera();

	ObjectPooling* pool = ObjectPooling::GetInstance();
	pool->AddApple();

	data = new Data();

	pool->AddSkeleton(20);
	srand(time(NULL));
}

void Scene1::Update(float dt)
{

	gameTime += dt;
	CheckActive();
	ProcessInput();
	CheckCollision(dt);
	camera->Update(dt);
	map->GetGrid()->Update(dt);

	// Camera follow player
	D3DXVECTOR3 playerPos = player->GetPosition();
	CheckCamera();


	if (playerPos.x < 25)
		player->SetPosition(25, playerPos.y);
	else if (playerPos.x > map->GetWidth() - 25)
		player->SetPosition(map->GetWidth() - 25, playerPos.y);

	// suface Data
	data->Update(dt);

	// chuyen scene Rviving
	if (isTransition == true)
	{
		SceneManager::GetInstance()->LoadScene(ID_RIVIVING_SCENE);
		return;
	}

	// chuyen Scene
	if (SceneManager::GetInstance()->isEndScene1 == true)
	{
		SceneManager::GetInstance()->LoadScene(ID_COMPLETE_SCENE);
		SceneManager::GetInstance()->SetSceneLv(2);
		return;
	}
}

void Scene1::Render()
{
	if (SceneManager::GetInstance()->isEndScene1 == true)
		return;
	map->Draw();
	map->GetGrid()->Render();
	data->Render();
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

