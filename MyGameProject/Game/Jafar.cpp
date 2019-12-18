#include "Jafar.h"
#include "BigItemExplosion.h"
#include "SceneManager.h"

Jafar* Jafar::instance = NULL;

Jafar::Jafar() : Enemy()
{
	SetTag(JAFAR);
	auto textures = Textures::GetInstance();
	textures->Add(TEX_JAFAR, "Resources/Enemys/Jafar.png", D3DCOLOR_XRGB(255, 0, 255));
	jafarIdleState = new JafarIdleState(enemyData);
	jafarAttackState = new JafarAttackState(enemyData);
	snakeAttackState = new SnakeAttackState(enemyData);
	point = 0;
	Hp = 10;
	isAttack = true;
	isSnake = false;
	instance = this;
}

Jafar::~Jafar()
{
}

Jafar* Jafar::GetInstance()
{
	if (!instance)
		instance = new Jafar();
	return instance;
}

void Jafar::Update(float dt)
{
	auto player = Player::GetInstance();
	D3DXVECTOR2 dis = GetDisToPlayer();
	SetMoveDirection(dis.x < 0 ? Entity::MoveDirection::LeftToRight : Entity::MoveDirection::RightToLeft);
	Enemy::Update(dt);
	
	if (isDied)
	{
		SceneManager::GetInstance()->isEndScene2 = true;
		SceneManager::GetInstance()->isCompleteScene2 = true;
		return;
	}
}

void Jafar::OnCollision(Entity* impactor, SideCollision side, float collisionTime, float dt)
{

	Entity::SideCollision side1;

	if (impactor->GetType() == PlayerType)
	{
		auto player = (Player*)impactor;
		bool isCol = CollisionDetector::IsCollide(player->GetRect(), GetBody());

		if (isCol)
			SetState(EnemyState::Idle);
		else
			SetState(EnemyState::Attack);
	}

	if (impactor->GetType() == pWeapon)
	{
		{
			effect = new EffectChain(new BigItemExplosion(position));
			Grid::GetInstance()->AddEffect(effect);
		}
		Hp--;
		if (Hp == 5) {
			TurnOutSnake();
		}
		else if (Hp == 0) {
			OnDestroy();
			isDied = true;
		}
	}
}

void Jafar::SetState(EnemyState::eState state)
{
	if (state == EnemyState::Idle) {
		enemyData->enemyState = jafarIdleState;
		currentStateName = EnemyState::Idle;
	}
	else if (state == EnemyState::Attack) {
		if(!isSnake)
			enemyData->enemyState = jafarAttackState;
		else
			enemyData->enemyState = snakeAttackState;
		currentStateName = EnemyState::Attack;
	}
	enemyData->enemyState->ResetState();
}

void Jafar::SetSpawnBox(BoxCollider box, int direction)
{
	Enemy::SetSpawnBox(box, direction);
	/*SetColliderTop(54);
	SetColliderBottom(-25);
	SetColliderRight(34);
	SetColliderLeft(-34);*/
	//SetBodyBox(30, -34, 34, -45);
	//collider = bodyBox;
}

void Jafar::Spawn()
{
	SetState(EnemyState::Attack);
	Enemy::Spawn();

	enemyData->enemy->SetBodyBox(30, -6, 20, -35);
	collider = bodyBox;
}

void Jafar::OnDestroy()
{
	auto pos = position + D3DXVECTOR3(0, 10, 0);
	effect = new EffectChain(new JafarExplosion(pos));
	Grid::GetInstance()->AddEffect(effect);
	SetActive(false);
	//Player::GetInstance()->AddScores(GetPoint());
	//gnhpSound::GetInstance()->PlayFX(SOUND_DAMAGE);
}

void Jafar::TurnOutSnake()
{
	auto pos = position + D3DXVECTOR3(0, 10, 0);
	effect = new EffectChain(new JafarExplosion(pos));
	Grid::GetInstance()->AddEffect(effect);
	if (!isSnake)
		isSnake = true;
	SetState(EnemyState::Attack);

	auto posJafar = GetPosition();
	ObjectPooling* pool = ObjectPooling::GetInstance();
	ObjectPooling::GetInstance()->SingleInstantiate(FIRE_INDEX, (posJafar - D3DXVECTOR3(20, 15, 0)));
	ObjectPooling::GetInstance()->SingleInstantiate(FIRE_INDEX, (posJafar - D3DXVECTOR3(0, 15, 0)));
	ObjectPooling::GetInstance()->SingleInstantiate(FIRE_INDEX, (posJafar - D3DXVECTOR3(-20, 15, 0)));
}

void Jafar::FireAppear()
{
	auto pos = Player::GetInstance()->GetPosition();
	pos.x += 15;
	ObjectPooling* pool = ObjectPooling::GetInstance();
	if (ObjectPooling::GetInstance()->SingleInstantiate(FIRE_INDEX, pos - D3DXVECTOR3(20, 0, 0))) {
		// Play Sound
	}
}
