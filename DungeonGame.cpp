#include "DungeonGame.h"
#include "Tile.h"

DungeonGame::DungeonGame(float tileSizeX, float tileSizeY)
{
	this->tileSizeX = tileSizeX;
	this->tileSizeY = tileSizeY;
}

DungeonGame::~DungeonGame()
{

}

void DungeonGame::LoadTextures(SDL_Renderer* renderer)
{
	this->Hero = new Player;

	// Load all textures
	this->Hero->Texture = IMG_LoadTexture(renderer, path_Hero.c_str());
	SDL_SetTextureScaleMode(this->Hero->Texture, SDL_SCALEMODE_NEAREST);
}


void LoadRoom(char* filename)
{
	SDL_Surface* surf = SDL_LoadBMP(filename);

	const SDL_PixelFormatDetails* pixelDetails = SDL_GetPixelFormatDetails(surf->format);
	const Uint8 bpp = SDL_BYTESPERPIXEL(surf->format);
	SDL_Color col;

	for (int y = 0; y < surf->h; y++) {
		for (int x = 0; x < surf->w; x++) {
			Uint8* pixel = static_cast<Uint8*>(surf->pixels) + y * surf->pitch + x * bpp;
			SDL_GetRGB(*reinterpret_cast<Uint32*>(pixel), pixelDetails, NULL, &col.r, &col.g, &col.b);

			// color now containts pixel color at position x,y
			// TODO, configure the title at x/y with this color
		}
	}
}

Tile* GetNeighbour(int currentX, int currentY, Direction dir)
{
	if (dir == Direction::North && currentY > 0)
	{
		return TileGrid[currentX][currentY - 1];

	}
	// follow the pattern for other directions
}

const int numRoomsX = 10;
const int numRoomsY = 10;

int DungeonLayout[numRoomsX][numRoomsY];

/*void RandomizeDungeon()
{
	for (int x = 0; x < numRoomsX; x++)
	{
		for (int y = 0; y < numRoomsY; y++)
		{
			DungeonLayout[x][y] = RandomNum();
		}
	}
}*/