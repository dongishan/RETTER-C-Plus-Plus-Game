#pragma once
#include "BaseEngine.h"
#include "TileManager.h"
#include "Gxd01uTileManager.h"

class Gxd01uMain :
	public BaseEngine
{

public:
	/*Enum to controll the game states*/
	enum GAME_STATE{
		GAME_STARTED,
		GAME_OPENED,
		GAME_EXIT,
		GAME_OVER
	};

	Gxd01uMain();
	~Gxd01uMain();
	
	bool isGameOver = false;

	int score, highScore;

	/*Updating score*/
	void UpdateScore();

	/*Handling game states*/
	void UpdateGameState(GAME_STATE gameState);

private:
	Gxd01uTileManager m_oTiles;
	GAME_STATE m_oGameState;

	int GameInit();
	void SetupBackgroundBuffer();
	/*Drawing the score, highscore and time tiles*/
	void DrawTiles();
	void KeyDown(int iKeyCode);
	int InitialiseObjects();

	/*Updating the highscore and storing in a file*/
	void UpdateHighScore();
	/*Handling mouse pressed*/
	void MouseDown(int iButton, int iX, int iY);
	/*The game logic - move things and change the state if necessary.
	Must call Redraw(true/false) if anything changes that shows on the screen.
	*/
	virtual void GameAction();

	/*Drawing strings on top of moving objects*/
	void DrawStringsOnTop();
};

