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
	for (p2List_item<Entity*>* iterator = entitiesList.start; iterator; iterator = iterator->next)
	{
		iterator->data->Update(dt); 
	}

	App->input->GetMousePosition(mousePos.x, mousePos.y);
	mousePos = App->render->ScreenToWorld(mousePos.x, mousePos.y);

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		App->input->GetMousePosition(mouseDownPos.x, mouseDownPos.y);
		mouseDownPos = App->render->ScreenToWorld(mouseDownPos.x, mouseDownPos.y);
	}
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		drawSelectionArea = true;
	}
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
	{
		selectedSquad = CreateSquad();
		drawSelectionArea = false;
	}



	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
	{
		selectedSquad->StartMovement(mousePos);
	}
	return true;
}

bool EntityManager::Draw()
{
	if (selectedSquad)
	{
		for (p2List_item<Entity*>* iterator = selectedSquad->squadMembers.start; iterator; iterator = iterator->next)
		{
			if(iterator->data->isLeader)
				App->render->DrawQuad(iterator->data->collider, 0, 0, 255, 255, false);
			else
				App->render->DrawQuad(iterator->data->collider, 0, 255, 255, 255, false);
		}
	}
	for (p2List_item<Entity*>* iterator = entitiesList.start; iterator; iterator = iterator->next)
	{
		iterator->data->Draw();

		if (drawSelectionArea) DrawSelectionArea();
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

	App->render->DrawQuad(unitSelectionArea, 255, 255, 255, 255, false);
}

Entity* EntityManager::CreateEntity(iPoint pos, float speed)
{
	Entity* tmp = new Entity(pos, speed);
	entitiesList.add(tmp);

	return tmp;
}

Squad* EntityManager::CreateSquad()
{
	p2List<Entity*> tmp;
	for (p2List_item<Entity*>* iterator = entitiesList.start; iterator; iterator = iterator->next)
	{
		if (SDL_HasIntersection(&iterator->data->collider, &unitSelectionArea))
		{
			tmp.add(iterator->data);
		}
	}
	Squad* tmp2 = new Squad(tmp);
	squadsList.add(tmp2);

	return tmp2;
}

bool EntityManager::CleanUp()
{
	return true;
}
