#include "header.h"
#include "templates.h"
#include "Gxd01uPlayer.h"

const int PLAYER_WIDTH = 150;
const int PLAYER_HEIGHT = 30;


Gxd01uPlayer::Gxd01uPlayer(Gxd01uMain *pEngine)
	:DisplayableObject(pEngine)
{
	p_OEngine = pEngine;
	// The ball coordinate will be the centre of the ball
	// Because we start drawing half the size to the top-left.
	m_iStartDrawPosX = -75;
	m_iStartDrawPosY = -15;
	// Record the ball size as both height and width
	m_iDrawWidth = PLAYER_WIDTH;
	m_iDrawHeight = PLAYER_HEIGHT;
	// Just put it somewhere initially
	m_dX = m_iPreviousScreenX = m_iCurrentScreenX = 400;
	m_dY = m_iPreviousScreenY = m_iCurrentScreenY = 555;
	// And make it visible
	SetVisible(true);
}


Gxd01uPlayer::~Gxd01uPlayer()
{
}

//Drawing the shape
void Gxd01uPlayer::Draw()
{
	GetEngine()->DrawRectangle(
		m_iCurrentScreenX - m_iDrawWidth / 2 + 1,
		m_iCurrentScreenY - m_iDrawHeight / 2 + 1,
		m_iCurrentScreenX + m_iDrawWidth / 2 - 1,
		m_iCurrentScreenY + m_iDrawHeight / 2 - 1,
		0x996600);

	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.
	// This will then remove the object from the screen.
	StoreLastScreenPositionForUndraw();
}

//Moving the player tile left to right
void Gxd01uPlayer::DoUpdate(int iCurrentTime){
	/*Update if the game is not over*/
	if (!p_OEngine->isGameOver){
		//Moving the player left if the player will be inside the screen
		if (GetEngine()->IsKeyPressed(SDLK_LEFT)){
			if (m_dX - 10 - (PLAYER_WIDTH / 2) > 0){
				m_dX -= 10;
			}
		}
		//Moving the player right if the player will be inside the screen
		if (GetEngine()->IsKeyPressed(SDLK_RIGHT)){
			if (m_dX + 10 + (PLAYER_WIDTH / 2) < 800){
				m_dX += 10;
			}
		}

		//Setting current position and redrawing the objects.
		m_iCurrentScreenX = m_dX;
		m_iCurrentScreenY = m_dY;
		// Ensure that the object gets redrawn on the display, if something changed
		RedrawObjects();
	}
}

//Getters
int Gxd01uPlayer::Getm_dY(){
	return m_dY;
}

int Gxd01uPlayer::Getm_dX(){
	return m_dX;
}

int Gxd01uPlayer::GetPlayerWidth(){
	return PLAYER_WIDTH;
}