#include "Camera.h"


Camera* Camera::instance = NULL;

Camera* Camera::GetInstance() {
	return instance;
}

Camera::Camera(int width, int height)
{
	this->mWidth = width;
	this->mHeight = height;

	this->mPosition = D3DXVECTOR3(0, 0, 0);
	instance = this;
}


Camera::~Camera()
{

}
bool Camera::IsCollide(BoxCollider r) {
	BoxCollider bound = GetRect();
	if (r.right < bound.left || r.left > bound.right)
		return false;
	if (r.top < bound.bottom || r.bottom > bound.top)
		return false;
	return true;
}

bool Camera::IsContaint(BoxCollider r) {
	BoxCollider bound = GetRect();
	return (bound.top >= r.top && bound.bottom <= r.bottom && bound.left <= r.left && bound.right >= r.right);
}


bool Camera::IsHalfContaint(BoxCollider r) {
	BoxCollider bound = GetRect();
	return ((bound.left < r.right && bound.left > r.left) || (bound.right < r.right && bound.right > r.left) || (bound.bottom > r.bottom && bound.bottom < r.top) || (bound.top > r.bottom && bound.top < r.top));
}

BoxCollider Camera::GetRect() {
	BoxCollider r;
	r.top = mPosition.y + mHeight / 2;
	r.left = mPosition.x - mWidth / 2;
	r.bottom = r.top - mHeight;
	r.right = r.left + mWidth;
	return r;
}
void Camera::SetPosition(float x, float y)
{
	SetPosition(D3DXVECTOR3(x, y, 0));
}

void Camera::SetPosition(D3DXVECTOR3 pos)
{
	mPosition = pos;
}

D3DXVECTOR3 Camera::GetPosition()
{
	return mPosition;
}


int Camera::GetWidth()
{
	return mWidth;
}

int Camera::GetHeight()
{
	return mHeight;
}

void Camera::FollowPlayer(float x, float y) {
	mPosition.x = x;
	mPosition.y = y;
}
