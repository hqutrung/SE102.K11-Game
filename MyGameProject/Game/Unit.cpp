#include "Unit.h"

Unit::Unit(Grid* grid, Entity* entity)
{
	this->grid = grid;
	this->entity = entity;
	this->pos = D3DXVECTOR2(entity->GetPosition());
	prev = NULL;
	next = NULL;
	grid->Add(this);
	
}

Unit::~Unit()
{
}

void Unit::Move(float x, float y)
{
	grid->Move(this, x, y);
}

void Unit::Move(D3DXVECTOR3 newPos)
{
	Move(newPos.x, newPos.y);
}

Entity* Unit::GetEntity()
{
	return entity;
}

void Unit::SetEntity(Entity* entity)
{
	this->entity = entity;
}

bool Unit::GetActive()
{
	return active;
}

void Unit::SetActive(bool active)
{
	this->active = active;
}

