#ifndef SQUAD
#define SQUAD

#include "p2List.h"
#include "p2DynArray.h"
#include "Entity.h"

class Squad
{
public:
	Squad();
	Squad(p2List<Entity*> squadMembers);
	~Squad();

	bool Update(float dt);
	void StartMovement(iPoint placeClicked);
	bool CreatePath();
	void SelectNewLeader();
public:
	p2List<Entity*> squadMembers;
	Entity* squadLeader;
	bool isMoving = false;
	iPoint destination;
	const p2DynArray<iPoint>* leaderPath;
};

#endif // SQUAD
