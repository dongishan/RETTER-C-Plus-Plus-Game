#pragma once
#include "DisplayableObject.h"
#include "Gxd01uMain.h"

class Gxd01uPlayer :
	public DisplayableObject
{

private:
	Gxd01uMain *p_OEngine;

public:
	double m_dSX;
	double m_dSY;
	double m_dX;
	double m_dY;

	Gxd01uPlayer(Gxd01uMain *pEngine);
	~Gxd01uPlayer();
	void Draw();
	void DoUpdate(int iCurrentTimer);
	//Getters
	int Getm_dY();
	int Getm_dX();
	int GetPlayerWidth();
};

