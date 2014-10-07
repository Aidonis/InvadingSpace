#include "AIE.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include <vector>

//Keyboard Enums broken, search and use GLFW keyboard keys

//Window variables
const int TOTAL_ALIENS = 18;
const float PLAYER_WIDTH = 64.0f;
const float PLAYER_HEIGHT = 32.0f;
float enemySpeed = 500.f;

//Initialize game state functions
void UpdateMainMenu();
void DrawUI();
void UpdateGameState(float a_deltaTime);
void CreateEnemies();
void EnemiesLoad();
void MoveEnemies(int a_direction, float a_deltaTime, float a_speed);
void DrawEnemies();
bool CheckCollision(float x1, float y1, float x2, float y2, float distance);
void PlayerLogic(Player* a_player, float a_deltaTime);
void EnemyLogic(Enemy* a_enemy, bool& a_down);

//Initialize objects
//Player player1;
Player* player = new Player();
//Enemy aliens[TOTAL_ALIENS];
std::vector<Entity*> gameObjects;

int aliensDirection = 1;

//initialize sprite variables
unsigned int arcadeMarquee;
unsigned int bulletTextureID;
unsigned int playerLives1;
unsigned int playerLives2;

//Alien Count
int activeAliens = TOTAL_ALIENS;

//Font
const char* INVADERS_FONT = "./fonts/invaders.fnt";

//UI variables
char* P1_SCORE = "00000";
char* P2_SCORE = "00000";
char* HIGH_SCORE = "00000";
char* TOTAL_CREDITS = "00";
char* TOTAL_LIVES = "2";
char* INSERT_COINS = "Insert_Coins";

enum GAMESTATES{
	MAIN_MENU,
	GAMEPLAY,
	END,
};

int main(int argc, char* argv[])
{
	Initialise(SCREEN_WIDTH, SCREEN_HEIGHT, false, "Psuedo-Invaders");

	SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF));

	GAMESTATES eCurrentState = MAIN_MENU;

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
	playerLives1 = CreateSprite("./images/playerShip1_green.png", player->GetWidth() * 0.5f, player->GetHeight() * 0.5f, true);
	playerLives2 = CreateSprite("./images/playerShip1_green.png", player->GetWidth() * 0.5f, player->GetHeight() * 0.5f, true);
	arcadeMarquee = CreateSprite("./images/Space-Invaders-Marquee.png", 755, 780, true);

	//Initialize sprite position
	MoveSprite(player->GetSpriteID(), player->GetX(), player->GetY());
	MoveSprite(playerLives1, SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT - 715);
	MoveSprite(playerLives2, SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT - 715);
	MoveSprite(arcadeMarquee, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	EnemiesLoad();

	do{

		ClearScreen();
		float deltaT = GetDeltaTime();
		SetFont(INVADERS_FONT);

		switch (eCurrentState){

		case MAIN_MENU:
			UpdateMainMenu();


			if (IsKeyDown(257)){
				eCurrentState = GAMEPLAY;
			}
			if (IsKeyDown(290)){
				Shutdown();
				exit(0);
			}

			break;

		case GAMEPLAY:
			UpdateGameState(deltaT);

			if (IsKeyDown(256)){
				eCurrentState = MAIN_MENU;
			}
			break;

		default:
			break;
		}
	} while (!FrameworkUpdate());

	DestroySprite(player->GetSpriteID());
	DestroySprite(playerLives1);
	DestroySprite(playerLives2);
	DestroySprite(arcadeMarquee);
	Shutdown();

	return 0;
}

void UpdateMainMenu(){
	DrawSprite(arcadeMarquee);
	DrawString(INSERT_COINS, SCREEN_WIDTH * 0.37f, SCREEN_HEIGHT * 0.5f);
	DrawString(TOTAL_CREDITS, SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.4f);
}

void UpdateGameState(float a_deltaTime){

	player->Update(a_deltaTime);
	player->Draw();
	DrawUI();


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

		//Update and draw objects
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

void EnemiesLoad(){

	//Initial position
	float enemyX = SCREEN_WIDTH * .2f;
	float enemyY = SCREEN_HEIGHT * .7f;

	for (int i = 0; i < TOTAL_ALIENS; i++){

		Enemy* aliens = new Enemy();

		//Initialize Sprite
		aliens->SetSize(player->GetWidth(), player->GetHeight());
		aliens->SetSpriteID(CreateSprite("./images/invaders/enemyBlack3.png", player->GetWidth(), player->GetHeight(), true));
		aliens->SetScoreValue(20);
		aliens->SetDirection(aliensDirection);

		if (enemyX > SCREEN_WIDTH * .8f){
			enemyX = SCREEN_WIDTH * .2f;
			enemyY -= .08f * SCREEN_HEIGHT;
		}

		//initialize position
		aliens->SetPosition(enemyX, enemyY);

		//Increment position
		enemyX += .12*SCREEN_WIDTH;

		gameObjects.push_back(aliens);
	}
}

void DrawUI(){
	//Draw UI elements
	DrawString("Score < 1 >", SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT - 2);
	DrawString(player->GetScoreAsString(), SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT - 35);
	DrawString("High-Score", SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT - 2);
	DrawString(HIGH_SCORE, SCREEN_WIDTH * 0.45f, SCREEN_HEIGHT - 35);
	DrawString("Score < 2 >", SCREEN_WIDTH * 0.7f, SCREEN_HEIGHT - 2);
	DrawString(P2_SCORE, SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT - 35);
	DrawString("Credit(s)", SCREEN_WIDTH * 0.7f, SCREEN_HEIGHT - 700);
	DrawString(TOTAL_CREDITS, SCREEN_WIDTH * 0.92f, SCREEN_HEIGHT - 700);
	DrawString("2", SCREEN_WIDTH * 0.05f, SCREEN_HEIGHT - 700);
	DrawLine(0, 100, 672, 100, SColour(255, 255, 255, 255));
	DrawSprite(playerLives1);
	DrawSprite(playerLives2);
}

bool CheckCollision(float x1, float y1, float x2, float y2, float distance){
	float d = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	if (d < distance)
		return true;
	else
	
		return false;
}

void PlayerLogic(Player* a_player, float a_deltaTime){

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

void EnemyLogic(Enemy* a_enemy, bool& a_down){
	if (a_enemy->GetX() > SCREEN_WIDTH * 0.9 && !a_down){
		aliensDirection = -1;
		a_down = true;
	}
	else if(a_enemy->GetX() < SCREEN_WIDTH * 0.1f && !a_down){
		aliensDirection = 1;
		a_down = true;

	}

	int speed = 10;
	a_enemy->SetDirection(aliensDirection);
	a_enemy->SetSpeed(enemySpeed / activeAliens);
}