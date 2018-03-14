#include "EntityManager.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"


EntityManager::EntityManager()
{
	name = "entityManager";
}


EntityManager::~EntityManager()
{
}

bool EntityManager::Awake(pugi::xml_node &)
{
	return true;
}

bool EntityManager::Start()
{
	return true;
}

bool EntityManager::Update(float dt)
{
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		App->input->GetMousePosition(mouseDownPos.x, mouseDownPos.y);
		mouseDownPos = App->render->ScreenToWorld(mouseDownPos.x, mouseDownPos.y);
	}
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		App->input->GetMousePosition(mousePos.x, mousePos.y);
		mousePos = App->render->ScreenToWorld(mousePos.x, mousePos.y);

		DrawSelectionArea();
	}
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
	{
		selectedSquad = CreateSquad(MakeEntityListFromSelection());
	}
	return true;
}

void EntityManager::DrawSelectionArea()
{
	if (mouseDownPos.x >= mousePos.x)
	{
		unitSelectionArea.x = mousePos.x;
		unitSelectionArea.w = mouseDownPos.x - mousePos.x;
	}
	else
	{
		unitSelectionArea.x = mouseDownPos.x;
		unitSelectionArea.w = mousePos.x - mouseDownPos.x;
	}

	if (mouseDownPos.y >= mousePos.y)
	{
		unitSelectionArea.y = mousePos.y;
		unitSelectionArea.h = mouseDownPos.y - mousePos.y;
	}
	else
	{
		unitSelectionArea.y = mouseDownPos.y;
		unitSelectionArea.h = mousePos.y - mouseDownPos.y;
	}

	App->render->DrawQuad(unitSelectionArea, 0, 100, 0, 80);
}

p2List<Entity*> EntityManager::MakeEntityListFromSelection()
{
	p2List<Entity*> tmp;
	for (p2List_item<Entity*>* iterator = entitiesList.start; iterator; iterator->next)
	{
		if (SDL_HasIntersection(&iterator->data->collider, &unitSelectionArea))
		{
			tmp.add(iterator->data);
		}
	}
	return tmp;
}

Entity* EntityManager::CreateEntity(iPoint pos)
{
	Entity* tmp = new Entity(pos);
	entitiesList.add(tmp);

	return tmp;
}

Squad* EntityManager::CreateSquad(p2List<Entity*> squadMembers)
{
	Squad* tmp = new Squad(squadMembers);
	squadsList.add(tmp);

	return tmp;
}

bool EntityManager::CleanUp()
{
	return false;
}
