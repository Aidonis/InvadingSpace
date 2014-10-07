#pragma once

#ifndef _MAINMENUSTATE_H_
#define _MAINMENUSTATE_H_

#include "BaseState.h"


class MainMenuState : public BaseState
{
public:
	MainMenuState();
	~MainMenuState();

	void Initialize();
	void Update(float a_deltaTime, StateMachine* a_pSM);
	void Draw();
	void Destroy();

private:
	unsigned int arcadeMarquee;

};

#endif //_MAINMENUSTATE_H_