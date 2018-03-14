#ifndef SQUAD
#define SQUAD

#include "p2List.h"
#include "Entity.h"

class Squad
{
public:
	Squad();
	Squad(p2List<Entity*> squadMembers);
	~Squad();
};

#endif // SQUAD
