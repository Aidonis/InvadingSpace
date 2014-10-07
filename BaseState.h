#pragma once

#ifndef _BASESTATE_H_
#define _BASESTATE_H_

class StateMachine;

class BaseState
{
public:
	BaseState();
	~BaseState();

	virtual void Initialize() = 0;
	virtual void Update(float a_deltaTime, StateMachine* a_pSM) = 0;
	virtual void Draw() = 0;
	virtual void Destroy() = 0;
};

#endif //_BASESTATE_H_