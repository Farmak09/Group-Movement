#include "Entity.h"
#include "j1App.h"
#include "j1Render.h"


Entity::Entity()
{
}


Entity::~Entity()
{
}

bool Entity::Update(float dt)
{
	return true;
}

bool Entity::Draw()
{
	bool ret = true;

	if (texture && active)
		ret = App->render->Blit(texture, pos.x, pos.y);


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
