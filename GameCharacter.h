#pragma once
#include <SDL3_image/SDL_image.h>
#include "Pickup.h";
#include "Tile.h"


class GameCharacter
{
public:
	GameCharacter();		// constructor, called when created
	~GameCharacter();		// destructor, called when destroyed
	virtual void Attack(GameCharacter& other);
	virtual void Killed();
	virtual void Update(float dt);		// for anything time-related
	virtual void Collect(Pickup& pickup);
	virtual bool CanMoveBetweenRooms();		// false by defualt
	void Move(Direction dir, int dist);		// moves the character in a direction by a distance
	bool GetIsAlive();


	Tile* CurrentTile;		// the tile the character is currently on
	SDL_FRect* GetRect();
	SDL_Texture* Texture;
	SDL_FRect Rect;

private:
	bool isAlive = true;
	

};

