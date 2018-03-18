#ifndef ENTITY
#define ENTITY

#include "p2DynArray.h"
#include "p2Point.h"
#include "SDL\include\SDL_rect.h"

struct SDL_Texture;

class Entity
{
public:

	Entity();
	Entity(iPoint pos, float speed);
	~Entity();

public:

	virtual bool Update(float dt);
	virtual bool Draw();
	virtual bool HandleInput();

	//returns position of the entity on the map
	iPoint GetPosition();

	//Sets the entity as active
	void SetActive(bool status);

	void Reset();

	bool FindLeader();

	void CopyPathData();
public:
	
	p2DynArray<iPoint> personalPath;
	bool active = false;
	bool lastStep = false;
	bool isLeader = false;
	iPoint pos = { 0,0 };
	iPoint posOnTiles = { 0,0 };
	int currentStep = 0;
	float speed = 0;
	SDL_Rect collider = { 0,0,0,0 };
	SDL_Texture* texture = nullptr;
	bool onDestination = false;
	bool isMoving = false;
	Entity* myLeader = nullptr;
	iPoint nextTile = { 0,0 };
	iPoint destination = { 0,0 };
};

#endif // ENTITY