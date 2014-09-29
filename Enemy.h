#pragma once

#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "Window.h"

class Enemy
{
public:

	void SetSize(float a_width, float a_height);
	void SetPosition(float a_x, float a_y);
	bool Collide(int a_Direction);

	void SetSpriteID(unsigned int spriteID);
	unsigned int GetSpriteID();

	void SetWidth(float width);
	void SetHeight(float height);

	float GetWidth();
	float GetHeight();
	
	void SetX(float x);
	void SetY(float y);

	float GetX();
	float GetY();

	void SetSpeed(float speed);
	float GetSpeed();

	enum DIR{
		LEFT,
		RIGHT,
		DOWN,
	};

	DIR direction = LEFT;

	Enemy();
	~Enemy();

private:
	unsigned int spriteID;
	float speed;
	float width;
	float height;
	float x;
	float y;
};

#endif //_ENEMY_H_