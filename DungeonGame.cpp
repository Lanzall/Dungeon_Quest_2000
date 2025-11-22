#include "DungeonGame.h"
#include "Tile.h"

DungeonGame::DungeonGame(float tileSizeX, float tileSizeY)
{
	this->tileSizeX = tileSizeX;
	this->tileSizeY = tileSizeY;
}

DungeonGame::~DungeonGame()
{
	delete this->Hero;		// used ai to figure out why this was needed, was causing memory leaks?
}

void DungeonGame::LoadTextures(SDL_Renderer* renderer)
{
	this->Hero = new Player;

	// Load all textures
	this->Hero->Texture = IMG_LoadTexture(renderer, path_Hero.c_str());		// loads the hero texutre using the path we defined earlier
	SDL_SetTextureScaleMode(this->Hero->Texture, SDL_SCALEMODE_NEAREST);	// Works like Point filtering in Unity, makes the pixels sharp

	this->Hero->Rect.x = 0;
	this->Hero->Rect.y = 0;
	this->Hero->Rect.w = tileSizeX;
	this->Hero->Rect.h = tileSizeY;

	for (int n = 0; n < 3; n++)		// loads floor textures
	{
		this->FloorTextures[n] = IMG_LoadTexture(renderer, path_Floor[n].c_str());
		SDL_SetTextureScaleMode(this->FloorTextures[n], SDL_SCALEMODE_NEAREST);
	}
}

void DungeonGame::Update(double dt)		// made in lesson, forgot what for, woopsies. I think it's DeltaTime?
{
}


void DungeonGame::LoadRoom(const char* filename)
{
	SDL_Surface* surface = SDL_LoadBMP(filename);

	const SDL_PixelFormatDetails* pixelDetails = SDL_GetPixelFormatDetails(surface->format);
	const Uint8 bpp = SDL_BYTESPERPIXEL(surface->format);
	SDL_Color color;

	for (int y = 0; y < surface->h; y++)
	{
		for (int x = 0; x < surface->w; x++)
		{
			Uint8* pixel = static_cast<Uint8*>(surface->pixels) + y * surface->pitch + x * bpp;		// gets the pixel at (x, y)
			SDL_GetRGB(*reinterpret_cast<Uint32*>(pixel), pixelDetails, NULL, &color.r, &color.g, &color.b);

			// color shouild now contain the color of the pixel at (x, y)

			this->Tiles[x][y].Configure(color, x, y, tileSizeX, this->FloorTextures);		// configure the tile based on the color
		}
	}
}

void DungeonGame::LoadRoom(int x, int y, bool firstTime, int spawnX, int spawnY)
{
}

void DungeonGame::EnteringNewRoom(Direction facingDirection)		// handles the players facing direction when entering a new room
{
	int posX = Hero->CurrentTile->posX;
	int posY = Hero->CurrentTile->posY;

	bool doLoad = false;		// whether we need to load a new room
	if (facingDirection == Direction::North)
	{
		if (currentOverlandY > 0)
		{
			doLoad = true;
			currentOverlandY--;		// move north on the overland map
			posY = roomHeight - 1;		// set the player's position to the bottom of the new room
			std::cout << "moved north" << std::endl;		// little debug message just for me :)
		}
	}
	else if (facingDirection == Direction::East)
	{
		if (currentOverlandX < overlandWidth - 1)
		{
			doLoad = true;
			currentOverlandX++;
			posX = 0;
			std::cout << "moved east" << std::endl;
		}
	}
	else if (facingDirection == Direction::South)
	{
		if (currentOverlandY < overlandHeight - 1)
		{
			doLoad = true;
			currentOverlandY++;
			posY = 0;
			std::cout << "moved south" << std::endl;
		}
	}
	else if (facingDirection == Direction::West)
	{
		if (currentOverlandX > 0)
		{
			doLoad = true;
			currentOverlandX--;
			posX = roomWidth - 1;
			std::cout << "moved west" << std::endl;
		}
	}

	if (doLoad)
	{
		LoadRoom(currentOverlandX, currentOverlandY, false, posX, posY);		// load the new room
	}
}


void DungeonGame::InitGrid()
{
	int index = 0;

	for (int x = 0; x < roomWidth; x++)
	{
		for (int y = 0; y < roomHeight; y++)
		{
			Tile* tile = &Tiles[x][y];
			tile->ID = index;
			tile->SetPosition(x, y);

			// NOTE: Used AI for a good portion below this point, but I roughly understand parts of it.

			// Sets if edge
			if (y == 0)
			{
				tile->SetIsEdge(Direction::North);
			}
			else if (y == roomHeight - 1)
			{
				tile->SetIsEdge(Direction::South);
			}
			if (x == roomWidth - 1)
			{
				tile->SetIsEdge(Direction::East);
			}
			else if (x == 0)
			{
				tile->SetIsEdge(Direction::West);
			}

			// creates a rectangle to represent the tile's position and size
			SDL_FRect r;
			r.x = x * tileSizeX;
			r.y = y * tileSizeY;
			r.w = tileSizeX;
			r.h = tileSizeY;

			tile->Rect = r; // assigns the rectangle to the tile's Rect property

			index++;	// increments the index for the next tile
		}
	}

	// connects neighbours
	for (int x = 0; x < roomWidth; x++)
	{
		for (int y = 0; y < roomHeight; y++)
		{
			Tile* tile = &Tiles[x][y];
			// North neighbour
			if (y > 0)
			{
				tile->SetNeighbour(Direction::North, Tiles[x][y - 1], false);
			}
			// East neighbour
			if (x < roomWidth - 1)
			{
				tile->SetNeighbour(Direction::East, Tiles[x + 1][y], false);
			}
			// South neighbour
			if (y < roomHeight - 1)
			{
				tile->SetNeighbour(Direction::South, Tiles[x][y + 1], false);
			}
			// West neighbour
			if (x > 0)
			{
				tile->SetNeighbour(Direction::West, Tiles[x - 1][y], false);
			}
		}
	}
}


void DungeonGame::InitOverland()		// the previous statement about AI was half true, this part I actually wrote myself
{
	for (int x = 0; x < overlandWidth; x++)
	{
		for (int y = 0; y < overlandHeight; y++)
		{
			// chosing a random room to select from
			int roomMax = std::size(roomFiles);
			int randomIndex = rand() % roomMax;		// random index between 0 and roomMax - 1
			overland[x][y] = randomIndex;		// assigns the random room index to the overland layout
		}
	}
}

void DungeonGame::RefreshVisuals()		// Back to AI here, this was a bit difficult for me
{

	// looks through grid, updates the rects list to reflect new room?

	int index = 0;
	for (int x = 0; x < roomWidth; x++)
	{
		for (int y = 0; y < roomHeight; y++)
		{
			if (Tiles[x][y].GetWalkable())
			{
				int texMax = 7;		// number of floor textures
				int randomIndex = rand() % texMax;		// random index between 0 and texMax - 1

				if (rand() % 10 <= 2)
				{
					Tiles[x][y].Texture = tileSetA[randomIndex];
				}
				else
				{
					Tiles[x][y].Texture = tileSetA[0];		// default floor texture
				}
			}

			else // if it isn't walkable
			{
				Tiles[x][y].Texture = texture_cantWalk;		// set to "can't walk" texture
			}

			index++;		// increments the index for the next tile
		}
	}
}

Tile* DungeonGame::FindNeighbour(int x, int y, Direction dir)		// Finds the neighbouring tile in a given direction
{
	// Finds the neighbour based on direction, returns nullptr if none found
	if (dir == Direction::North)
	{
		if (y > 0)
		{
			return &Tiles[x][y - 1];
		}
	}
	else if (dir == Direction::East)
	{
		if (x < roomWidth - 1)
		{
			return &Tiles[x + 1][y];
		}
	}
	else if (dir == Direction::South)
	{
		if (y < roomHeight - 1)
		{
			return &Tiles[x][y + 1];
		}
	}
	else if (dir == Direction::West)
	{
		if (x > 0)
		{
			return &Tiles[x - 1][y];
		}
	}

	return nullptr;		// no neighbour found
}

bool DungeonGame::IsTileFree(Tile* tile)		// checks if a tile is free
{
	// For now, we just check if the tile is walkable
	return tile->GetWalkable();
}

MoveResult DungeonGame::MoveAttempt(GameCharacter& character, Direction dir)		// attempts to move a character in a direction
{
	return MoveResult();
}

void DungeonGame::HandleMoveDirection(GameCharacter& character, Direction dir)		// handles moving a character in a direction
{
	if (character.CanMoveBetweenRooms())
	{
		// Handle room transitions here
		Tile* currentTile = character.CurrentTile;
		if (currentTile->GetIsEdge() == dir)
		{
			EnteringNewRoom(dir);		// tries entering new room
			return;
		}
	}

	auto result = MoveAttempt(character, dir);

	if (result.GetAction() == MoveResultAction::MoveOK)
	{
		CharacterMovedToTile(character, result.GetTile());		// moves character to new tile
	}
	else if (result.GetAction() == MoveResultAction::Fight)
	{
		// Not really sure what to do here for fighting but I don't think it's needed yet
	}
}

void DungeonGame::CharacterMovedToTile(GameCharacter& character, Tile* newTile)
{
	// Update character's position and current tile
	character.Rect.x = newTile->posX * tileSizeX;
	character.Rect.y = newTile->posY * tileSizeY;
	character.Rect.w = tileSizeX;
	character.Rect.h = tileSizeY;
	character.CurrentTile = newTile;

	// Probably put pickup effects here if they're on the tile
}




/*const int numRoomsX = 10;
const int numRoomsY = 10;

int DungeonLayout[numRoomsX][numRoomsY];

void RandomizeDungeon()
{
	for (int x = 0; x < numRoomsX; x++)
	{
		for (int y = 0; y < numRoomsY; y++)
		{
			DungeonLayout[x][y] = RandomNum();
		}
	}
}*/