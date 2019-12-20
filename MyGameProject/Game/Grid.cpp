#include "Grid.h"
#include "Unit.h"
#include "Player.h"
#include "ExitPort.h"
#include"Enemy.h"
#include "Jafar.h"

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
	effects = NULL;
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
					other = unit->pNext;
					delete unit;
					unit = other;
				}
				Cells[x][y] = NULL;
			}
	//delete effects double link list
	EffectChain* chain = effects;
	while (effects != NULL) {
		chain = effects->pNext;
		delete effects;
		effects = chain;
	}
	effects = NULL;
	//delete static object;
	for (size_t i = 0; i < staticObjects.size(); i++) {
		delete staticObjects[i];
		staticObjects[i] = NULL;
	}
}

void Grid::AddUnit(Unit* unit)
{
	// Determine which cell it's in
	int cellX = (int)(unit->pos.x / this->cellWidth);
	int cellY = (int)(unit->pos.y / this->cellHeight);

	// Add Unit to the front of list at the cell it's in
	unit->pPrev = NULL;
	unit->pNext = Cells[cellX][cellY];
	Cells[cellX][cellY] = unit;

	if (unit->pNext != NULL)
		unit->pNext->pPrev = unit;
}
void Grid::AddUnit(Unit* unit, int cellX, int cellY)
{
	// Add Unit to the front of list at the cell it's in
	unit->pPrev = NULL;
	unit->pNext = Cells[cellX][cellY];
	Cells[cellX][cellY] = unit;

	if (unit->pNext != NULL)
		unit->pNext->pPrev = unit;
}

void Grid::RemoveUnit(Unit* unit)
{
	int cellX = (int)(unit->pos.x / cellWidth);
	int cellY = (int)(unit->pos.y / cellHeight);

	if (unit->pPrev != NULL)
		unit->pPrev->pNext = unit->pNext;
	if (unit->pNext != NULL)
		unit->pNext->pPrev = unit->pPrev;

	// If it's the head of a list, remove it.
	if (Cells[cellX][cellY] == unit)
		Cells[cellX][cellY] = unit->pNext;
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

	if (unit->pPrev != NULL)
		unit->pPrev->pNext = unit->pNext;
	if (unit->pNext != NULL)
		unit->pNext->pPrev = unit->pPrev;

	// If it's the head of a list, remove it.
	if (Cells[oldCellX][oldCellY] == unit)
		Cells[oldCellX][oldCellY] = unit->pNext;

	// Add it to the grid at new cell.
	AddUnit(unit);
}

void Grid::MoveActiveUnit(Unit* unit)
{
	Unit* other = unit;
	while (other != NULL)
	{
		unit = other;
		unit->Move(unit->entity->GetPosition());
		other = other->pNext;
	}
}

// Active/InActive

void Grid::HandleActive(BoxCollider camRect, Entity::MoveDirection camDirection)
{
	// Get cellRec which contain camRect
	RECT r;
	r.left = (int)(Support::Clamp(camRect.left / cellWidth, 0, colNumbers));
	r.right = (int)(Support::Clamp(camRect.right / cellWidth, 0, colNumbers));
	r.top = (int)(Support::Clamp(camRect.top / cellHeight, 0, rowNumbers));
	r.bottom = (int)(Support::Clamp(camRect.bottom / cellHeight, 0, rowNumbers));

	// Check Active: it's in r => active
	for (int i = 0; i < colNumbers; i++)
		for (int j = 0; j < rowNumbers; j++)
		{
			if (i < r.left || i > r.right || j > r.top || j < r.bottom)
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
		BoxCollider box = staticObjects[i]->GetRect();
		if (staticObjects[i]->GetTag() == EXITPORT)
		{
			ExitPort* exitPort = (ExitPort*)staticObjects[i];
			box = exitPort->GetSpawnBox();
		}
		staticObjects[i]->SetActive(Camera::GetInstance()->IsCollide(box));
	}

}

void Grid::HandleActiveUnit(BoxCollider camRect, Entity::MoveDirection camDirection, Unit* unit)
{
	Unit* other = unit;

	while (other != NULL)
	{
		other->active = true;
		if (other->entity->GetType() != pWeapon && other->entity->GetType() != eWeapon) {
			if (other->entity->GetTag() == BAT)
				int x = 0;
			// Set active entity
			other->entity->SetActive(true);
		}
		other = other->pNext;
	}
}

void Grid::HandleInActiveUnit(Unit* unit)
{
	Unit* other = unit;
	while (other != NULL) {
		unit = other;
		unit->active = false;
		unit->entity->SetActive(false);
		other = unit->pNext;
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
		if (unit->entity->GetType() == pWeapon && unit->entity->IsActived())
			int x = 0;
		if (unit->entity->IsActived())
		{

			// Handle other units in this cell
			HandleUnit(unit, unit->pNext, dt);

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
		unit = unit->pNext;
	}
}

void Grid::HandleUnit(Unit* unit, Unit* other, float dt)
{
	while (other != NULL)
	{
		if (unit->entity->IsActived() && other->entity->IsActived())
		{
			HandleCollision(unit->entity, other->entity, dt);
		}
		other = other->pNext;
	}
}

void Grid::HandleCollision(Entity* ent1, Entity* ent2, float dt)
{

	float colTime = 2;
	Entity::SideCollision  side;
	auto rectEnt1 = ent1->GetRect();
	auto rectEnt2 = ent2->GetRect();

	// eWeapon vs Player

	/*if (ent1->GetType() == PlayerType && ent2->GetType() == eWeapon)
	{
		auto e = (Player*)ent1;
		rectEnt1 = e->GetBody();
	}
	else if (ent2->GetType() == PlayerType && ent1->GetType() == eWeapon)
	{
		auto e = (Player*)ent2;
		rectEnt2 = e->GetBody();
	}*/

	// apple and enemy
	if (ent1->GetType() == pWeapon && ent2->GetType() == EnemyType)
	{
		auto e = (Enemy*)ent2;
		rectEnt2 = e->GetBody();
	}
	else if (ent2->GetType() == pWeapon && ent1->GetType() == EnemyType)
	{
		auto e1 = (Enemy*)ent1;
		rectEnt1 = e1->GetBody();
	}

	// player vs Jafar
	/*if (ent1->GetType() == PlayerType && ent2->GetTag()==JAFAR)
	{
		auto e = (Jafar*)ent2;
		rectEnt2 = e->GetBody();
	}
	else if (ent2->GetType() == PlayerType && ent1->GetTag() == JAFAR)
	{
		auto e = (Jafar*)ent1;
		rectEnt1 = e->GetBody();
	}*/


	colTime = CollisionDetector::SweptAABB(rectEnt1, ent1->GetVelocity(), rectEnt2, ent2->GetVelocity(), side, dt);


	//=======================

	if (!ent1->isStatic) {
		if (colTime == 2)
			return;
		ent1->OnCollision(ent2, side, colTime, dt);
	}

	if (!ent2->isStatic) {
		if (colTime == 2)
			return;
		switch (side)
		{
		case Entity::Left:
			side = Entity::Right;
			break;
		case Entity::Right:
			side = Entity::Left;
			break;
		case Entity::Top:
			side = Entity::Bottom;
			break;
		case Entity::Bottom:
			side = Entity::Top;
			break;
		default:
			break;
		}
		ent2->OnCollision(ent1, side, colTime, dt);
	}
}

void Grid::HandleCellWithStatic(Unit* unit, float dt)
{
	while (unit != NULL) {
		if (unit->entity->IsActived()) {
			if (unit->entity->GetTag() == BAT)
				int x = 0;
			for (size_t i = 0; i < staticObjects.size(); i++)
			{
				if (staticObjects[i]->IsActived())
					HandleColissionStatic(unit->entity, staticObjects[i], dt);
			}
		}
		unit = unit->pNext;
	}
}

void Grid::HandleColissionStatic(Entity* ent1, Entity* ent2, float dt)
{
	float colTime = 2;
	auto player = Player::GetInstance();
	Entity::SideCollision side;

	if (ent2->GetType() == Surface && ent2->GetTag() != EXITPORT)
		return;

	auto rectEnt1 = ent1->GetRect();
	auto impactorRect = ent2->GetRect();

	if (ent1->GetTag() == PLAYER && ent2->GetTag() == WALL)
	{
		if (player->GetMoveDirection() == Player::MoveDirection::LeftToRight)
			rectEnt1 = BoxCollider(player->GetBigBound().top, player->GetPosition().x + 5, player->GetBigBound().right, player->GetBigBound().bottom);
		else
			rectEnt1 = BoxCollider(player->GetBigBound().top, player->GetBigBound().left, player->GetPosition().x - 5, player->GetBigBound().bottom);
	}
	
	colTime = CollisionDetector::SweptAABB(rectEnt1, ent1->GetVelocity(), impactorRect, D3DXVECTOR2(0, 0), side, dt);
	if (colTime == 2)
		return;

	ent1->OnCollision(ent2, side, colTime, dt);
}

void Grid::Update(float dt)
{
	// Update Unit
	for (int i = 0; i < colNumbers; i++)
		for (int j = 0; j < rowNumbers; j++)
			if ((Cells[i][j] != NULL && activeCells[i][j] == true))
				UpdateUnit(Cells[i][j], dt);

	UpdateEffect(dt);

	for (size_t i = 0; i < staticObjects.size(); i++)
	{
		if (staticObjects[i]->GetTag() == CHAINEDPILLAR)
			int x = 0;
		if ((staticObjects[i]->GetType() == ObstaclesType) || staticObjects[i]->GetTag() == CHAINEDPILLAR || staticObjects[i]->GetTag() == SNAKEPILLAR)
			staticObjects[i]->Update(dt);
	}

	// Move Unit
	for (int i = 0; i < colNumbers; i++)
		for (int j = 0; j < rowNumbers; j++)
			if ((Cells[i][j] != NULL && activeCells[i][j] == true))
				MoveActiveUnit(Cells[i][j]);
}

#include "Enemy.h"
void Grid::UpdateUnit(Unit* unit, float dt)
{
	while (unit != NULL)
	{
		if (unit->entity->IsActived())
		{
			unit->entity->Update(dt);
			if (unit->entity->GetType() == EnemyType)
			{
				auto enemy = (Enemy*)unit->entity;
				if (enemy->isDied) {
					RemoveUnit(unit);
				}
			}
		}
		unit = unit->pNext;
	}
}

void Grid::Render()
{
	if (KeyBoard::GetInstance()->GetKey(DIK_O))
		isDrawRect = false;
	if (KeyBoard::GetInstance()->GetKey(DIK_P))
		isDrawRect = true;

	// Draw items + obstacles
	for (size_t i = 0; i < staticObjects.size(); i++)
	{
		if ((staticObjects[i]->GetTag() == SNAKEPILLAR))
			continue;
		if ((staticObjects[i]->GetType() == ObstaclesType) && staticObjects[i]->IsActived()) {
			staticObjects[i]->Render();
			if (isDrawRect) {
				BoxCollider boundbox = staticObjects[i]->GetRect();
				D3DXVECTOR3 position = (D3DXVECTOR3)boundbox.getCenter();
				Support::DrawRect(position, boundbox);
			}
		}
	}

	// Draw Grid
	for (int i = 0; i < colNumbers; i++)
		for (int j = 0; j < rowNumbers; j++)
			if ((Cells[i][j] != NULL && activeCells[i][j] == true))
				RenderUnit(Cells[i][j]);

	// Draw Player
	if (Player::GetInstance()->IsActived())
		Player::GetInstance()->Render();
	D3DXVECTOR3 pos = (D3DXVECTOR3)Player::GetInstance()->GetRect().getCenter();
	if (isDrawRect)
		Support::DrawRect(pos, Player::GetInstance()->GetRect());

	RenderEffect();

	// Draw surface
	for (size_t i = 0; i < staticObjects.size(); i++)
	{
		if (staticObjects[i]->GetType() == ObstaclesType || staticObjects[i]->GetTag() == SNAKEPILLAR)
			continue;
		if ((staticObjects[i]->GetType() == Surface) && staticObjects[i]->IsActived() || (staticObjects[i]->GetTag() == CHAINEDPILLAR)) {
			staticObjects[i]->Render();
		}
		if (isDrawRect && staticObjects[i]->IsActived() && staticObjects[i]->GetTag() != CHAINEDPILLAR) {
			BoxCollider boundbox = staticObjects[i]->GetRect();
			D3DXVECTOR3 position = (D3DXVECTOR3)boundbox.getCenter();
			Support::DrawRect(position, boundbox);
		}
	}

}

void Grid::RenderUnit(Unit* unit)
{
	while (unit != NULL)
	{
		LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->GetTexture(2911);
		if (unit->entity->IsActived())
		{
			if (unit->entity->GetType() != PlayerType)
				unit->entity->Render();
			// Draw ObjectRect
			if (isDrawRect) {
				BoxCollider boundbox = unit->entity->GetRect();
				D3DXVECTOR3 position = (D3DXVECTOR3)boundbox.getCenter();
				Support::DrawRect(position, boundbox);
			}
		}
		unit = unit->pNext;
	}
}

void Grid::AddStaticObject(Entity* ent) {
	staticObjects.push_back(ent);
}

// Effects
void Grid::AddEffect(EffectChain* chain)
{
	chain->pPrev = NULL;
	chain->pNext = effects;
	effects = chain;
	if (chain->pNext != NULL)
		chain->pNext->pPrev = chain;
}

void Grid::RemoveEffect(EffectChain* chain)
{
	if (chain->pPrev != NULL)
		chain->pPrev->pNext = chain->pNext;
	if (chain->pNext != NULL)
		chain->pNext->pPrev = chain->pPrev;
	// If it's the head of a list, remove it.
	if (effects == chain)
		effects = chain->pNext;
	chain = effects;
}

void Grid::UpdateEffect(double dt)
{
	auto chain = effects;
	while (chain != NULL) {
		if ((!chain->data->Update(dt)))
			RemoveEffect(chain);
		chain = chain->pNext;
	}
}

void Grid::RenderEffect()
{
	auto chain = effects;
	while (chain != NULL) {
		chain->data->Render();
		chain = chain->pNext;
	}
}

void Grid::RenderBackGround()
{
	for (size_t i = 0; i < staticObjects.size(); i++)
	{
		if (staticObjects[i]->IsActived() || (staticObjects[i]->GetTag() == SNAKEPILLAR))
			staticObjects[i]->Render();
	}
}

Entity* Grid::findObject(Tag tag)
{
	BoxCollider camRect = Camera::GetInstance()->GetRect();
	RECT r;
	r.left = (int)(Support::Clamp(camRect.left / cellWidth, 0, colNumbers));
	r.right = (int)(Support::Clamp(camRect.right / cellWidth, 0, colNumbers));
	r.top = (int)(Support::Clamp(camRect.top / cellHeight, 0, rowNumbers));
	r.bottom = (int)(Support::Clamp(camRect.bottom / cellHeight, 0, rowNumbers));

	for (int i = r.bottom; i < r.top; i++)
		for (int j = r.left; j < r.right; j++)
		{
			Unit* unit = Cells[i][j];
			while (unit != NULL)
			{
				if (unit->entity->GetTag() == tag)
					return unit->entity;
				unit = unit->pNext;
			}
		}
	return NULL;
}
