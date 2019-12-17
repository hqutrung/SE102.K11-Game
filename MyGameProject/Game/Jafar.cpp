#include "Jafar.h"
#include "BigItemExplosion.h"
#include "SceneManager.h"

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
}

Jafar::~Jafar()
{
}

void Jafar::Update(float dt)
{
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
	if (impactor->GetType() == pWeapon)
	{
		{
			effect = new EffectChain(new BigItemExplosion(position));
			Grid::GetInstance()->AddEffect(effect);
		}
		Hp--;
		if (Hp == 5) {
			isSnake =  true;
			OnDestroy();
			SetState(EnemyState::Attack);
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
	SetColliderTop(54);
	SetColliderBottom(-25);
	SetColliderRight(34);
	SetColliderLeft(-34);
}

void Jafar::Spawn()
{
	SetState(EnemyState::Idle);
	Enemy::Spawn();

	enemyData->enemy->SetBodyBox(51, -18, 34, -25);
	collider = bodyBox;
}

void Jafar::OnDestroy()
{
	effect = new EffectChain(new EnemyExplosion(position));
	Grid::GetInstance()->AddEffect(effect);
	//SetActive(false);
	//Player::GetInstance()->AddScores(GetPoint());
	//gnhpSound::GetInstance()->PlayFX(SOUND_DAMAGE);
}

void Jafar::TurnOutSnake()
{
	auto pos = GetPosition();
	if (!isSnake) {
		Sound::GetInstance()->PlayFX(SKELETON_EXPLOSIVE);
		ObjectPooling* pool = ObjectPooling::GetInstance();

		if (ObjectPooling::GetInstance()->Instantiate(SKELETON_WEAPON_INDEX, pos)) {
			//gnhpSound::GetInstance()->PlayFX(SOUND_THROWSHURIKEN);
		}
	}
}
