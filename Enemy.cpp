#include "Enemy.h"


Enemy::Enemy()
{
	isActive = true;
}

void Enemy::Update(float a_deltaTime){
	if (isActive){
		x += speed * direction * a_deltaTime;
	}
}

void Enemy::Draw(){
	if (isActive){
		MoveSprite(spriteID, x, y);
		DrawSprite(spriteID);
	}
}

void Enemy::SetDirection(int a_direction){
	direction = a_direction;
}
int Enemy::GetDirection(){
	return direction;
}

void Enemy::SetSpeed(float speed){
	this->speed = speed;
}

float Enemy::GetSpeed(){
	return speed;
}

void Enemy::SetScoreValue(int a_scoreValue){
	scoreValue = a_scoreValue;
}
int Enemy::GetScoreValue(){
	return scoreValue;
}

void Enemy::SetSize(float a_width, float a_height){
	width = a_width;
	height = a_height;
}

void Enemy::SetPosition(float a_x, float a_y){
	x = a_x;
	y = a_y;
}

void Enemy::SetIsActive(bool a_isActive){
	isActive = a_isActive;
}

bool Enemy::GetIsActive(){
	return isActive;
}

Enemy::~Enemy()
{
}
