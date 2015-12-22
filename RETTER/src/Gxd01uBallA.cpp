#include "header.h"
#include "templates.h"
#include "Gxd01uBallA.h"

Gxd01uBallA::Gxd01uBallA(Gxd01uMain *pEngine,Gxd01uPlayer *pPlayer)
	:Gxd01uBallBase(pEngine,pPlayer)
{
	// The ball coordinate will be the centre of the ball
	// Because we start drawing half the size to the top-left.
	m_iStartDrawPosX = -25;
	m_iStartDrawPosY = -25;
	// Record the ball size as both height and width
	m_iDrawWidth = 50;
	m_iDrawHeight = 50;
	// Just put it somewhere initially
	m_dX = m_iPreviousScreenX = m_iCurrentScreenX = m_iDrawWidth;
	m_dY = m_iPreviousScreenY = m_iCurrentScreenY = m_iDrawHeight;
	// Speed
	m_dSX = 2.5;
	m_dSY = 3.5;
	//Overriding the color variable for the base class
	iUiColor = 0xFF3366;
	//Setting the player object 
	p_OPlayer = pPlayer;
	// And make it visible
	SetVisible(true);
}

Gxd01uBallA::~Gxd01uBallA()
{
}
