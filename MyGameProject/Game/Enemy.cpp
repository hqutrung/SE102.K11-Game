#include "Enemy.h"

Enemy::Enemy() : Entity() {
	SetType(EnemyType);
	SetStatic(false);
	isDied = false;
	auto textures = Textures::GetInstance();
	textures->Add(TEX_ENEMY, "Resources/Enemys/Enemy.png", D3DCOLOR_XRGB(255, 0, 255));
	enemyData = new EnemyData();
	enemyData->enemy = this;
	//currentStateName = EnemyState::Idle;
}

Enemy::~Enemy()
{

}

void Enemy::Update(float dt)
{
	if (!isActived)
		return;
	enemyData->enemyState->Update(dt);
	Entity::Update(dt);
	disToPlayer = D3DXVECTOR2(this->GetPosition() - Player::GetInstance()->GetPosition());
}

void Enemy::Render()
{
	if (isActived)
		enemyData->enemyState->Render();
}

void Enemy::SetSpawnBox(BoxCollider box, int direction)
{
	spawnBox = box;
	spawnPosition = D3DXVECTOR3(box.getCenter());
	spawnDirection = (MoveDirection)direction;
	SetColliderTop((spawnBox.top - spawnBox.bottom) / 2);
	SetColliderLeft((spawnBox.left - spawnBox.right) / 2);
	SetColliderBottom(-collider.top);
	SetColliderRight(-collider.left);
	MakeInactive();
}

void Enemy::SetBodyBox(float t, float l, float r, float b)
{
	bodyBox = BoxCollider(t, l, r, b);
}

BoxCollider Enemy::GetRect()
{
	BoxCollider r;
	r.top = position.y + collider.top;
	r.bottom = position.y + collider.bottom;

	if (direction == Entity::LeftToRight) {
		r.left = position.x + collider.left;
		r.right = position.x + collider.right;
	}
	else {
		r.left = position.x - collider.right;
		r.right = position.x - collider.left;
	}
	return r;
}

BoxCollider Enemy::GetSpawnBox()
{
	return spawnBox;
}

Entity::MoveDirection Enemy::GetSpawnDirection()
{
	return spawnDirection;
}

BoxCollider Enemy::GetBody()
{
	if (GetMoveDirection() == LeftToRight)
		return BoxCollider(position.y + bodyBox.top, position.x + bodyBox.left, position.x + bodyBox.right, position.y + bodyBox.bottom);
	else
		return BoxCollider(position.y + bodyBox.top, position.x - bodyBox.right, position.x - bodyBox.left, position.y + bodyBox.bottom);
}

void Enemy::SetState(EnemyState::eState state)
{
}

void Enemy::SetRect(BoxCollider box)
{
	collider = box;
}

float Enemy::GetWidth()
{
	return collider.right - collider.left;
}

float Enemy::GetBigWidth()
{
	return width;
}

float Enemy::GetHeight()
{
	return collider.top - collider.bottom;
}

float Enemy::GetBigHeight()
{
	return height;
}

void Enemy::SetActive(bool active)
{
	if (isActived == active)
		return;

	if (active)
		Spawn();
	else
		MakeInactive();
}

void Enemy::MakeInactive()
{
	isActived = false;
	position = spawnPosition;
	direction = spawnDirection;
}

void Enemy::Spawn()
{
	isActived = true;
	position = spawnPosition;
	disToPlayer = D3DXVECTOR2(this->GetPosition() - Player::GetInstance()->GetPosition());
}

void Enemy::OnDestroy()
{
	isDied = true;
	effect = new EffectChain(new EnemyExplosion(position));
	Grid::GetInstance()->AddEffect(effect);
	SetActive(false);
	Player::GetInstance()->AddScores(GetPoint());
	//gnhpSound::GetInstance()->PlayFX(SOUND_DAMAGE);
	//return EarnedData(point);
}

void Enemy::OnCollision(Entity* impactor, SideCollision side, float collisionTime, float dt)
{
	Entity::SideCollision side1;

	if (impactor->GetType() == PlayerType)
	{
		auto player = (Player*)impactor;
		//ktra Body cua enemy && rectAttack cua player   co va cham?
		bool isCol = CollisionDetector::IsCollide(player->GetRect(), GetBody());
		//enemy trong trang thai Attack && va cham vs RectBody cua player
		bool x = player->isAttack && isCol;

		if (x)
		{
			if (GetCurrentStateName() != EnemyState::Injured)
				Hp--;
			if (Hp == 0)
				OnDestroy();
			else
				SetState(EnemyState::Injured);
		}
	}

	if (impactor->GetType() == pWeapon)
	{
		//if (GetCurrentStateName() != EnemyState::Injured)
			Hp--;
		if (Hp == 0)
			OnDestroy();
		else
			SetState(EnemyState::Injured);
	}
}
