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
	//TO DOs 2 and 3: Create the path needed for both the leader and the other units in the squad
	// for the leader, it has to return true in case it can reach the goal
	// it also needs to stop the unit's movement if its distance to the destination is 0
	// before adding the path to the entity delete the previous existing one with CopyPathData

	return false;
}

void Squad::CreateSecondaryPaths()
{
}



bool Squad::SelectNewLeader()
{
	// TO DO 1: Fill the function with the loop to select the new leader
	// it has to return false in case no leader is available
	// make sure it changes the variable bool in each of the entities to false so only the leader has it on true
	// when a leader changes from one that has died/reached the destination the path needs to be remade the the whole squad
	// all entities' myLeader need to point to the new leader

	return false;
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
