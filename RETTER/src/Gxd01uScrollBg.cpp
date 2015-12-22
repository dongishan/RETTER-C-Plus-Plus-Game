#include "header.h"
#include "templates.h"
#include "Gxd01uScrollBg.h"

Gxd01uScrollBg::Gxd01uScrollBg(Gxd01uMain *pEngine, int m_iStartPosX)
	:DisplayableObject(pEngine)
{
	p_OEngine = pEngine;

	m_iStartDrawPosX = m_iStartPosX;
	m_iStartDrawPosY = 50;
	
	m_iDrawWidth = GetEngine()->GetScreenWidth();
	m_iDrawHeight = GetEngine()->GetScreenHeight();
	
	m_dX = m_iPreviousScreenX = m_iCurrentScreenX = m_iDrawWidth;
	m_dY = m_iPreviousScreenY = m_iCurrentScreenY = m_iDrawHeight;
	
	m_iCurrentScreenX = m_iStartDrawPosX;
	m_iCurrentScreenY = m_iStartDrawPosY;
	
	// Load the image file into an image object - at the normal size
	bool imageLoaded = bgImage.LoadImage("assets/fire_bg_full.jpg");
	if (!imageLoaded){
		printf("Background image not loaded!!!!");
	}

	SetVisible(true);
}


Gxd01uScrollBg::~Gxd01uScrollBg()
{
}

void Gxd01uScrollBg::Draw()
{
	/*Render the image to the surface*/
	bgImage.RenderImage(GetEngine()->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, m_iDrawWidth, m_iDrawHeight-50);
	
	/* This will store the position at which the object was drawn
	 so that the background can be drawn over the top.
	 This will then remove the object from the screen.*/
	StoreLastScreenPositionForUndraw();

}

void Gxd01uScrollBg::DoUpdate(int iCurrentTimer)
{	
	/*Update if the game is not over*/
	if (!p_OEngine->isGameOver){
		/*Width of the scroll bg is same as the width of the screen.
		If the scroll bg current x position is equal to the -(width of the screen) that means the scroll bg's x+width position is at the x = 0.
		If so we set the scroll bg x postion to width of the screen so it will appear in the screen again.
		Two scroll bgs are used to show the scroll background. These are initialised from the Gxd01uMain class*/
		if (m_iCurrentScreenX == (-1 * GetEngine()->GetScreenWidth())){
			m_iCurrentScreenX = GetEngine()->GetScreenWidth();
		}
		/*Update the x value to slide the bg horizontally*/
		m_iCurrentScreenX -= 2;
		RedrawObjects();
	}
}


