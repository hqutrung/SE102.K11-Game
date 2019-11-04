#include "Grid.h"
#include "Unit.h"

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
			if (i<r.left || i>r.right || j > r.top || j < r.bottom)
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
	while (other != NULL)
	{
		unit = other;
		unit->active = false;
		unit->entity->SetActive(false);
		//other->active = false;
		//other->entity->SetActive(false);
		other = other->next;
	}
}



void Grid::HandMelee()
{
	//  walks each cell
	for (int i = 0; i < colNumbers; i++)
		for (int j = 0; j < rowNumbers; j++)
			if (Cells[i][j] != NULL && activeCells[i][j] == true)
				HandleCell(i, j);
}

void Grid::HandleCell(int cellX, int cellY)
{
	if (!Cells[cellX][cellY]->active)
		return;

	Unit* unit = Cells[cellX][cellY];

	while (unit != NULL)
	{
		if (unit->entity->IsActived())
		{
			// Handle other units in this cell
			HandleUnit(unit, unit->next);

			// Handle the neighbor cells
			if (cellX > 0 && cellY > 0)
				HandleUnit(unit, Cells[cellX - 1][cellY - 1]);
			if (cellX > 0)
				HandleUnit(unit, Cells[cellX - 1][cellY]);
			if (cellY > 0)
				HandleUnit(unit, Cells[cellX][cellY - 1]);
			if (cellX > 0 && cellY < cellHeight)
				HandleUnit(unit, Cells[cellX - 1][cellY + 1]);
		}
		unit = unit->next;
	}
}

void Grid::HandleUnit(Unit* unit, Unit* other)
{
	while (other != NULL)
	{
		if (other->entity->IsActived())
			{
				HandleCollision(unit, other);
			}
		other = other->next;
	}
}

void Grid::HandleCollision(Unit* unit, Unit *other)
{
	//OnCollision();
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
			unit->entity->Render();
		unit = unit->next;
	}
}
