#include "GameState.h"
#include "AIE.h"
#include "StateMachine.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HIEGHT;

extern const float PLAYER_WIDTH;
extern const float PLAYER_HEIGHT;


extern const char* INVADERS_FONT;
extern const char* P1_SCORE;
extern const char* P2_SCORE;
extern const char* HIGH_SCORE;
extern const char* TOTAL_LIVES;


GameState::GameState(void)
{
	score = 0;
	direction = 1;
	bulletTextureID = -1;
}

void GameState::Initialize(){

	Player* player = new Player();

	//Initialize player
	player->SetSize(PLAYER_WIDTH, PLAYER_HEIGHT);
	player->SetSpriteID(CreateSprite("./images/playerShip1_green.png", player->GetWidth(), player->GetHeight(), true));
	player->SetX(SCREEN_WIDTH * 0.5f);
	player->SetY(140);
	player->SetMovementKeys('A', 'D');
	player->SetMovementExtremes(0, SCREEN_WIDTH);
	player->SetSpeed(200.f);
	player->SetShootKey(265);

	//add player object to the dynamic array
	gameObjects.push_back(player);

	bulletTextureID = CreateSprite("./images/laserGreen04.png", 5, 20, true);

	//Initialize font
	AddFont(INVADERS_FONT);

	//Initialize UI sprites
	//playerLives1 = CreateSprite("./images/playerShip1_green.png", player->GetWidth() * 0.5f, player->GetHeight() * 0.5f, true);
	//playerLives2 = CreateSprite("./images/playerShip1_green.png", player->GetWidth() * 0.5f, player->GetHeight() * 0.5f, true);

	//Initialize sprite position
	MoveSprite(player->GetSpriteID(), player->GetX(), player->GetY());

	//Load enemies
	EnemiesLoad();
}

void GameState::Destroy(){
	for (auto object : gameObjects){
		DestroySprite(object->GetSpriteID());
	}
	DestroySprite(bulletTextureID);
}

void GameState::PlayerLogic(Player* player, float a_deltaTime){
	player->Shoot(bulletTextureID, a_deltaTime);

	for (int i = 0; i < MAX_BULLETS; i++){
		player->bullets[i].Update(a_deltaTime);
		player->bullets[i].Draw();
	}

	for (auto object : gameObjects){
		if (dynamic_cast<Enemy*>(object) != 0){
			Enemy* aliens = dynamic_cast<Enemy*>(object);
			for (int i = 0; i < MAX_BULLETS; i++){
				if (CheckCollision(player->bullets[i].x, player->bullets[i].y, aliens->GetX(), aliens->GetY(), 30.0f) && aliens->GetIsActive() && player->bullets[i].isActive){
					aliens->SetIsActive(false);
					player->bullets[i].isActive = false;
					player->AddScore(aliens->GetScoreValue());
					activeAliens--;
				}
			}
		}
	}
}

void GameState::EnemyLogic(Enemy* a_enemy, bool& a_down){
	if (a_enemy->GetX() > SCREEN_WIDTH * 0.9 && !a_down){
		direction = -1;
		a_down = true;
	}
	else if (a_enemy->GetX() < SCREEN_WIDTH * 0.1f && !a_down){
		direction = 1;
		a_down = true;

	}

	int speed = 10;
	a_enemy->SetDirection(direction);
	a_enemy->SetSpeed(enemySpeed / activeAliens);
}

void GameState::Update(float a_deltaTime, StateMachine* a_pSM){
	player->Update(a_deltaTime);
	player->Draw();
	DrawUI();

	if (IsKeyDown(KEY_ESC)){
		BaseState* lastState = a_pSM->PopState();
		delete lastState;
		return;
	}



	bool down = false;

	for (auto object : gameObjects){
		//Determine type at runtime
		if (dynamic_cast<Player*>(object) != 0){
			//Process player logic
			PlayerLogic(dynamic_cast<Player*>(object), a_deltaTime);
		}

		if (dynamic_cast<Enemy*>(object) != 0){
			//Process Enemy Logic
			EnemyLogic(dynamic_cast<Enemy*>(object), down);
		}

		//Update anddraw objects
		object->Update(a_deltaTime);
		object->Draw();
	}

	if (down){
		for (auto object : gameObjects){
			if (dynamic_cast<Enemy*>(object) != 0){
				Enemy* enemy = dynamic_cast<Enemy*>(object);

				enemy->SetY(enemy->GetY() - (0.05f * SCREEN_HEIGHT));
			}
		}
	}
}
////////
//START HERE
///////
void GameState::Draw(){
	for (auto object : gameObjects){
		object->Draw();
	}

	Draw();
}


GameState::~GameState()
{
}
