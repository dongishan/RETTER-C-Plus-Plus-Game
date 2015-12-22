#include "header.h"
#include "templates.h"
#include "Gxd01uMain.h"
#include "Gxd01uPlayer.h"
#include "Gxd01uBallA.h"
#include "Gxd01uBallB.h"
#include "Gxd01uScrollBg.h"
#include "TileManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "JPGImage.h"

using namespace std;

/*Declaring the number of object as a constant*/
const int NUM_OBJECTS = 5;

Gxd01uMain::Gxd01uMain()
	:BaseEngine(NUM_OBJECTS)
{
}

Gxd01uMain::~Gxd01uMain()
{
}

/*Overriding the base class method*/
int Gxd01uMain::GameInit()
{
	/*Initialising the variables*/
	highScore = 0;
	score = 0;
	
	/*Set the initial state to Game Opened*/
	m_oGameState = GAME_OPENED;
	
	/*Setting Background first*/
	SetupBackgroundBuffer();

	/*Updating the game state*/
	UpdateGameState(GAME_OPENED);

	return 0;
}

/*Handling game states*/
void Gxd01uMain::UpdateGameState(GAME_STATE gameState)
{
	/*Updating the game state to the current game state*/
	m_oGameState = gameState;

	/*Handling Game States*/
	switch (m_oGameState){
		/*Game Opened State*/
		/*This will be called as soon as the app opened*/
		case GAME_OPENED:
		{
			printf("\nGame Opened");
			/*Reading the highest score from the file*/
			char line[100];
			FILE *txtFile;
			txtFile = fopen("highScore.txt", "r");
			if (txtFile != NULL)
			{
				while (fgets(line, sizeof line, txtFile) != NULL)
				{
				}
				fclose(txtFile);
			}

			string highestScoreStr(line);
			/*Setting the value to the highscore*/
			if (!highestScoreStr.empty())
			{
				highScore = atoi(highestScoreStr.c_str());
			}
			printf("\nHighest Score Read -> %d", highScore);

		}	
		break;
		/*Game start state*/
		/*This will be called once the user pressed Start button*/
		case GAME_STARTED:
			printf("\nGame Started");
			/*Redraw the background*/
			SetupBackgroundBuffer();
			Redraw(true); // Force total redraw

			/*Draw score and time tiles*/
			DrawTiles();

			/*Drawing strings*/
			DrawStringsOnTop();

			/*Add the objects to the game*/
			InitialiseObjects();
			break;
		break;
		/*Game exit state*/
		/*This will be called when a user presses the Exit or Escape button*/
		case GAME_EXIT:
			printf("\nGame Exit");
			/*First updating the highscore*/
			UpdateHighScore();
			/*Exit the game*/
			SetExitWithCode(0);
		break;
		//Game over state
		case GAME_OVER:
			printf("\nGame Over");
			/*First updating the highscore*/
			UpdateHighScore();
		break;
		
		default:
		break;
	}/*End switch*/
}

void Gxd01uMain::UpdateHighScore(){
	/*Storing the current highscore in the file
	Store only if the highscore is broken by the user*/
	if (score > highScore)
	{
		ofstream txtFile;
		txtFile.open("highScore.txt");
		/*Storing to the file if the file opened successfully*/
		if (txtFile.is_open())
		{
			/*Writing the score to the file with an end of line appended to the end*/
			txtFile << score << endl;
			/*Closing the file after writing*/
			txtFile.close();
		}
	}
}
/*Overriding the BaseEngine class method*/
int Gxd01uMain::InitialiseObjects(void)
{
	/*Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it*/
	DrawableObjectsChanged();

	/*Destroy any existing objects*/
	DestroyOldObjects();

	/*Creating an vector*/
	CreateObjectArray(NUM_OBJECTS);

	/*No need to add NULL as a vector is used. Also no need to pass the index.
	But passing this to maintain the same finction decaration*/
	Gxd01uPlayer *pPlayer = new Gxd01uPlayer(this);
	/*Scrolling background.
	First scrollbg object is initialised with the start x position as 0
	Second scroll object has the start x position equal to the width of the screen.
	So when the bgs are sliding there will be no empty area.*/
	StoreObjectInArray(0, new Gxd01uScrollBg(this,0));
	StoreObjectInArray(1, new Gxd01uScrollBg(this, GetScreenWidth()));
	StoreObjectInArray(2, pPlayer);
	StoreObjectInArray(3, new Gxd01uBallA(this, pPlayer));
	StoreObjectInArray(4, new Gxd01uBallB(this, pPlayer));

	/*Returning the number of objects*/
	return NUM_OBJECTS;
}

void Gxd01uMain::SetupBackgroundBuffer()
{
	/*Setting the initial background color to blackk*/
	FillBackground(0x000000);

	/*Loading the bitmap image with SDL 2.0. Different background images for the below two states*/
	SDL_Surface *bg;
	if (m_oGameState == GAME_OPENED)
	{
		/*Adding the static background for the main page*/
		ImageData mainBg;
		mainBg.LoadImage("assets/bg.jpg");
		mainBg.RenderImage(GetBackground(), 0, 0, 0, 0, GetScreenWidth(), GetScreenHeight());
	}
}

/*Draw Score and time tiles*/
void Gxd01uMain::DrawTiles()
{
	/*Setting the tiles for the score and time background*/
	/*Number of tiles*/
	m_oTiles.SetSize(3, 1);
	/*Setting up the tiles*/
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 1; y++)
		{
			/*Setting the value of the tile at x and y*/
			if (x == 1)
			{
				m_oTiles.SetValue(x, y, 3);
			}
			else
			{
				m_oTiles.SetValue(x, y, 5);
			}
		}
	}

	/*Specifing initial x and y*/
	m_oTiles.SetBaseTilesPositionOnScreen(0, 0);
	/*Drawing the tiles from the inital position to the end*/
	m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 100, 0);
}

/*Updating score*/
void Gxd01uMain::UpdateScore()
{
	score++;
	DrawStringsOnTop();
}

/*Override to add a node at specified point*/
void Gxd01uMain::MouseDown(int iButton, int iX, int iY)
{
	/*If the game state is Game Opened then handle the Start and Exit events*/
	if (m_oGameState == GAME_OPENED)
	{	
		/*Start button*/
		if ((iX > 340 && iX < 475) 
			&& (iY > 240 && iY < 275))
		{
			UpdateGameState(GAME_STARTED);
		}/*Exit button*/
		else if ((iX > 340 && iX < 475)
				&& (iY > 295 && iY < 330))
		{
			UpdateGameState(GAME_EXIT);
		}
	}
}

void Gxd01uMain::KeyDown(int iKeyCode)
{
	switch (iKeyCode){
		case SDLK_ESCAPE:
			/*Game paused*/
			UpdateGameState(GAME_EXIT);
			break;
		case SDLK_SPACE:
			break;
		default:
			break;
	}/*End switch*/
}

void Gxd01uMain::GameAction()
{
	/*If too early to act then do nothing*/
	if (!IsTimeToActWithSleep())
		return;

	/*Don't act for another 15 ticks*/
	SetTimeToAct(15);

	/*Tell all objects to update themselves*/
	UpdateAllObjects(GetTime());
}



/* Draw any string which should appear on top of moving objects - i.e. objects move behind these */
void Gxd01uMain::DrawStringsOnTop()
{
	/*Draw Strings if the game started*/
	if (m_oGameState == GAME_STARTED){
		stringstream scoreStream,highScoreStream,timeStream;

		scoreStream << "Score : " << score;
		DrawScreenString(75, 10, scoreStream.str().c_str(), 0xffffff, NULL);
		Redraw(true);

		highScoreStream << "High Score : " << highScore;
		DrawScreenString(294, 10, highScoreStream.str().c_str(), 0xffffff, NULL);
		Redraw(true);

		CopyBackgroundPixels(590/*X*/, 10/*Y*/, 10/*Width*/, 30/*Height*/);
		DrawBackgroundString(590, 10, "RETTER", 0xffffff, NULL);
		Redraw(true);
	}
}
