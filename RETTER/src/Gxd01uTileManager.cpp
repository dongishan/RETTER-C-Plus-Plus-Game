#include "header.h"
#include "Gxd01uTileManager.h"

const int TILE_WIDTH = 267;
const int TILE_HEIGHT = 50;

Gxd01uTileManager::Gxd01uTileManager()
	:TileManager(TILE_HEIGHT, TILE_WIDTH)//Setting the size of the tile
{
}

Gxd01uTileManager::~Gxd01uTileManager()
{
}


//Overriding the base class DrawTileAt method
void Gxd01uTileManager::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY){
	
	//Drawing the a background rectangle
	pEngine->DrawBackgroundRectangle(
		iStartPositionScreenX,
		iStartPositionScreenY,
		iStartPositionScreenX + GetTileWidth() - 1,
		iStartPositionScreenY + GetTileHeight() - 1, 
		pEngine->GetColour(GetValue(iMapX, iMapY)));
}

