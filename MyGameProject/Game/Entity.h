#pragma once
#
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

	struct ColissionReturn
	{
		bool isCollission;
		BoxCollider regionCollision;
	};

	enum MoveDirection {
		LeftToRight,
		RightToLeft,
		None
	};
protected:
	bool isActived;
	int id;
	//Tag Tag;
	//Layer type;

	D3DXVECTOR3 position;				// Vi tri tam
	D3DXVECTOR2 velocity;				// Van toc theo huong x, y
	float width, height;				// Kich thuoc
	MoveDirection direction;			// Huong di chuyen

	virtual void onSetPosition(D3DXVECTOR3 position);	// Set vi tri cua Entity, dung cho ke thua

public:

	bool isStatic;						// Entity tinh or dong
	static int currentID;

	Entity();
	virtual ~Entity();
	
	virtual BoxCollider GetRect();

	virtual void update(float dt);
	virtual void render();
	
	//virtual void OnCollision(Entity* impactor, SideCollision side, float collisionTime, double dt = (1.0 / 60));		// Va cham
	//virtual EarnedData OnDestroy();

	// static
	virtual void SetStatic(bool flag);

	// ID
	virtual int GetID();
	
	// Active
	virtual void SetActive(bool active);
	virtual bool IsActived();

	//virtual Tag GetTag();
	//virtual void SetTag(enum Tag Tag);

	//virtual Layer GetType();
	//virtual void SetType(Layer type);


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