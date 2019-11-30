#include "Grid.h"
#include "Unit.h"
#include "Camera.h"
#include "CollisionDetector.h"

Grid* Grid::instance = NULL;

Grid* Grid::GetInstance()
{
	return instance;
}

Grid::Grid(BoxCollider r, int rowNumbers, int colNumbers)
{
	this->rowNumbers = rowNumbers;
	this->colNumbers = colNumbers;

	cellWidth = (float)(r.right - r.left) / colNumbers;
	cellHeight = (float)(r.top - r.bottom) / rowNumbers;

	// Clear the grid
	for (int i = 0; i < colNumbers; i++)
		for (int j = 0; j < rowNumbers; j++)
		{
			Cells[i][j] = NULL;
			activeCells[i][j] = false;
		}
	instance = this;
}

Grid::~Grid()
{
	for (int x = 0; x < colNumbers; x++)
		for (int y = 0; y < rowNumbers; y++)
			if (Cells[x][y] != NULL) {
				Unit* unit = Cells[x][y];
				Unit* other;
				while (unit != NULL) {
					other = unit->next;
					delete unit;
					unit = other;
				}
				Cells[x][y] = NULL;
			}
	for (size_t i = 0; i < staticObjects.size(); i++) {
		delete staticObjects[i];
		staticObjects[i] = NULL;
	}
}

void Grid::Add(Unit* unit)
{
	// Determine which cell it's in
	int cellX = (int)(unit->pos.x / this->cellWidth);
	int cellY = (int)(unit->pos.y / this->cellHeight);

	// Add Unit to the front of list at the cell it's in
	unit->prev = NULL;
	unit->next = Cells[cellX][cellY];
	Cells[cellX][cellY] = unit;

	if (unit->next != NULL)
		unit->next->prev = unit;
}	

void Grid::HandleActive(BoxCollider camRect, Entity::MoveDirection camDirection)
{
	// Get cellRec which contain camRect
	RECT r;
	r.left = (int)(Support::Clamp(camRect.left / cellWidth, 0, colNumbers));
	r.right = (int)(Support::Clamp(camRect.right / cellWidth, 0, colNumbers));
	r.top = (int)(Support::Clamp(camRect.top / cellWidth, 0, rowNumbers));
	r.bottom = (int)(Support::Clamp(camRect.bottom / cellWidth, 0, rowNumbers));

	// Check Active: it's in r => active

	for (int i = 0; i < colNumbers; i++)
		for (int j = 0; j < rowNumbers; j++)
		{
			if (i < r.left - 1 || i > r.right + 1 || j > r.top + 1 || j < r.bottom - 1)
			{
				activeCells[i][j] = false;
				if (Cells[i][j] != NULL)
				{
					if (Cells[i][j]->entity->IsActived())
					{
						HandleInActiveUnit(Cells[i][j]);
					
						//Cells[i][j]->Move(Cells[i][j]->entity->GetPosition());
					}
				}
			}
			else
			{
				activeCells[i][j] = true;
				if (Cells[i][j] != NULL)
					HandleActiveUnit(camRect, camDirection, Cells[i][j]);
			}
		}


}

void Grid::HandleActiveUnit(BoxCollider camRect, Entity::MoveDirection camDirection, Unit* unit)
{
	Unit* other = unit;
	
	while (other != NULL)
	{
		other->active = true;

		// Set active entity
		other->entity->SetActive(true);

		other = other->next;	
	}

}

void Grid::HandleInActiveUnit(Unit* unit)
{
	Unit* other = unit;
	while (other != NULL) {
		unit = other;
		other = unit->next;
		unit->active = false;
		if (unit->entity->GetTag() != Tag::PLAYER)
			//maybe unit value of this unit pointer delete
			unit->entity->SetActive(false);
	}
}



void Grid::HandleMelee(Entity* ent1, Entity* ent2, double dt)
{
	Entity::SideCollision side;

	float collisionTime = 2;

	if (ent1->GetTag() == PLAYER || ent2->GetTag() == PLAYER)
		ent1 = ent1;

	if (!ent1->isStatic) {
		collisionTime = CollisionDetector::SweptAABB(ent1, ent2, side, dt);
		if (collisionTime == 2)
			return;
		ent1->OnCollision(ent2, side, collisionTime, dt);
	}
	if (!ent2->isStatic) {
		collisionTime = CollisionDetector::SweptAABB(ent2, ent1, side, dt);
		ent2->OnCollision(ent1, side, collisionTime, dt);
	}
}

void Grid::	HandleCell(int x, int y, RECT r, double dt)

{
	//if (!Cells[cellX][cellY]->active)
	//	return;

	//Unit* unit = Cells[cellX][cellY];

	//while (unit != NULL)
	//{
	//	if (unit->entity->IsActived())
	//	{
	//		// Handle other units in this cell
	//		HandleUnit(unit, unit->next);

	//		// Handle the neighbor cells
	//		if (cellX > 0 && cellY > 0)
	//			HandleUnit(unit, Cells[cellX - 1][cellY - 1]);
	//		if (cellX > 0)
	//			HandleUnit(unit, Cells[cellX - 1][cellY]);
	//		if (cellY > 0)
	//			HandleUnit(unit, Cells[cellX][cellY - 1]);
	//		if (cellX > 0 && cellY < cellHeight)
	//			HandleUnit(unit, Cells[cellX - 1][cellY + 1]);
	//	}
	//	unit = unit->next;
	//}
	if (!Cells[x][y]->active)
		return;

	Unit* unit = Cells[x][y];

	while (unit != NULL) {
		if (unit->entity->IsActived()) {
			HandleUnit(unit, unit->next, dt);

			if (x > 0 && y > 0) HandleUnit(unit, Cells[x - 1][y - 1], dt);
			if (x > 0) HandleUnit(unit, Cells[x - 1][y], dt);
			if (y < rowNumbers - 1) HandleUnit(unit, Cells[x][y + 1], dt);
			if (x > 0 && y < rowNumbers - 1)
				HandleUnit(unit, Cells[x - 1][y + 1], dt);
		}
		unit = unit->next;
	}

}

void Grid::HandleUnit(Unit* unit, Unit* other, double dt)
{
	while (other != NULL)
	{
		if (other->entity->IsActived())
			{
			HandleMelee(unit->entity, other->entity, dt);
			}
		other = other->next;
	}
}

void Grid::HandleCollision(double dt)
{
	for (int x = 0; x < colNumbers; x++)
		for (int y = 0; y < rowNumbers; y++)
			if (Cells[x][y] != NULL && activeCells[x][y] == true) {

				HandleCellWithStatic(Cells[x][y], dt);
			}

	//CHECK COLLISION
	for (int x = 0; x < colNumbers; x++)
		for (int y = 0; y < rowNumbers; y++)
			if (Cells[x][y] != NULL && activeCells[x][y] == true)
				HandleCell(x, y, activeRect, dt);
}

void Grid::HandleCollideStatic(Entity* ent1, Entity* ent2, double dt)
{
	//ent2's always static
	Entity::SideCollision side;

	BoxCollider rectEnt1 = ent1->GetRect();
	if (ent1->GetType() == Layer::PlayerType)
		rectEnt1 = BoxCollider(ent1->GetPosition(), ent1->GetWidth(), ent1->GetBigHeight());

	auto impactorRect = ent2->GetRect();

	float groundTime = CollisionDetector::SweptAABB(rectEnt1, ent1->GetVelocity(), impactorRect, D3DXVECTOR2(0, 0), side, dt);

	ent1->OnCollision(ent2, side, groundTime, dt);
}

void Grid::HandleCellWithStatic(Unit* unit, double dt)
{
	while (unit != NULL) {
		if (unit->entity->IsActived()) {
			for (size_t i = 0; i < staticObjects.size(); i++)
				HandleCollideStatic(unit->entity, staticObjects[i], dt);
		}
		unit = unit->next;
	}
}


void Grid::Move(Unit* unit, float x, float y)
{
	// old cell
	int oldCellX = (int)(unit->pos.x / cellWidth);
	int oldCellY = (int)(unit->pos.y / cellHeight);

	// new cell
	int cellX = (int)(x / cellWidth);
	int cellY = (int)(y / cellHeight);

	//Out of screen
	if (cellX >= colNumbers || cellX < 0 || cellY >= rowNumbers || cellY < 0) {
		unit->entity->SetActive(false);
		return;
	}

	// update unit's position
	unit->pos.x = x;
	unit->pos.y = y;

	// if didn't change cell
	if (cellX == oldCellX && cellY == oldCellY)
		return;

	// Unlink it from the list of its old cell.
	if(unit->prev != NULL)
		unit->prev->next = unit->next;
	if (unit->next != NULL)
		unit->next->prev = unit->prev;

	// If it's the head of a list, remove it.
	if (Cells[oldCellX][oldCellY] == unit)
		Cells[oldCellX][oldCellY] = unit->next;

	// Add it to the grid at new cell.
	Add(unit);
}

void Grid::MoveActiveUnit(Unit* unit)
{
	Unit* other = unit;
	while (other != NULL)
	{
		unit = other;
		unit->Move(unit->entity->GetPosition());
		other = other->next;
	}
}

void Grid::Update(float dt)
{
	// Update entity
	for (int i = 0; i < colNumbers; i++)
		for (int j = 0; j < rowNumbers; j++)
			if ((Cells[i][j] != NULL && activeCells[i][j] == true))
				UpdateUnit(Cells[i][j], dt);

	// Update Unit
	for (int i = 0; i < colNumbers; i++)
		for (int j = 0; j < rowNumbers; j++)
			if ((Cells[i][j] != NULL && activeCells[i][j] == true))
				MoveActiveUnit(Cells[i][j]);
}

void Grid::Render()
{
	for (int i = 0; i < colNumbers; i++)
		for (int j = 0; j < rowNumbers; j++)
			if ((Cells[i][j] != NULL && activeCells[i][j] == true))
				RenderUnit(Cells[i][j]);
}

void Grid::UpdateUnit(Unit* unit, float dt)
{
	while (unit != NULL) 
	{
		if (unit->entity->IsActived())
		{
			unit->entity->Update(dt);
		}
		unit = unit->next;
	}
}

void Grid::RenderUnit(Unit* unit)
{
	while (unit != NULL) 
	{
		if (unit->entity->IsActived())
		{
			Camera* cam = Camera::GetInstance();
			//if(cam->IsCollide(unit->entity->GetRect()))
				unit->entity->Render();
		}
		unit = unit->next;
	}
}
void Grid::AddStaticObject(Entity* ent) {
	staticObjects.push_back(ent);
}