#include "Tile.h"


Tile* GetNeighbour(int currentX, int currentY, Direction dir)
{
	if (dir == Direction::North && currentY > 0)
	{
		return &TileGrid[currentX][currentY - 1];

	}
	// follow the pattern for other directions
}

bool Tile::CompareColours(SDL_Color& col1, SDL_Color& col2)
{
	return (col1.r == col2.r && col1.g == col2.g && col1.b == col2.b && col1.a == col2.a);	// Compares RGbA values (I hope)
}

Tile::Tile()
{
}

Tile::Tile(int id)
{
}

Tile::~Tile()
{
}

void Tile::SetPosition(int x, int y)
{
}

void Tile::Configure(SDL_Color& color, float x, float y, float size, SDL_Texture* textures[])
{
}

Tile* Tile::GetNeighbour(Direction dir)
{
	return nullptr;
}

void Tile::SetNeighbour(Direction dir, Tile& newNeighbour, bool reciprocate)
{
}

void Tile::AddNeighbour(Tile& neighbour, bool reciprocate)
{
}

std::list<Tile>* Tile::GetAllNeighbours()
{
	return nullptr;
}
