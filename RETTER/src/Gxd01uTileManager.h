#pragma once

#include "tilemanager.h"

class Gxd01uTileManager:
	public TileManager
{
public:
	Gxd01uTileManager();
	~Gxd01uTileManager();

	//Overriding the base class DrawTileAt method
	virtual void DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY);
};

