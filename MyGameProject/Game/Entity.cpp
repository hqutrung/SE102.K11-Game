#include "Entity.h"

int Entity::currentID = 0;

void Entity::onSetPosition(D3DXVECTOR3 position)
{
	this->position = position;
}

Entity::Entity()
{
	//Tag = NONE;
	id = ++currentID;
	isStatic = false;
}

Entity::~Entity()
{
}

BoxCollider Entity::GetRect()
{
	BoxCollider r;
	r.left = position.x - width / 2;
	r.top = position.y + height / 2;
	r.right = r.left + width;
	r.bottom = r.top - height;
	return r;
}

void Entity::Update(float dt)
{
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
}

void Entity::Render()
{
}

void Entity::SetStatic(bool flag)
{
	this->isStatic = flag;
	velocity = D3DXVECTOR2(0, 0);
}

int Entity::GetID()
{
	return id;
}

void Entity::SetActive(bool active)
{
	this->isActived = active;
}

bool Entity::IsActived()
{
	return isActived;
	;
}

D3DXVECTOR3 Entity::GetPosition()
{
	return position;
}

void Entity::SetPosition(D3DXVECTOR3 pos)
{
	this->position = pos;
}

void Entity::SetPosition(D3DXVECTOR2 pos)
{
	SetPosition(D3DXVECTOR3(pos));
}

void Entity::SetPosition(float x, float y)
{
	SetPosition(D3DXVECTOR3(x, y, 0));
}

void Entity::AddPosition(D3DXVECTOR3 pos)
{
	SetPosition(pos + position);
}

void Entity::AddPosition(D3DXVECTOR2 pos) 
{
	AddPosition(D3DXVECTOR3(pos));
}

void Entity::AddPosition(float x, float y) 
{
	AddPosition(D3DXVECTOR3(x, y, 0));
}

D3DXVECTOR2 Entity::GetVelocity()
{
	return velocity;
}

void Entity::SetVelocity(D3DXVECTOR2 vel)
{
	if (vel.x > 0)
		SetMoveDirection(LeftToRight);
	else
		if (vel.x < 0)
			SetMoveDirection(RightToLeft);
	velocity = vel;
}

void Entity::AddVelocity(D3DXVECTOR2 vel)
{
	velocity.x += vel.x;
	velocity.y += vel.y;
}

float Entity::GetVx() {
	return velocity.x;
}

void Entity::SetVx(float vx) {
	if (vx > 0)
		SetMoveDirection(LeftToRight);
	else
		if (vx < 0)
			SetMoveDirection(RightToLeft);
	this->velocity.x = vx;
}

void Entity::AddVx(float vx) {
	this->velocity.x += vx;
}

float Entity::GetVy() {
	return velocity.y;
}

void Entity::SetVy(float vy) {
	this->velocity.y = vy;
}

void Entity::AddVy(float vy) {
	this->velocity.y += vy;
}

float Entity::GetWidth()
{
	return width;
}

void Entity::SetWidth(int width)
{
	this->width = width;
}

float Entity::GetBigWidth()
{
	return GetWidth();
}

void Entity::SetHeight(int height) {
	this->height = height;
}

float Entity::GetHeight() {
	return height;
}

float Entity::GetBigHeight() {
	return GetHeight();
}

Entity::MoveDirection Entity::GetMoveDirection()
{
	return direction;
}

void Entity::SetMoveDirection(MoveDirection direction)
{
	this->direction = direction;
}
