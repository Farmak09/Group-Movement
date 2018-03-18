#include "Entity.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Map.h"
#include "j1Textures.h"
#include "j1Pathfinding.h"


Entity::Entity()
{
}

Entity::Entity(iPoint poss, float speed) : speed(speed)
{
	texture = App->tex->Load("textures/TestSprite.png");
	active = true;

	posOnTiles = App->map->WorldToMap(poss.x, poss.y); 
	pos = App->map->MapToWorld(posOnTiles.x, posOnTiles.y);
	collider.x = pos.x;
	collider.y = pos.y;
	collider.h = 32;
	collider.w = 32;
}


Entity::~Entity()
{
}

bool Entity::Update(float dt)
{
	if (isMoving && !onDestination)
	{
		if (personalPath.Count() > currentStep)
		{
			if (posOnTiles == nextTile || nextTile.IsZero())
			{
				nextTile = *personalPath.At(currentStep++);
			}
		}
		else if(posOnTiles == nextTile)
		{
			currentStep = 0;

			if (FindLeader())
			{
				nextTile = *personalPath.At(currentStep++);
			}
		}

		if (isMoving && !destination.IsZero())
		{
			if (posOnTiles.x > nextTile.x)
			{
				pos.x -= speed;
			}
			else if (posOnTiles.x < nextTile.x)
			{
				pos.x += speed;
			}
			else if (posOnTiles.y > nextTile.y)
			{
				pos.y -= speed;
			}
			else if(posOnTiles.y < nextTile.y)
			{
				pos.y += speed;
			}
		}
		posOnTiles = App->map->WorldToMap(pos.x, pos.y);
		if (posOnTiles == destination)
		{
			onDestination = true;
		}
		collider.x = pos.x;
		collider.y = pos.y;
	}
	else if (onDestination)
	{
		personalPath.Clear();
	}

	return true;
}

bool Entity::Draw()
{
	bool ret = true;

	if (texture && active)
	{
		ret = App->render->Blit(texture, pos.x, pos.y);

		if (personalPath.Count() > 0)
		{
			SDL_Rect tmpRect;
			tmpRect.h = 32;
			tmpRect.w = 32;
			int i = 0;
			for (iPoint* iterator = personalPath.At(i); i < personalPath.Count(); iterator = personalPath.At(++i))
			{
				iPoint tmp;
				tmp = App->map->MapToWorld(iterator->x, iterator->y);
				tmpRect.x = tmp.x;
				tmpRect.y = tmp.y;
				if(!isLeader)
					App->render->DrawQuad(tmpRect, 0, 255, 255, 100);
				else
					App->render->DrawQuad(tmpRect, 0, 0, 255, 100);
			}
		}
	}

	return ret;
}

bool Entity::HandleInput()
{
	return true;
}

iPoint Entity::GetPosition()
{
	return pos;
}

void Entity::SetActive(bool status)
{
}

void Entity::Reset()
{
	destination = { 0,0 };
	onDestination = false;
	personalPath.Clear();
	lastStep = false;
	isLeader = false;
	myLeader = nullptr;
	nextTile = { 0,0 };
	currentStep = 0;
}

bool Entity::FindLeader()
{
	bool ret = true;

	if (App->pathfinding->CreatePath(posOnTiles, myLeader->posOnTiles) > 0)
		CopyPathData();

	else if (isLeader)
	{
		App->pathfinding->CreatePath(posOnTiles, destination);
		CopyPathData();
	}
	else
	{
		ret = false;
	}

	return ret;
}

void Entity::CopyPathData()
{
	int i = 0;
	personalPath.Clear();
	p2DynArray<iPoint>* tmp = App->pathfinding->GetLastPath();
	for (iPoint iterator; i < tmp->Count(); i++)
	{
		iterator = *tmp->At(i);
		personalPath.PushBack(iterator);
	}
}
