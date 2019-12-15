#include "Jafar'sPalace.h"

JafarPalace::JafarPalace()
{
	LoadContent();
}

JafarPalace::~JafarPalace()
{
}

void JafarPalace::LoadContent()
{
	auto texs = Textures::GetInstance();
	map = new GameMap(JAFAR_PALACE ,(char*)"Resources/tileset32.png", (char*)"Resources/tilemap32.txt", (char*)"Resources/gridBuiltMan2.txt", 32, 32);

	int width = Graphic::GetInstance()->GetBackBufferWidth();
	int height = Graphic::GetInstance()->GetBackBufferHeight();

	camera = new Camera(width, height);
	//camera = new Camera(318, 230);

	map->SetCamera(camera);

	// Player
	player = new Player();
	player->SetPosition(710, 350);
	player->lastposition = player->GetPosition();

	(new Unit(map->GetGrid(), player))->SetActive(true);

	camera->SetPosition(player->GetPosition());
	CheckCamera();

	data = new Data();

	ObjectPooling* pool = ObjectPooling::GetInstance();
	pool->AddApple();
	//pool->AddSkeleton(16);
	srand(time(NULL));
}

void JafarPalace::Update(float dt)
{
	gameTime += dt;
	CheckActive();
	ProcessInput();
	CheckCollision(dt);

	//chuyen scene
	if (player->GetHp() <= 0)
	{
		isTransition = true;
	}
	//
	camera->Update(dt);
	map->GetGrid()->Update(dt);

	// Camera follow player
	D3DXVECTOR3 playerPos = player->GetPosition();
	CheckCamera();

	// 
	if (playerPos.x < 25)
		player->SetPosition(25, playerPos.y);
	else if (playerPos.x > map->GetWidth() - 25)
		player->SetPosition(map->GetWidth() - 25, playerPos.y);

	//if (player->GetRect().top > map->GetHeight() + 10)
	//	player->SetState(PlayerState::Fall);


	data->Update(dt);
}

void JafarPalace::Render()
{

	map->GetGrid()->RenderBackGround();
	map->Draw();
	map->GetGrid()->Render();
	data->Render();
}

int JafarPalace::GetSceneID()
{
	return JAFAR_PALACE;
}

void JafarPalace::ProcessInput()
{
	KeyBoard* input = KeyBoard::GetInstance();
	player->HandleInput();
}

void JafarPalace::CheckCamera()
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

void JafarPalace::CheckActive()
{
	Entity::MoveDirection camDirection = player->GetVelocity().x > 0 ? Entity::LeftToRight : Entity::RightToLeft;
	map->GetGrid()->HandleActive(camera->GetRect(), camDirection);
}

void JafarPalace::CheckCollision(float dt)
{
	map->GetGrid()->HandMelee(dt);
}
