#ifndef ENTITY
#define ENTITY

#include "p2Point.h"
#include "SDL\include\SDL_rect.h"

struct SDL_Texture;

class Entity
{
public:

	Entity();
	Entity(iPoint pos, float speed) : pos(pos), speed(speed) {};
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
	float speed = 0;
	SDL_Rect collider = { 0,0,0,0 };
	SDL_Texture* texture = nullptr;
	bool onDestination = false;
};

#endif // ENTITY