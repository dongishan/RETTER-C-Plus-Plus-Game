#pragma once
#include "Gxd01uMain.h"
#include "Gxd01uBallBase.h"
#include "Gxd01uPlayer.h"

class Gxd01uBallA :
	public Gxd01uBallBase //Extending the base class
{
public:
	Gxd01uBallA(Gxd01uMain *pEngine,Gxd01uPlayer *pPlayer);
	~Gxd01uBallA();
};

