#include "Squad.h"
#include "j1App.h"
#include "j1Pathfinding.h"


Squad::Squad()
{
}

Squad::Squad(p2List<Entity*> squadMembers) : squadMembers(squadMembers)
{
	if (squadMembers.start)
	{
		squadLeader = squadMembers.start->data;
		SelectNewLeader();
	}

}


Squad::~Squad()
{
}

bool Squad::Update(float dt)
{
	if (isMoving)
		if (CreatePath())
		{

		}

	return false;
}

void Squad::StartMovement(iPoint placeClicked)
{
	isMoving = true;
	destination = placeClicked;
}

bool Squad::CreatePath()
{
	bool ret = false;

	if (App->pathfinding->CreatePath(squadLeader->pos, destination) <= 0)
	{
		isMoving = false;
		SelectNewLeader();
	}
	else
	{
		leaderPath = App->pathfinding->GetLastPath();
		ret = true;
	}

	return ret;
}

void Squad::SelectNewLeader()
{
	for (p2List_item<Entity*>* iterator = squadMembers.start; iterator; iterator = iterator->next)
	{
		if (iterator->data->onDestination)
			continue;

		if (iterator->data->pos.DistanceManhattan(destination) < squadLeader->pos.DistanceManhattan(destination))
			squadLeader = iterator->data;
	}
}
