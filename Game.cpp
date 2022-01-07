#ifndef LINUX
#include <windows.h>
#endif
#include "Game.h"


Game::Game(Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight) 
{
	mScreenHeight = pScreenHeight;

	mBoard = pBoard;
	mPieces = pPieces;
	mIO = pIO;

	InitGame ();
}


/*
Gauti atsitiktini skaiciu
pA - pirmas skaicius
pB - antras skaicius
*/ 
int Game::GetRand (int pA, int pB)
{
	return rand () % (pB - pA + 1) + pA;
}


// Pradiniai zaidimo parametrai
void Game::InitGame()
{
	// Atsitiktiniai skaiciai
	srand ((unsigned int) time(NULL));

	// Pirma figura
	mPiece			= GetRand (0, 6);
	mRotation		= GetRand (0, 3);
	mPosX 			= (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition (mPiece, mRotation);
	mPosY 			= mPieces->GetYInitialPosition (mPiece, mRotation);

	// Sekanti figura
	mNextPiece 		= GetRand (0, 6);
	mNextRotation 	= GetRand (0, 3);
	mNextPosX 		= BOARD_WIDTH + 5;
	mNextPosY 		= 5;	
}



// Sukurti atsitiktine figura
void Game::CreateNewPiece()
{
	// Nauja figura
	mPiece			= mNextPiece;
	mRotation		= mNextRotation;
	mPosX 			= (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition (mPiece, mRotation);
	mPosY 			= mPieces->GetYInitialPosition (mPiece, mRotation);

	// Sekanti figura
	mNextPiece 		= GetRand (0, 6);
	mNextRotation 	= GetRand (0, 3);
}



/*
Sukurti figura
pX - horizontali pozicija
pY - vertikali pozicija
pPiece - figura
pRotation - rotacija
*/
void Game::DrawPiece (int pX, int pY, int pPiece, int pRotation)
{
	color mColor;				// Bloko spalva 

	// Gauti kuriamo bloko pozicija
	int mPixelsX = mBoard->GetXPosInPixels (pX);
	int mPixelsY = mBoard->GetYPosInPixels (pY);

	for (int i = 0; i < PIECE_BLOCKS; i++)
	{
		for (int j = 0; j < PIECE_BLOCKS; j++)
		{
			// Gauti bloko rusi ir pasirinkti reikiama spalva
			switch (mPieces->GetBlockType (pPiece, pRotation, j, i))
			{
				case 1: mColor = GREEN; break;	// Paprastiem blokam
				case 2: mColor = BLUE; break;	// Blokui aplink kuri sukasi figura
			}
			
			if (mPieces->GetBlockType (pPiece, pRotation, j, i) != 0)
				mIO->DrawRectangle	(mPixelsX + i * BLOCK_SIZE, 
									mPixelsY + j * BLOCK_SIZE, 
									(mPixelsX + i * BLOCK_SIZE) + BLOCK_SIZE - 1, 
									(mPixelsY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, 
									mColor);
		}
	}
}



/*
Sukurti zaidimo lauka
Nupiesia dvi linijas kaip lauko ribas
*/

void Game::DrawBoard ()
{
	// Apskaiciuoti lauko ribas 
	int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
	int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
	int mY = mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT);	

	mIO->DrawRectangle (mX1 - BOARD_LINE_WIDTH, mY, mX1, mScreenHeight - 1, BLUE);
	mIO->DrawRectangle (mX2, mY, mX2 + BOARD_LINE_WIDTH, mScreenHeight - 1, BLUE);

	mX1 += 1;
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{	
			// Patikrinti ar blokas uzpildytas, jei taip, tai sukurti ji
			if (!mBoard->IsFreeBlock(i, j))	
				mIO->DrawRectangle (	mX1 + i * BLOCK_SIZE, 
										mY + j * BLOCK_SIZE, 
										(mX1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1, 
										(mY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, 
										RED);
		}
	}	
}



// Sukurti scena ir visus jos objektus
void Game::DrawScene ()
{
	DrawBoard ();													
	DrawPiece (mPosX, mPosY, mPiece, mRotation);					// Dabartine figura
	DrawPiece (mNextPosX, mNextPosY, mNextPiece, mNextRotation);	// Sekanti figura
}
