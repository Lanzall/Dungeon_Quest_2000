#pragma once
#include <string>
#include <list>
#include <iostream>
#include "Enums.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
class Tile
{
	static bool CompareColours(SDL_Color& col1, SDL_Color& col2);

public:

	Tile();		// default constructor
	Tile(int id);		// constructor with ID
	~Tile();		// destructorinator

	int posX;	// logical position x
	int posY;	// logical position y
	int ID;
	int VisualMaterial;
	SDL_Texture* Texture;
	SDL_FRect Rect;

	void SetPosition(int x, int y);		// sets the position of the tile
	void Configure(SDL_Color& color, float x, float y, float size, SDL_Texture* textures[]);	// configures the tile based on color

	// Neighbours, gets their direction, sets them, adds them to list, gets all
	Tile* GetNeighbour(Direction dir);
	void SetNeighbour(Direction dir, Tile& newNeighbour, bool reciprocate);
	void AddNeighbour(Tile& neighbour, bool reciprocate);
	std::list<Tile>* GetAllNeighbours();

	Direction GetIsEdge();		// gets if the tile is an edge
	void SetIsEdge(Direction dir);		// sets the tile as an edge in a direction

	void SetWalkable(bool canWalk);	// sets if the tile is walkable
	bool GetWalkable();		// gets if the tile is walkable

private:
	std::list<Tile> neighbours;		// list of neighbouring tiles
	Tile* neighbourNorth;
	Tile* neighbourEast;
	Tile* neighbourSouth;
	Tile* neighbourWest;
	Direction edge;
	bool walkable;


};

