#include "PlayerJumpAttack.h"

PlayerJumpAttackState::PlayerJumpAttackState(PlayerData* data)
{
	this->playerData = data;
	auto texs = Textures::GetInstance();
	texs->Add(1029, "Resources/PlayerState/jump_attack_after.png", D3DCOLOR_XRGB(255, 0, 255));
	m_Animation = new Animation();
	m_Animation->AddFrames(texs->GetTexture(1029), 1, 7, 0.065f, D3DCOLOR_XRGB(255, 255, 255));
	heavy = true;

}

PlayerJumpAttackState::~PlayerJumpAttackState()
{
}

void PlayerJumpAttackState::Render()
{
	PlayerState::Render();
}

void PlayerJumpAttackState::Update(float dt)
{
	auto player = playerData->player->GetInstance();
	
	if (player->status == Player::Status::Jumping&&player->GetPosition().y < player->lastposition.y + MAX_JUMP)
		player->SetVy(JUMP_SPEED);
	if (player->GetPosition().y >= player->lastposition.y + MAX_JUMP)
	{
		player->status = Player::Status::Falling;
		player->SetVy(-JUMP_SPEED);
	}
	// set time cua cac frame
	if (m_Animation->GetCurrentFrameID() == 6)
		m_Animation->SetDefaultTime(0.15f);
	else m_Animation->SetDefaultTime(0.05f);

	// end frame
	if (player->status==Player::Status::OnGround)
		player->SetState(TouchGroud);

	// animation update

	if (m_Animation->IsLastFrame(dt) && player->status != Player::Status::OnGround)
		player->SetState(Fall);


	
	PlayerState::Update(dt);

	//isAttack
	if (Support::IsContainedIn(m_Animation->GetCurrentFrameID(), 3, 5))
		playerData->player->isAttack = true;
	else playerData->player->isAttack = false;

}

void PlayerJumpAttackState::HandleInput()
{
	auto player = playerData->player->GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	if (keyboard->GetKey(THROW_ARROW) && player->GetApples() > 0)
	{
		player->SetState(JumpThrow);
		return;
	}


	if (keyboard->GetKey(RIGHT_ARROW) || keyboard->GetKeyDown(RIGHT_ARROW))
	{
		player->SetVx(RUN_SPEED / 1.1f);
		return;
	}
	// Nếu ấn left-arrow thì chạy qua trái
	if (keyboard->GetKey(LEFT_ARROW) || keyboard->GetKeyDown(LEFT_ARROW))
	{
		player->SetVx(- RUN_SPEED / 1.1f);
		return;
	}
	player->SetVx(0);
}

void PlayerJumpAttackState::OnCollision(Entity* impactor, Entity::SideCollision side, float collisionTime, float dt)
{
	auto player = playerData->player;
	if (player->status == Player::Status::OnGround
		&& (impactor->GetTag() == GROUND || (impactor->GetTag() == STONE && impactor->IsCollidable())) && player->GetPrevStateName() != TouchGroud)
	{
		player->SetState(TouchGroud);
	}
}

PlayerState::State PlayerJumpAttackState::GetStateName()
{
	return JumpAttack;
}

void PlayerJumpAttackState::ResetState(int dummy)
{
	auto player = playerData->player;
//collider around center point, collider often smaller than player sprite
	player->SetColliderLeft(-22);
	player->SetColliderRight(60);
	player->SetColliderTop(46);
	player->SetColliderBottom(-24);
	PlayerState::ResetState(dummy);
}
