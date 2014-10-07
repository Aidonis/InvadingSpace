#pragma once

#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "BaseState.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

const int TOTAL_ALIENS = 18;

class GameState : public BaseState
{
public:
	GameState();
	~GameState();

	void Initialize();
	void Update(float a_delatTime, StateMachine* a_pSM);
	void Draw();
	void Destroy();

private:
	void CreateEnemies();
	void MoveEnemies(float a_speed, int a_direction, float a_deltaTime);
	void DrawEnemies();

	void PlayerLogic(Player* a_player, float a_deltaTime);
	void EnemyLogic(Enemy* enemy, bool& down);

	bool CheckCollision(float x1, float y1, float x2, float y2, float distance);

private:
	std::vector<Entity*> gameObjects;
	Enemy aliens[TOTAL_ALIENS];

	unsigned int bulletTextureID;
	int score;
	int direction;

};

#endif //_GAMESTATE_H_