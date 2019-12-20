#include "Unit.h"

Unit::Unit(Grid* grid, Entity* entity)
{
	this->grid = grid;
	this->entity = entity;
	this->pos = D3DXVECTOR2(entity->GetPosition());
	pPrev = NULL;
	pNext = NULL;
	grid->AddUnit(this);
	active = false;
}

Unit::Unit(Grid* grid, Entity* entity, int cellX, int cellY)
{
	this->grid = grid;
	this->entity = entity;
	this->pos = D3DXVECTOR2(entity->GetPosition());
	pPrev = NULL;
	pNext = NULL;
	grid->AddUnit(this, cellX, cellY);
}

Unit::~Unit()
{
	delete entity;
	entity = NULL;
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

