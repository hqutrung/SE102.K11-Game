#pragma once
#include "GameConfig.h"
#include "BoxCollider.h"

class Entity
{
public:
	enum SideCollision {
		Left, //0
		Right, //1
		Top, //2
		Bottom, //3
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
		NotKnow
	};

	struct CollisionReturn
	{
		bool IsCollided;
		BoxCollider regionCollision;
	};

	// Huong di chuyen
	enum MoveDirection {
		LeftToRight,
		RightToLeft,
		None
	};

	bool isStatic;
	static int currentID;
	
protected:
	bool isActived;
	bool isCollidable;
	int id;
	Tag tag;
	Layer type;

	D3DXVECTOR3 position;				// Vi tri tam
	D3DXVECTOR2 velocity;				// Van toc theo huong x, y
	float width, height;				// Kich thuoc
	MoveDirection direction;			// Huong di chuyen
	BoxCollider collider;

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
	virtual bool IsCollidable() { return isCollidable; };

	// Tag
	virtual Tag GetTag();
	virtual void SetTag(enum Tag tag);
	virtual Layer GetType();
	virtual void SetType(enum Layer layer);
	
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
	virtual void SetVy(float vy);
	virtual void AddVy(float vy);

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

	virtual void SetColliderTop(int top);
	virtual void SetColliderLeft(int left);
	virtual void SetColliderBottom(int bottom);
	virtual void SetColliderRight(int right);

	virtual void OnCollision(Entity* impactor, SideCollision side, float collisionTime, float dt = SPF);
	//virtual EarnedData OnDestroy();

};