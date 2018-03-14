#ifndef ENTITY
#define ENTITY

#include "p2Point.h"
#include "SDL\include\SDL_rect.h"

class SDL_Texture;

class Entity
{
public:

	Entity();
	Entity(iPoint pos) : pos(pos) {};
	~Entity();

public:

	virtual bool Update(float dt);
	virtual bool Draw();
	virtual bool HandleInput();

	//returns position of the entity on the map
	iPoint GetPosition();

	//Sets the entity as active
	void SetActive(bool status);

public:
	
	bool active = false;
	iPoint pos = { 0,0 };
	SDL_Rect collider = { 0,0,0,0 };
	SDL_Texture* texture = nullptr;
	
};

#endif // ENTITY