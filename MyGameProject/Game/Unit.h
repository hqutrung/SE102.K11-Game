#include "Entity.h"
#include "Grid.h"

class Unit
{
	friend class Grid;

	Unit *prev, *next;
	Grid *grid;
	D3DXVECTOR2 pos;
	Entity* entity;
	bool active;		// active Unit is in Camera

public:

	Unit(Grid* grid, Entity* entity);
	Unit(Grid* grid, Entity* entity, int cellX, int cellY);
	virtual ~Unit();

	void Move(float x, float y);
	void Move(D3DXVECTOR3 newPos);

	Entity* GetEntity();
	void SetEntity(Entity* entity);

	bool GetActive();
	void SetActive(bool active);
};
