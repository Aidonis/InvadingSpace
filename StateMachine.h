#pragma once

#ifndef _STATEMACHINE_H_
#define  _STATEMACHINE_H_
#include "BaseState.h"
#include <list>

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	void PushState(BaseState* a_gameState);
	BaseState* PopState();
	BaseState* SwitchState(BaseState* a_gameState);

	void Update(float a_deltaTime);
	void Draw();

private:
	std::list<BaseState*> stateStack;
};

#endif // _STATEMACHINE_H_