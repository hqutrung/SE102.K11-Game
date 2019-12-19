#include "SultanDungeon.h"
#include "SceneManager.h"

SultanDungeon::SultanDungeon()
{
	LoadContent();
}

SultanDungeon::~SultanDungeon()
{
	delete map;
	map = NULL;
	delete camera;
	camera = NULL;
	delete _wish;
	_wish = NULL;
	delete _wish1;
	_wish1 = NULL;
}

void SultanDungeon::LoadContent()
{
	auto texs = Textures::GetInstance();
	map = new GameMap(ID_SULTAN_DUNGEON, (char*)"Resources/Maps/1tileset.png", (char*)"Resources/Maps/1tilemap.txt", (char*)"Resources/Maps/1gridBuilt.txt", 16, 16);

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
	player->SetPosition(2100, 1000);
	(new Unit(map->GetGrid(), player))->SetActive(true);

	camera->SetPosition(player->GetPosition());
	CheckCamera();

	ObjectPooling* pool = ObjectPooling::GetInstance();
	pool->AddApple();

	data = new Data();

	pool->AddSkeleton(25);
	srand(time(NULL));

	texs->Add(111111, "Resources/Scene/deal.png", D3DCOLOR_XRGB(255, 0, 255));
	_wish = new Sprites(texs->GetTexture(111111), BoxCollider());
	posWish = D3DXVECTOR3(SCREEN_WIDTH / 2  /*-_wish->GetWidth() / 2*/, SCREEN_HEIGHT / 3, 0);

	texs->Add(111112, "Resources/Scene/moreGems.png", D3DCOLOR_XRGB(255, 0, 255));
	_wish1 = new Sprites(texs->GetTexture(111112), BoxCollider());
	posWish1 = D3DXVECTOR3(SCREEN_WIDTH / 2 /*- _wish1->GetWidth() / 2*/, SCREEN_HEIGHT / 3, 0);
}


void SultanDungeon::Update(float dt)
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
	DrawWish(dt);
	// chuyen scene Rviving
	if (isTransition == true)
	{
		SceneManager::GetInstance()->LoadScene(ID_RIVIVING_SCENE);
		return;
	}

	// chuyen Scene
	if (SceneManager::GetInstance()->isEndSultanDungeon == true)
	{
		SceneManager::GetInstance()->LoadScene(ID_COMPLETE_SCENE);
		SceneManager::GetInstance()->SetSceneLv(2);
		return;
	}
}

void SultanDungeon::Render()
{
	if (SceneManager::GetInstance()->isEndSultanDungeon == true)
		return;
	map->Draw();
	map->GetGrid()->Render();
	data->Render();
	if (drawWish == true)
		_wish->NormalDraw(posWish);
	if (drawWish1 == true)
		_wish1->NormalDraw(posWish1);
}

int SultanDungeon::GetSceneID()
{
	return ID_SULTAN_DUNGEON;
}

void SultanDungeon::ProcessInput()
{
	KeyBoard* input = KeyBoard::GetInstance();
	player->HandleInput();
}

void SultanDungeon::CheckCamera()
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

void SultanDungeon::CheckActive()
{
	Entity::MoveDirection camDirection = player->GetVelocity().x > 0 ? Entity::LeftToRight : Entity::RightToLeft;
	map->GetGrid()->HandleActive(camera->GetRect(), camDirection);
}

void SultanDungeon::CheckCollision(float dt)
{
	map->GetGrid()->HandMelee(dt);
}

void SultanDungeon::DrawWish(float dt)
{
	if (drawWish)
		posWish = D3DXVECTOR3(posWish.x - RUN_SPEED * dt, posWish.y, 0);
	if (drawWish1)
		posWish1 = D3DXVECTOR3(posWish1.x - RUN_SPEED * dt, posWish1.y, 0);
	if (posWish.x + _wish->GetWidth() < 0)
	{
		posWish = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3, 0);
		drawWish = false;
	}
	if (posWish1.x + _wish1->GetWidth() < 0)
	{
		posWish1 = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3, 0);
		drawWish1 = false;
	}
}
