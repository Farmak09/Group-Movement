#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

#include "j1Module.h"
#include "Entity.h"
#include "Squad.h"
#include "p2List.h"
class EntityManager : public j1Module
{
public:

	EntityManager();
	virtual ~EntityManager();

public:

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Update Elements
	bool Update(float dt);

	//Draw all entities
	bool Draw();

	// Draws the area selected when clicking
	void DrawSelectionArea();

	Entity* CreateEntity(iPoint pos, float speed);

	Squad* CreateSquad();
	
	
	
	// Called before quitting
	bool CleanUp();

public:

	iPoint mousePos;
	iPoint mouseDownPos;
	p2List<Entity*> entitiesList;
	p2List<Squad*> squadsList;
	Squad* selectedSquad = nullptr;
	SDL_Rect unitSelectionArea;
	bool drawSelectionArea = false;
};

#endif // ENTITY_MANAGER