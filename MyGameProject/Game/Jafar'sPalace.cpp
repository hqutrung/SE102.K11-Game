#include "Jafar'sPalace.h"
#include "SceneManager.h"
#include "Jafar.h"
#include "Apple.h"

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
	map = new GameMap(SCENE_JAFAR_PALACE, (char*)"Resources/tileset32.png", (char*)"Resources/tilemap32.txt", (char*)"Resources/gridBuiltMan2.txt", 32, 32);

	int width = Graphic::GetInstance()->GetBackBufferWidth();
	int height = Graphic::GetInstance()->GetBackBufferHeight();

	camera = new Camera(width, height);
	//camera = new Camera(318, 230);

	map->SetCamera(camera);

	// Player
	player = new Player();
	player->SetPosition(710, 306);

	// load Data
	if (SceneManager::GetInstance()->GetPreSceneID() != ID_CONTINUE_SCENE)
	{
		player->ReloadData();
	}

	player->lastposition = player->GetPosition();
	(new Unit(map->GetGrid(), player))->SetActive(true);


	camera->SetPosition(player->GetPosition());
	CheckCamera();

	data = new Data();

	ObjectPooling* pool = ObjectPooling::GetInstance();
	pool->AddApple();
	pool->AddSnakeWeapon(2);
	pool->AddFire(5);
	pool->AddJafarWeapon(50);
	srand(time(NULL));
}



void JafarPalace::Update(float dt)
{
	if (IsSpawnApple())
		SpawnApples();

	gameTime += dt;
	CheckActive();
	ProcessInput();
	CheckCollision(dt);

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

	data->Update(dt);


	// chuyen scene Rviving
	if (isTransition == true)
	{
		SceneManager::GetInstance()->LoadScene(ID_RIVIVING_SCENE);
		return;
	}

	// chuyen Scene
	if (SceneManager::GetInstance()->isEndScene2 == true)
	{
		SceneManager::GetInstance()->LoadScene(ID_COMPLETE_SCENE);
		SceneManager::GetInstance()->SetSceneLv(2);
		return;
	}
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
	return SCENE_JAFAR_PALACE;
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

bool JafarPalace::IsSpawnApple()
{
	if (Player::GetInstance()->GetApples() > 0)
		return false;
	for (size_t i = 0; i < apples.size(); i++)
		if (apples[i]->IsActived())
			return false;
	return true;
}

void JafarPalace::SpawnApples()
{
	apples.clear();
	Unit* unit;
	Apple* apple1, * apple2, * apple3, * apple4;
	if (Jafar::GetInstance()->GetDisToPlayer().x < 0)
	{
		// 7 36 104 12 12 2 0 1
		apple1 = new Apple();
		apple1->SetSpawnBox1(172, 312, 160, 324);
		unit = new Unit(Grid::GetInstance(), apple1);
		apples.push_back(apple1);
		apple2 = new Apple();
		apple2->SetSpawnBox1(184, 300, 172, 312);
		unit = new Unit(Grid::GetInstance(), apple2);
		apples.push_back(apple2);
		apple3 = new Apple();
		apple3->SetSpawnBox1(184, 324, 172, 336);
		unit = new Unit(Grid::GetInstance(), apple3);
		apples.push_back(apple3);
		apple4 = new Apple();
		apple4->SetSpawnBox1(196, 312, 184, 324);
		unit = new Unit(Grid::GetInstance(), apple4);
		apples.push_back(apple4);
	}
	else
	{
		apple1 = new Apple();
		apple1->SetSpawnBox1(172, 516, 160, 528);
		unit = new Unit(Grid::GetInstance(), apple1);
		apples.push_back(apple1);
		apple2 = new Apple();
		apple2->SetSpawnBox1(184, 504, 172, 516);
		unit = new Unit(Grid::GetInstance(), apple2);
		apples.push_back(apple2);
		apple3 = new Apple();
		apple3->SetSpawnBox1(184, 528, 172, 540);
		unit = new Unit(Grid::GetInstance(), apple3);
		apples.push_back(apple3);
		apple4 = new Apple();
		apple4->SetSpawnBox1(196, 516, 184, 528);
		unit = new Unit(Grid::GetInstance(), apple4);
		apples.push_back(apple4);
	}
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
