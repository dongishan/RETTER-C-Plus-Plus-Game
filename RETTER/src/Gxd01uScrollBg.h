#pragma once
#include "DisplayableObject.h"
#include "Gxd01uMain.h"
#include "JPGImage.h"

class Gxd01uScrollBg :
	public DisplayableObject
{

private:
	Gxd01uMain *p_OEngine;
	ImageData bgImage;

public:
	Gxd01uScrollBg(Gxd01uMain *pEngine, int m_iStartPosX);
	~Gxd01uScrollBg();

	double m_dSX;
	double m_dSY;
	double m_dX;
	double m_dY;

	void Draw();
	void DoUpdate(int iCurrentTimer);
};


