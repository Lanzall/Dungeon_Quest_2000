#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <list>
#include "GameCharacter.h"
#include "Player.h"
#include "Tile.h"
#include "Enums.h"
#include "MoveResult.h"

const static std::string path_Hero = "Textures/Hero_sword.png";		// Path to hero texture

const static std::string path_Floor[] =	// Paths to floor tile textures
{
	"Textures/Tile_Grey_base.bmp",
	"Textures/Tile_Grey_blood_1.bmp",
	"Textures/Tile_Grey_bones.bmp",
	"Textures/Tile_Grey_crack_1.bmp",
	"Textures/Tile_Grey_crack_2.bmp",
	"Textures/Tile_Grey_crack_3.bmp",
	"Textures/Tile_Grey_crack_4.bmp:"
};

const static char* roomFiles[]		// Paths to the room files, stored as bitmaps
{
	"Data/Rooms/Room01.bmp",
	"Data/Rooms/Room02.bmp",
	"Data/Rooms/Room03.bmp",
	"Data/Rooms/Room04.bmp",
	"Data/Rooms/Room05.bmp"
};

const static int RoomSize = 10;		// size of the room
const int roomWidth = 10;	// number of tiles in a room
const int roomHeight = 10;
const int overlandWidth = 10;
const int overlandHeight = 10;


class DungeonGame
{
public:
	DungeonGame(float tileSizeX, float tileSizeY);		// pretty sure this is a constructor
	~DungeonGame();

	void LoadTextures(SDL_Renderer* renderer);
	void LoadRoom(const char* filename);		// loads a room from a bitmap file
	void LoadRoom(int x, int y, bool firstTime, int spawnX, int spawnY);	
	void EnteringNewRoom(Direction facingDirection);	// handles the players facing direction when entering a new room
	void InitGrid();		// initializes the tile grid
	void InitOverland();		// initializes the overland grid
	void RefreshVisuals();		// refreshes the tiles between rooms
	Tile* FindNeighbour(int fromX, int fromY, Direction dir);

	Player* Hero;
	Tile Tiles[RoomSize][RoomSize];
	SDL_Texture* FloorTextures[7];		// array of floor tile textures

	bool IsTileFree(Tile* tile);		// checks if a tile is free
	MoveResult MoveAttempt(GameCharacter& character, Direction dir);		// attempts to move a character in a direction
	void HandleMoveDirection(GameCharacter& character, Direction dir);		// handles moving a character in a direction
	void CharacterMovedToTile(GameCharacter& character, Tile* newTile);		// handles when a character moves to a new tile

	int overland[overlandWidth][overlandHeight];		// overland layout
	int currentOverlandX;
	int currentOverlandY;

	SDL_Texture* texture_cantWalk;	// texture for when the player can't walk somewhere
	SDL_Texture* texture_hero;		// texture for the hero

	void Update(double dt);		// updates the game state

private:
	float tileSizeX;
	float tileSizeY;



	std::vector<SDL_Texture*> tileSetA; 	// loaded sdl tile surfaces
	std::vector<SDL_Texture*> tileSetB;	// differing tile surface sets, same for tileSSetC
	std::vector<SDL_Texture*> tileSetC;
};

