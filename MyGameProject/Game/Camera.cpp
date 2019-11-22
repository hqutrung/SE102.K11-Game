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
	int index;
	auto player = Player::GetInstance();
	auto keyboard = KeyBoard::GetInstance();

	PlayerState::State currentNameState = player->GetCurrentState()->GetStateName();

	if (isLookRight)
	{
		if (keyboard->GetKey(RIGHT_ARROW) && !keyboard->GetKey(LEFT_ARROW))
		{
			if (position.x > player->GetPosition().x)
				return;
			//else if (position.x < player->GetPosition().x)
			//	position.x++;
			else
				position.x = player->GetPosition().x;
				
		}
		else
		{
			if (keyboard->GetKey(LEFT_ARROW))
			{
				isLookLeft = true;
				isLookRight = false;
			}
			else
			{
				if (position.x <= player->GetPosition().x + INDEX_CAMERA_WIDTH)
					position.x++;
			}
		}
		/*if (index > 0)
		{
			position.x--;
			index--;
		}*/
	}

	if (isLookLeft)
	{
		if (keyboard->GetKey(LEFT_ARROW) && !keyboard->GetKey(RIGHT_ARROW))
		{
			if (position.x < player->GetPosition().x)
				return;
			/*else if (position.x > player->GetPosition().x)
				position.x--;*/
			else
				position.x = player->GetPosition().x;
		}
		else
		{
			if (keyboard->GetKey(RIGHT_ARROW))
			{
				isLookRight = true;
				isLookLeft = false;
			}
			else
			{
				if (position.x > player->GetPosition().x - INDEX_CAMERA_WIDTH)
					position.x--;
			}
		}
	}

	if (currentNameState == PlayerState::LookUp)
	{
		if(player->GetCurrentState()->GetAnimation()->GetCurrentFrameID() == 2)
			if (position.y < player->GetPosition().y + 30)
				position.y++;
	}
	else if (player->GetCurrentState()->GetStateName() == PlayerState::Duck)
	{
		if (position.y > player->GetPosition().y - 30)
			position.y--;
	}
	else if (currentNameState == PlayerState::Jump || currentNameState == PlayerState::JumpCross) {
		position.y += player->GetVy() * dt;
	}
	else
	{
		if (position.y > (int)player->GetPosition().y)
			position.y = (int)(position.y - 1);
		else if (position.y < (int)player->GetPosition().y)
			position.y = (int)(position.y + 1);
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
