#include "Grid.h"
#include "Unit.h"
#include "Player.h"

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
void Grid::Add(Unit* unit, int cellX, int cellY)
{
	// Add Unit to the front of list at the cell it's in
	unit->prev = NULL;
	unit->next = Cells[cellX][cellY];
	Cells[cellX][cellY] = unit;

	if (unit->next != NULL)
		unit->next->prev = unit;
}

// Active/InActive

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
					
						if (Cells[i][j] == NULL)
							continue;
						Cells[i][j]->Move(Cells[i][j]->entity->GetPosition());
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

	// Handle Active staticObjects
	for (size_t i = 0; i < staticObjects.size(); i++)
	{
		/*if (staticObjects[i]->GetType() == StaticType)
			continue;*/
		BoxCollider box = staticObjects[i]->GetRect();
		if (Camera::GetInstance()->IsCollide(box)) 
			staticObjects[i]->SetActive(true);
		else
			staticObjects[i]->SetActive(false);
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

// Colission

void Grid::HandMelee(float dt)
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
				HandleCell(x, y, dt);
}

void Grid::HandleCell(int cellX, int cellY, float dt)
{
	if (!Cells[cellX][cellY]->active)
		return;

	Unit* unit = Cells[cellX][cellY];

	while (unit != NULL)
	{
		if (unit->entity->IsActived())
		{
			// Handle other units in this cell
			HandleUnit(unit, unit->next, dt);

			// Handle the neighbor cells
			if (cellX > 0 && cellY > 0)
				HandleUnit(unit, Cells[cellX - 1][cellY - 1], dt);
			if (cellX > 0)
				HandleUnit(unit, Cells[cellX - 1][cellY], dt);
			if (cellY > 0)
				HandleUnit(unit, Cells[cellX][cellY - 1], dt);
			if (cellX > 0 && cellY < cellHeight)
				HandleUnit(unit, Cells[cellX - 1][cellY + 1], dt);
		}
		unit = unit->next;
	}
}

void Grid::HandleUnit(Unit* unit, Unit* other, float dt)
{
	while (other != NULL)
	{
		if (other->entity->IsActived())
			{
				HandleCollision(unit->entity, other->entity, dt);
			}
		other = other->next;
	}
}

void Grid::HandleCollision(Entity* ent1, Entity* ent2, float dt)
{
	Entity::SideCollision side;
	
	float collisionTime = 2;


	if (ent1->GetTag()==Tag::PLAYER) 
	{
		collisionTime = CollisionDetector::SweptAABB(ent1, ent2, side, dt);
		if (collisionTime == 2)
			return;
		ent1->OnCollision(ent2, side, collisionTime, dt);
	}
	if (ent2->GetTag() == Tag::PLAYER)
	{
		collisionTime = CollisionDetector::SweptAABB(ent2, ent1, side, dt);
		if (collisionTime == 2)
			return;
		ent2->OnCollision(ent1, side, collisionTime, dt);
	}
}

void Grid::HandleCellWithStatic(Unit* unit, float dt)
{
	while (unit != NULL) {
		if (unit->entity->IsActived()) {
			for (size_t i = 0; i < staticObjects.size(); i++)
			{
				if (staticObjects[i]->GetID() == 1 && unit->entity->GetType() == PlayerType)
					printf("");
				if ((staticObjects[i]->GetType() != Surface || staticObjects[i]->GetTag() == EXITPORT) && staticObjects[i]->IsActived())
					HandleColissionStatic(unit->entity, staticObjects[i], dt);
			}
		}
		unit = unit->next;
	}
}

void Grid::HandleColissionStatic(Entity* ent1, Entity* ent2, float dt)
{
	if (ent2->GetTag() == CHAINEDPILLAR)
		return;
	//ent2's always static
	Entity::SideCollision side;

	BoxCollider rectEnt1 = ent1->GetRect();
	auto impactorRect = ent2->GetRect();

	float groundTime = CollisionDetector::SweptAABB(rectEnt1, ent1->GetVelocity(), impactorRect, D3DXVECTOR2(0, 0), side, dt);

	if (groundTime == 2)
		return;
	ent1->OnCollision(ent2, side, groundTime, dt);
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
	// Draw Grid
	for (int i = 0; i < colNumbers; i++)
		for (int j = 0; j < rowNumbers; j++)
			if ((Cells[i][j] != NULL && activeCells[i][j] == true))
				RenderUnit(Cells[i][j]);
	
	// Draw Player
	Player::GetInstance()->GetCurrentState()->Render();
	D3DXVECTOR3 pos = (D3DXVECTOR3)Player::GetInstance()->GetRect().getCenter();
	Support::DrawRect(pos, Player::GetInstance()->GetRect());
	
	// Draw surface + objectRect
	for (size_t i = 0; i < staticObjects.size(); i++)
	{
		D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);
		switch (staticObjects[i]->GetType()) {
		case PlayerType:
			break;
		case EnemyType:
			break;
		case ItemType:
			break;
		case ObstaclesType:
			break;
		case StaticType:
			break;
		case Surface:
			break;
		}
		BoxCollider boundbox = staticObjects[i]->GetRect();
		D3DXVECTOR3 position = (D3DXVECTOR3)boundbox.getCenter();

		if ((staticObjects[i]->GetType() == Surface) && staticObjects[i]->IsActived())
			staticObjects[i]->Render();

		if (staticObjects[i]->IsActived())
			Support::DrawRect(position, boundbox);
	}
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
		if (unit->entity->GetTag() != PLAYER) {
			LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->GetTexture(2911);
			if (unit->entity->IsActived())
			{
				
				Camera* cam = Camera::GetInstance();
				//if(cam->IsCollide(unit->entity->GetRect()))
				// Draw entity
				unit->entity->Render();

				// Draw ObjectRect
				BoxCollider boundbox = unit->entity->GetRect();
				D3DXVECTOR3 position = (D3DXVECTOR3)boundbox.getCenter();
				Support::DrawRect(position, boundbox);
			}
		}
		unit = unit->next;
	}


}
void Grid::AddStaticObject(Entity* ent) {
	staticObjects.push_back(ent);
}