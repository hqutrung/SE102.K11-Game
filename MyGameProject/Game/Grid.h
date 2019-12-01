#pragma once
#include <Windows.h>
#include "GameConfig.h"
#include "Entity.h"
#include "Support.h"

class Unit;
class Grid
{
	static Grid* instance;

	int rowNumbers, colNumbers;			// numbers of cells
	float cellWidth, cellHeight;		// Size of cell

	Unit* Cells[GRID_COLUMN_NUMBERS][GRID_ROW_NUMBERS];
	bool activeCells[GRID_COLUMN_NUMBERS][GRID_ROW_NUMBERS];
	RECT activeRect;

	//std::vector<Entity*> staticObjects;

public:
	static Grid* GetInstance();

	Grid(BoxCollider r, int rowNumbers, int colNumbers);
	~Grid();

	void Add(Unit* unit);							// Add Unit to Grid
	void Add(Unit* unit, int cellX, int cellY);

	//void AddStaticObject(Entity* ent);

	// Active Unit is in camera
	void HandleActive(BoxCollider camRect, Entity::MoveDirection camDirection);
	void HandleActiveUnit(BoxCollider camRect, Entity::MoveDirection camDirection, Unit* unit);
	void HandleInActiveUnit(Unit* unit);

	// Collision
	void HandMelee();								// partitioned the battlefield into little skirmishes
	void HandleCell(int cellX, int cellY);			// handle this cell
	void HandleUnit(Unit* unit, Unit* other);		// handle this Unit
	void HandleCollision(Entity* ent1, Entity* ent2);	// handle collision

	/*void HandleCellWithStatic(Unit* unit);
	void HandleColissionStatic(Entity* ent1, Entity* ent2);*/


	void Move(Unit* unit, float x, float y);		// Move Unit
	void MoveActiveUnit(Unit* unit);				// Move active Unit after update

	void Update(float dt);							// Update, render Grid
	void Render();

	void UpdateUnit(Unit* unit, float dt);			// Update, render 1 Unit
	void RenderUnit(Unit* unit);

	/*void AddStaticObject(Entity* ent);
	void HandleCellWithStatic(Unit *unit, double dt);*/
};