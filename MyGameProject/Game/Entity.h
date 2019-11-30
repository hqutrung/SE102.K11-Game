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

protected:
	bool isActived;
	int id;
	Tag tag;

	Layer type;

	D3DXVECTOR3 position;				// Vi tri tam
	D3DXVECTOR2 velocity;				// Van toc theo huong x, y
	D3DXVECTOR2 acceleration = D3DXVECTOR2(0,0);           // gia toc
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
	//layer
	virtual Layer GetType();
	virtual void SetType(Layer type);
	
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
	//gia toc
	virtual D3DXVECTOR2 GetAcceleration() { return acceleration; };
	virtual void SetAcceleration(float ax, float ay) {
		acceleration.x = ax; acceleration.y = ay;
	};
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
	virtual void OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt = SPF);


	struct CollisionReturn
	{
		bool IsCollided;
		BoxCollider regionCollision;
	};

};