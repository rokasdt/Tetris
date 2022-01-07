#ifndef _GAME_
#define _GAME_

#include "Board.h"
#include "Pieces.h"
#include "IO.h"
#include <time.h>


#define WAIT_TIME 700			// Laikas per kuri figura pajuda vienu bloku zemyn


class Game
{
public:

	Game			(Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight);

	void DrawScene ();
	void CreateNewPiece ();

	int mPosX, mPosY;				// Figuros pozicija
	int mPiece, mRotation;			// Figura ir jos rotacija

private:

	int mScreenHeight;				// Ekrano ilgis
	int mNextPosX, mNextPosY;		// Sekancios figuros pozicija
	int mNextPiece, mNextRotation;	// Sekanti figura ir jos rotacija

	Board *mBoard;
	Pieces *mPieces;
	IO *mIO;

	int GetRand (int pA, int pB);
	void InitGame();
	void DrawPiece (int pX, int pY, int pPiece, int pRotation);
	void DrawBoard ();
};

#endif 
