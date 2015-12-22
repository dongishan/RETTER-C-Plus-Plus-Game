#pragma once
#include "DisplayableObject.h"
#include "Gxd01uBallBase.h"
#include "Gxd01uMain.h"
#include "Gxd01uPlayer.h"

class Gxd01uBallBase :
	public DisplayableObject
{

private:
	Gxd01uMain *p_OEngine;

protected:
	int iUiColor;
	double m_dSX;
	double m_dSY;
	double m_dX;
	double m_dY;
	Gxd01uPlayer *p_OPlayer;
	
public:
	Gxd01uBallBase(Gxd01uMain *pEngine, Gxd01uPlayer *pPlayer);
	~Gxd01uBallBase();
	void Draw();
	void DoUpdate(int iCurrentTimer);

};

