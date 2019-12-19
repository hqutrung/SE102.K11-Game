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
	Hp = 30;
	delaytime = 0;
	isAttack = true;
	isSnake = false;
	instance = this;
	disToAttack = 20;
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
	D3DXVECTOR2 dis = GetDisToPlayer();
	SetMoveDirection(dis.x < 0 ? Entity::MoveDirection::LeftToRight : Entity::MoveDirection::RightToLeft);

	Entity::SideCollision side1;
	auto player = Player::GetInstance();
	auto box = GetBody();
	box.left -= disToAttack;
	box.right += disToAttack;
	bool isCol = CollisionDetector::IsCollide(player->GetRect(), box);

	if (isCol & !isSnake)
		SetState(EnemyState::Idle);
	else
		SetState(EnemyState::Attack);

	Enemy::Update(dt);

	if (isDied)
	{
		if (delaytime <= 0) {
			SceneManager::GetInstance()->isEndScene2 = true;
			SceneManager::GetInstance()->isCompleteScene2 = true;
			return;
		}
		delaytime -= dt;
	}
}

void Jafar::OnCollision(Entity* impactor, SideCollision side, float collisionTime, float dt)
{

	if (impactor->GetType() == pWeapon)
	{
		Sound::GetInstance()->PlayFX(JAFAR_INJURED);
		Sound::GetInstance()->PlayFX(ENEMY_EXPLOSIVE);

		effect = new EffectChain(new BigItemExplosion(position));
		Grid::GetInstance()->AddEffect(effect);
		Hp--;
		if (Hp == 20) 
		{
			Sound::GetInstance()->PlayFX(JAFAR_DESTROY);
			TurnOutSnake();
		}
		else if (Hp == 0) 
		{
			Sound::GetInstance()->PlayFX(JAFAR_DESTROY);
			OnDestroy();
			isDied = true;
			delaytime = 0.5f;
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
		if (!isSnake)
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
	SetColliderTop(30);
	SetColliderBottom(-35);
	SetColliderRight(40);
	SetColliderLeft(-40);
	SetBodyBox(30, -10, 24, -35);
}

void Jafar::Spawn()
{
	SetState(EnemyState::Attack);
	Enemy::Spawn();

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
