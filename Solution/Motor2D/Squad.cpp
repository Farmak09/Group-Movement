#include "Squad.h"
#include "j1App.h"
#include "j1Pathfinding.h"
#include "j1Map.h"


Squad::Squad()
{
}

Squad::Squad(p2List<Entity*> &squaders)
{
	for (p2List_item<Entity*>* iterator = squaders.start; iterator; iterator = iterator->next)
	{
		squadMembers.add(iterator->data);
	}

	if (squadMembers.start)
	{
		squadLeader = squadMembers.start->data;
		squadLeader->isLeader = true;
		SelectNewLeader();
	}
}


Squad::~Squad()
{
}

bool Squad::Update(float dt)
{

	return true;
}

void Squad::StartMovement(iPoint placeClicked)
{
	isMoving = true;
	destination = App->map->WorldToMap(placeClicked.x, placeClicked.y);

	for (p2List_item<Entity*>* iterator = squadMembers.start; iterator; iterator = iterator->next)
	{
		iterator->data->Reset();
		iterator->data->isMoving = true;
		iterator->data->destination = destination;
		iterator->data->onDestination = false;
	}

	SelectNewLeader();

	GenerateNewPaths();
}

void Squad::GenerateNewPaths()
{
	if (CreateMainPath())
	{
		CreateSecondaryPaths();
	}
	else
	{
		isMoving = false;
	}
}

bool Squad::CreateMainPath()
{
	bool ret = false;

	if (App->pathfinding->CreatePath(squadLeader->posOnTiles, destination) <= 0 && !destination.IsZero())
	{
		squadLeader->isMoving = false;
		squadLeader->onDestination = true;

		if (SelectNewLeader())
		{
			App->pathfinding->CreatePath(squadLeader->posOnTiles, destination);
			CopyPathData(squadLeader);

			ret = true;
		}
	}
	else if(!destination.IsZero())
	{
		CopyPathData(squadLeader);
		ret = true;
	}

	return ret;
}

void Squad::CreateSecondaryPaths()
{
	for (p2List_item<Entity*>* iterator = squadMembers.start; iterator; iterator = iterator->next)
	{
		if (iterator->data == squadLeader)
			continue;


		if (App->pathfinding->CreatePath(iterator->data->posOnTiles, squadLeader->posOnTiles) > 0)
			CopyPathData(iterator->data);

		else
			iterator->data->isMoving = false;
	}
}



bool Squad::SelectNewLeader()
{
	bool ret = false;

	for (p2List_item<Entity*>* iterator = squadMembers.start; iterator; iterator = iterator->next)
	{
		iterator->data->isLeader = false;

		if (iterator->data->onDestination)
			continue;

		if (iterator->data->posOnTiles.DistanceManhattan(destination) < squadLeader->posOnTiles.DistanceManhattan(destination))
		{
			squadLeader = iterator->data;
			ret = true;
		}
	}

	if (squadLeader)
	{
		squadLeader->isLeader = true;

		GenerateNewPaths();

		for (p2List_item<Entity*>* iterator = squadMembers.start; iterator; iterator = iterator->next)
		{
			iterator->data->myLeader = squadLeader;
		}
	}
	return ret;
}

void Squad::CopyPathData(Entity* entity)
{
	int i = 0;
	entity->personalPath.Clear();
	p2DynArray<iPoint>* tmp = App->pathfinding->GetLastPath();
	for (iPoint iterator; i < tmp->Count(); i++)
	{
		iterator = *tmp->At(i);
		entity->personalPath.PushBack(iterator);
	}
}
