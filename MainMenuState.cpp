#include "MainMenuState.h"
#include "AIE.h"
#include "GameState.h"
#include "StateMachine.h"


extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const char* INSERT_COINS;
extern const char* TOTAL_CREDITS;

MainMenuState::MainMenuState()
{
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::Initialize(){
	arcadeMarquee = CreateSprite("./images/Space-Invaders-Marquee.png", SCREEN_WIDTH, SCREEN_HEIGHT, true);
	MoveSprite(arcadeMarquee, SCREEN_WIDTH * .5f, SCREEN_HEIGHT * .5f);
}

void MainMenuState::Update(float a_fTimeStep, StateMachine* a_pSM){
	if (IsKeyDown(KEY_ENTER))
	{
		a_pSM->PushState(new GameState());
	}
}

void MainMenuState::Draw(){
	DrawSprite(arcadeMarquee);
	DrawString(INSERT_COINS, SCREEN_WIDTH * 0.37f, SCREEN_HEIGHT * 0.5f, 0.75f);
	DrawString(TOTAL_CREDITS, SCREEN_HEIGHT * 0.25f, SCREEN_HEIGHT * 0.4f, 0.7f);
}

void MainMenuState::Destroy()
{
	DestroySprite(arcadeMarquee);
}