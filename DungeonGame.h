#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "GameCharacter.h"
#include "Player.h"
#include "Tile.h"
#include "Enums.h"

const static std::string path_Hero = "Textures/Hero_sword.png";

const static int RoomSize = 10;
const int roomWidth = 10;	// number of tiles in a room
const int roomHeight = 10;
const int overlandWidth = 10;
const int overlandHeight = 10;


class DungeonGame
{
public:
	DungeonGame(float tileSizeX, float tileSizeY);
	~DungeonGame();
	void LoadTextures(SDL_Renderer* renderer);
	Player* Hero;
	Tile TileGrid[roomWidth][roomHeight];

	void Update(double dt);

	Tile* NorthNeighbour;
	Tile* EastNeighbour;
	Tile* SouthNeighbour;
	Tile* WestNeighbour;

private:
	float tileSizeX;
	float tileSizeY;
};

