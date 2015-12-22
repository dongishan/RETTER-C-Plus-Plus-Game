#include "header.h"
#include "templates.h"
#include "Gxd01uBallB.h"

Gxd01uBallB::Gxd01uBallB(Gxd01uMain *pEngine,Gxd01uPlayer *pPlayer)
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
	m_dX = m_iPreviousScreenX = m_iCurrentScreenX = 750;
	m_dY = m_iPreviousScreenY = m_iCurrentScreenY = 50;
	// Speed
	m_dSX = 5.5;
	m_dSY = 6.5;
	//Overriding the color variable for the base class
	iUiColor = 0xFFFF00;
	//Setting the player object 
	p_OPlayer = pPlayer;
	// And make it visible
	SetVisible(true);
}

Gxd01uBallB::~Gxd01uBallB()
{
}
