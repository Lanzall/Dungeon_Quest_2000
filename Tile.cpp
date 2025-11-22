#include "Tile.h"


bool Tile::CompareColours(SDL_Color& col1, SDL_Color& col2)
{
	return (col1.r == col2.r && col1.g == col2.g && col1.b == col2.b && col1.a == col2.a);	// Compares RGbA values (I hope)
}

Tile::Tile()
{
	neighbourNorth = nullptr;
	neighbourEast = nullptr;
	neighbourSouth = nullptr;
	neighbourWest = nullptr;
	ID = 0;
	VisualMaterial = -1;
	posX = 0;
	posY = 0;
	edge = Direction::Unknown;
	Texture = nullptr;
	Rect = { 0.0f, 0.0f, 0.0f, 0.0f }; // Initialize Rect to zero
	walkable = false;
}

Tile::Tile(int id)
{
	neighbourNorth = nullptr;
	neighbourEast = nullptr;
	neighbourSouth = nullptr;
	neighbourWest = nullptr;
	ID = id;
	VisualMaterial = -1;
	posX = 0;
	posY = 0;
	edge = Direction::Unknown;
	Texture = nullptr; // Initialize Texture
	Rect = { 0.0f, 0.0f, 0.0f, 0.0f }; // Initialize Rect to zero
	walkable = false; // Initialize walkable
}

Tile::~Tile()
{
	// deletes the rectangle?
}

void Tile::SetPosition(int x, int y)
{
}

void Tile::Configure(SDL_Color& color, float x, float y, float size, SDL_Texture* textures[])
{
	SDL_Color black = { 0, 0, 0, 255 };
	if (CompareColours(color, black))		// if the color is black
	{
		SetWalkable(false);		// not walkable
		this->Texture = nullptr;		// no texture
	}
	else
	{
		SetWalkable(true);		// walkable
		this->Texture = textures[1]; 	// floor texture
	}

	SDL_FRect rect;		// creates a rectangle to represent the tile's position and size
	rect.x = x * size;
	rect.y = y * size;
	rect.w = size;
	rect.h = size;
	this->Rect = rect;
}

Tile* Tile::GetNeighbour(Direction dir)
{	
	// Heard that lecturer and other classmates used switch case for this, so I gave it a go
	switch (dir)	// checks the direction
	{
	case Direction::North:	// if north, return north neighbour
		return neighbourNorth;
		break;	// break to avoid fallthrough
	case Direction::East:
		return neighbourEast;
		break;
	case Direction::South:
		return neighbourSouth;
		break;
	case Direction::West:
		return neighbourWest;
		break;

	default:		// if none of the above, return nullptr
		return nullptr;
	}
}

void Tile::SetNeighbour(Direction dir, Tile& newNeighbour, bool reciprocate)
{
	// sets the neighbour in the given direction
	if (dir == Direction::North)
	{
		neighbourNorth = &newNeighbour;
	}
	if (dir == Direction::East)
	{
		neighbourEast = &newNeighbour;
	}
	if (dir == Direction::South)
	{
		neighbourSouth = &newNeighbour;
	}
	if (dir == Direction::West)
	{
		neighbourWest = &newNeighbour;
	}

	neighbours.push_back(newNeighbour);		// adds the new neighbour to the list

	if (reciprocate)
	{
		Direction op = OppositeDirection(dir);		// gets the opposite direction
		newNeighbour.SetNeighbour(op, *this, false);		// sets this tile as the neighbour of the new neighbour
	}
}

void Tile::AddNeighbour(Tile& neighbour, bool reciprocate)
{
}

std::list<Tile>* Tile::GetAllNeighbours()
{
	return &neighbours;		// returns the list of neighbours
}

Direction Tile::GetIsEdge()
{
	return edge;		// returns the edge direction
}

void Tile::SetIsEdge(Direction dir)
{
	edge = dir;		// sets the edge direction
}

void Tile::SetWalkable(bool canWalk)
{
	walkable = canWalk;		// sets the walkable property
}

bool Tile::GetWalkable()
{
	return walkable;		// returns the walkable property
}
