#pragma once
#include "GameConfig.h"
#include "BoxCollider.h"


class Entity
{
public:
	bool isStatic;
	static int currentID;

	// Huong di chuyen
	enum MoveDirection {
		LeftToRight,
		RightToLeft,
		None
	};
protected:
	bool isActived;
	int id;
	Tag tag;

	D3DXVECTOR3 position;				// Vi tri tam
	D3DXVECTOR2 velocity;				// Van toc theo huong x, y
	float width, height;				// Kich thuoc
	MoveDirection direction;			// Huong di chuyen
	//float collisionTime;
	//SideCollision side;

	virtual void onSetPosition(D3DXVECTOR3 position);	// Set vi tri cua Entity, dung cho ke thua

public:

	Entity();
	virtual ~Entity();
	
	virtual BoxCollider GetRect();

	virtual void Update(float dt);
	virtual void Render();

	// static
	virtual void SetStatic(bool flag);

	// ID
	virtual int GetID();

	// Tag
	virtual Tag GetTag();
	virtual void SetTag(enum Tag tag);
	
	// Active
	virtual void SetActive(bool active);
	virtual bool IsActived();

	// Vi tri
	virtual D3DXVECTOR3 GetPosition();

	virtual void SetPosition(D3DXVECTOR3 pos);
	virtual void SetPosition(D3DXVECTOR2 pos);
	virtual void SetPosition(float x, float y);

	virtual void AddPosition(D3DXVECTOR3 pos);
	virtual void AddPosition(D3DXVECTOR2 pos);
	virtual void AddPosition(float x, float y);

	// Van toc
	virtual D3DXVECTOR2 GetVelocity();
	virtual void SetVelocity(D3DXVECTOR2 vel);
	virtual void AddVelocity(D3DXVECTOR2 vel);

	virtual float GetVx();
	virtual void SetVx(float vx);
	virtual void AddVx(float vx);

	virtual float GetVy();
	virtual void SetVy(float vx);
	virtual void AddVy(float vx);

	// Kich Thuoc
	virtual float GetWidth();
	virtual void SetWidth(int width);
	virtual float GetBigWidth();

	virtual float GetHeight();
	virtual void SetHeight(int height);
	virtual float GetBigHeight();

	// Huong di chuyen
	virtual MoveDirection GetMoveDirection();
	virtual void SetMoveDirection(MoveDirection direction);

};