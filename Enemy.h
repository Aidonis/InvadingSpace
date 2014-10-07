#pragma once

#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "Window.h"
#include "Entity.h"
#include "AIE.h"


class Enemy : public Entity
{
public:

	void SetSize(float a_width, float a_height);
	void SetPosition(float a_x, float a_y);
	bool Collide(int a_Direction);

	virtual void Update(float a_deltaTime);
	virtual void Draw();

	bool isActive;

	void SetSpeed(float speed);
	float GetSpeed();

	void SetScoreValue(int a_scoreValue);
	int GetScoreValue();

	void SetDirection(int a_direction);
	int GetDirection();


	Enemy();
	~Enemy();

private:
	float speed;
	unsigned int scoreValue;
	int direction;
};

#endif //_ENEMY_H_