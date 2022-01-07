#ifndef _BOARD_
#define _BOARD_

#include "Pieces.h"

#define BOARD_LINE_WIDTH 6			// Ribu liniju dydis
#define BLOCK_SIZE 16				// Kiekvieno bloko dydis
#define BOARD_POSITION 320			// Centrine zaidimo lauko pozicija
#define BOARD_WIDTH 10				// Zaidimo lauko plotis
#define BOARD_HEIGHT 20				// Zaidimo lauko ilgis
#define MIN_VERTICAL_MARGIN 20		// Minimalios vertikalios ribos	
#define MIN_HORIZONTAL_MARGIN 20	// Minimalios horizontalios ribos
#define PIECE_BLOCKS 5				// Bloku matricos dydis



class Board
{
public:

	Board						(Pieces *pPieces, int pScreenHeight);

	int GetXPosInPixels			(int pPos);
	int GetYPosInPixels			(int pPos);
	bool IsFreeBlock			(int pX, int pY);
	bool IsPossibleMovement		(int pX, int pY, int pPiece, int pRotation);
	void StorePiece				(int pX, int pY, int pPiece, int pRotation);
	void DeletePossibleLines	();
	bool IsGameOver				();

private:

	enum { POS_FREE, POS_FILLED };			// POS_FREE - laisva pozicija lentoje; POS_FILLED - uzpildyta vieta lentoje
	int mBoard [BOARD_WIDTH][BOARD_HEIGHT];	// lenta kuri laiko figuras
	Pieces *mPieces;
	int mScreenHeight;

	void InitBoard();
	void DeleteLine (int pY);
};

#endif 
