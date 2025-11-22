#include "GameCharacter.h"
#include "Enums.h"

GameCharacter::GameCharacter()
{
}

GameCharacter::~GameCharacter()
{
}

void GameCharacter::Attack(GameCharacter& other)
{
}

void GameCharacter::Killed()
{
}

void GameCharacter::Update(float dt)
{
}

void GameCharacter::Collect(Pickup& pickup)
{
}

bool GameCharacter::CanMoveBetweenRooms()
{
	return false;
}

void GameCharacter::Move(Direction dir, int dist)		// moves the character in a direction by a distance
{
	if (dir == Direction::North)
	{
		Rect.y -= dist;
	}
	else if (dir == Direction::East)
	{
		Rect.x += dist;
	}
	else if (dir == Direction::South)
	{
		Rect.y += dist;
	}
	else if (dir == Direction::West)
	{
		Rect.x -= dist;
	}
}

bool GameCharacter::GetIsAlive()
{
	return false;
}

SDL_FRect* GameCharacter::GetRect()
{
	return nullptr;
}
