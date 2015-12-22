#pragma once
#include "Gxd01uMain.h"
#include "Gxd01uBallBase.h"
#include "Gxd01uPlayer.h"

class Gxd01uBallB :
	public Gxd01uBallBase //Extending the base class
{
public:
	Gxd01uBallB(Gxd01uMain *pEngine,Gxd01uPlayer *pPlayer);
	~Gxd01uBallB();
};