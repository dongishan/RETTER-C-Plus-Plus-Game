#include "header.h"
#include "Gxd01uBallBase.h"

const int BALL_WIDTH = 50;
//Constructor will be override by the sub classes
Gxd01uBallBase::Gxd01uBallBase(Gxd01uMain *pEngine,Gxd01uPlayer *pPlayer)
	:DisplayableObject(pEngine)
{
	p_OEngine = pEngine;
}


Gxd01uBallBase::~Gxd01uBallBase()
{
}

//Drawing the shape
void Gxd01uBallBase::Draw()
{
	GetEngine()->DrawScreenOval(
		m_iCurrentScreenX - m_iDrawWidth / 2 + 1,
		m_iCurrentScreenY - m_iDrawHeight / 2 + 1,
		m_iCurrentScreenX + m_iDrawWidth / 2 - 1,
		m_iCurrentScreenY + m_iDrawHeight / 2 - 1,
		iUiColor);

	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.
	// This will then remove the object from the screen.
	StoreLastScreenPositionForUndraw();
}

// Called frequently, this should move the item
void Gxd01uBallBase::DoUpdate(int iCurrentTime){
	/*Update if the game is not over*/
	if (!p_OEngine->isGameOver){
		// Alter position for speed
		m_dX += m_dSX;
		m_dY += m_dSY;

		// Bouncing back when hit the edges of the screen
		if ((m_dX + m_iStartDrawPosX) < 0)
		{
			m_dX = -m_iStartDrawPosX;
			if (m_dSX < 0)
				m_dSX = -m_dSX;
		}

		if ((m_dX + m_iStartDrawPosX + m_iDrawWidth) > (GetEngine()->GetScreenWidth() - 1))
		{
			m_dX = GetEngine()->GetScreenWidth() - 1 - m_iStartDrawPosX - m_iDrawWidth;
			if (m_dSX > 0)
				m_dSX = -m_dSX;
		}

		if ((m_dY + m_iStartDrawPosY) < 0)
		{
			m_dY = -m_iStartDrawPosY;
			if (m_dSY < 0)
				m_dSY = -m_dSY;
		}

		//Collision with the player object and bounce back the balls
		if ((m_dY + m_iStartDrawPosY + m_iDrawHeight) > (p_OPlayer->Getm_dY() - 1))
		{
			if ((m_dX + (BALL_WIDTH/2)) >= (p_OPlayer->Getm_dX() - (p_OPlayer->GetPlayerWidth() / 2))
				&& (m_dX - (BALL_WIDTH/2)) <= (p_OPlayer->Getm_dX() + (p_OPlayer->GetPlayerWidth() / 2))){
				m_dY = p_OPlayer->Getm_dY() - 1 - m_iStartDrawPosY - m_iDrawHeight;
				if (m_dSY > 0){
					m_dSY = -m_dSY;
				}
				p_OEngine->UpdateScore();
			}
			else{
				//Game over
				p_OEngine->isGameOver = true;
				//Notifying the game engine class with Game Over state
				p_OEngine->UpdateGameState(Gxd01uMain::GAME_OVER);
			}
		}

		// Set current position
		m_iCurrentScreenX = (int)(m_dX + 0.5);
		m_iCurrentScreenY = (int)(m_dY + 0.5);

		// Ensure that the object gets redrawn on the display, if something changed
		RedrawObjects();
	}
}