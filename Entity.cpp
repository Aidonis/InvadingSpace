#include "Entity.h"


Entity::Entity()
{
}

void Entity::SetSize(float a_width, float a_height)
{
	width = a_width;
	height = a_height;
}

void Entity::SetPosition(float a_x, float a_y)
{
	x = a_x;
	y = a_y;
}

void Entity::SetSpriteID(unsigned int a_spriteID)
{
	spriteID = a_spriteID;
}

unsigned int Entity::GetSpriteID()
{
	return spriteID;
}

void Entity::SetWidth(float a_width)
{
	width = a_width;
}

void Entity::SetHeight(float a_height)
{
	height = a_height;
}

float Entity::GetWidth()
{
	return width;
}

float Entity::GetHeight()
{
	return height;
}

void Entity::SetX(float a_x)
{
	x = a_x;
}

void Entity::SetY(float a_y)
{
	y = a_y;
}

float Entity::GetX()
{
	return x;
}

float Entity::GetY()
{
	return y;
}

Entity::~Entity()
{
}
