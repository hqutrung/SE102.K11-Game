#include "Camera.h"
#include "Player.h"
Camera* Camera::instance = NULL;


Camera* Camera::GetInstance()
{
	return instance;
}

Camera::Camera(int width, int height)
{
	this->width = width;
	this->height = height;
	instance = this;
	isLookLeft = false;
	isLookRight = true;
	index = INDEX_CAMERA_WIDTH - 30;
}

Camera::~Camera()
{
}

void Camera::SetPosition(D3DXVECTOR3 pos)
{
	this->position = pos;
}

D3DXVECTOR3 Camera::GetPosition()
{
	return position;
}

int Camera::GetWidth()
{
	return width;
}

int Camera::GetHeight()
{
	return height;
}

BoxCollider Camera::GetRect()
{
	BoxCollider r;
	r.top = position.y + height / 2;
	r.left = position.x - width / 2;
	r.right = r.left + width;
	r.bottom = r.top - height;
	return r;
}

void Camera::Update(float dt)
{
	auto player = Player::GetInstance();
	auto keyboard = KeyBoard::GetInstance();
	PlayerState::State currentStateName = player->GetCurrentState()->GetStateName();
	
	// Camera.X
	if (!keyboard->GetKey(LEFT_ARROW) && !keyboard->GetKey(RIGHT_ARROW))
	{
		if (isLookLeft)
			position.x -= (VELOCITY_CAMERA);
		else
			position.x += (VELOCITY_CAMERA);
	}
	else if (keyboard->GetKey(LEFT_ARROW) && !keyboard->GetKey(RIGHT_ARROW))
	{
		isLookLeft = true;
		if (index == 0)
			position.x = player->GetPosition().x;
		if (index < 0)
		{
			/*if (keyboard->GetKeyUp(LEFT_ARROW))
				position.x = player->GetPosition().x;
			else*/
				position.x -= (VELOCITY_CAMERA);
		}
	}
	else
	{
		isLookLeft = false;
		if (index == 0)
			position.x = player->GetPosition().x;
		if (index > 0)
		{
			/*if (keyboard->GetKeyUp(RIGHT_ARROW))
				position.x = player->GetPosition().x;
			else*/
				position.x += (VELOCITY_CAMERA);
		}
	}
	index = player->GetPosition().x - position.x;
	position.x = Support::Clamp(position.x, player->GetPosition().x - (INDEX_CAMERA_WIDTH - 30), player->GetPosition().x + (INDEX_CAMERA_WIDTH - 30));

	

	// Camera.Y

	switch (currentStateName)
	{
	case PlayerState::LookUp:
	{
		if (player->GetCurrentState()->GetAnimation()->GetCurrentFrameID() == 3)
		{
			if (player->GetRect().bottom - 10 > position.y - height / 2)
				position.y += 10;
			position.y = Support::Clamp(position.y, player->GetPosition().y, player->GetRect().bottom - 10 + height / 2);
		}
		break;
	}
	case PlayerState::Duck: 
	{
		if (player->GetCurrentState()->GetAnimation()->GetCurrentFrameID() == 4)
		{
			if (player->GetRect().top + 15 < position.y + height / 2)
				position.y -= 10;
			position.y = Support::Clamp(position.y, player->GetRect().top + 15 - height / 2, player->GetPosition().y);
		}
		break;
	}

	case PlayerState::DuckAttack:
	case PlayerState::DuckThrow:
		break;
	case PlayerState::Jump:
	case PlayerState::JumpCross:
	case PlayerState::JumpAttack:
	case PlayerState::JumpThrow:
	{
		position.y = player->GetPosition().y;
		break;
	}
	case PlayerState::LookUpAttack:
		if(keyboard->GetKey(UP_ARROW))
			break;
	case PlayerState::IdleThrow:
	{
		if(player->GetPrevStateName() == PlayerState::State::LookUp)
			break;
	}
	default:
	{
		if (position.y > player->GetPosition().y) {
			position.y = (position.y - 10);
			position.y = Support::Clamp(position.y, player->GetPosition().y, player->GetRect().bottom + height / 2);
		}
		else if (position.y < player->GetPosition().y)
		{
			position.y = (position.y + 10);
			position.y = Support::Clamp(position.y, player->GetRect().top - height / 2, player->GetPosition().y);
		}
		break;
	}
	}
}

bool Camera::IsCollide(BoxCollider r)
{
	BoxCollider bound = GetRect();
	if (r.right < bound.left || r.left > bound.right)
		return false;
	if (r.top < bound.bottom || r.bottom > bound.top)
		return false;
	return true;
}

bool Camera::IsHalfContaint(BoxCollider r)
{
	BoxCollider bound = GetRect();
	return ((bound.left < r.right && bound.left > r.left)
		|| (bound.right < r.right && bound.right > r.left)
		|| (bound.bottom > r.bottom&& bound.bottom < r.top)
		|| (bound.top > r.bottom&& bound.top < r.top));
}

bool Camera::IsContaint(BoxCollider r)
{
	BoxCollider bound = GetRect();
	return (bound.top >= r.top && bound.bottom <= r.bottom && bound.left <= r.left && bound.right >= r.right);
}
