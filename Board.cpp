#include "Board.h"

Board::Board (Pieces *pPieces, int pScreenHeight)
{
	// Ekrano ilgis
	mScreenHeight = pScreenHeight;

	mPieces = pPieces;

	InitBoard();
}



void Board::InitBoard()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
		for (int j = 0; j < BOARD_HEIGHT; j++)
			mBoard[i][j] = POS_FREE;
}


/*
Talpinti figure lauke uzpildant blokus

pPiece - figura
pRotation - figuros rotacija
pX - horizontali bloku pozicija
pY - vertikali bloku pozicija
*/

void Board::StorePiece (int pX, int pY, int pPiece, int pRotation)
{
	// Talpinti kiekviena figuros bloka zaidimo lauke
	for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++)
	{
		for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++)
		{	
			if (mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0)		
				mBoard[i1][j1] = POS_FILLED;	
		}
	}
}




//Patikrinti ar zaidimas pasibaige nes figura pasieke auksciausia ribu pozicija

bool Board::IsGameOver()
{
	//Jeigu virsutine eilute turi bloku, zaidimas pasibaigia
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		if (mBoard[i][0] == POS_FILLED) return true;
	}

	return false;
}


 
//Istrinti eilute pastumiant visas eilutes zemyn								

void Board::DeleteLine (int pY)
{
	for (int j = pY; j > 0; j--)
	{
		for (int i = 0; i < BOARD_WIDTH; i++)
		{
			mBoard[i][j] = mBoard[i][j-1];
		}
	}	
}


								
//Istrinti visas eilutes kurios turi buti pasalintos

void Board::DeletePossibleLines ()
{
	for (int j = 0; j < BOARD_HEIGHT; j++)
	{
		int i = 0;
		while (i < BOARD_WIDTH)
		{
			if (mBoard[i][j] != POS_FILLED) break;
			i++;
		}

		if (i == BOARD_WIDTH) DeleteLine (j);
	}
}



// true jeigu blokas tuscias, false jeigu uzpildytas

bool Board::IsFreeBlock (int pX, int pY)
{
	if (mBoard [pX][pY] == POS_FREE) return true; else return false;
}



/* 
Horizontali bloko pozicija pikseliais
pPos - horizontali bloko pozicija lauke
*/

int Board::GetXPosInPixels (int pPos)
{
	return  ( ( BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) ) + (pPos * BLOCK_SIZE) );
}


/*
Vertikali bloko pozicija pikseliais
pPos - horizontali bloko pozicija lauke
*/
int Board::GetYPosInPixels (int pPos)
{
	return ( (mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (pPos * BLOCK_SIZE) );
}


/* 
Patikrinti ar figura tilps tarp ribu
True jeigu judejimas imanomas, false jei me

pPiece - figura
pRotation - figuros rotacija
pX - horizontali bloku pozicija
pY - vertikali bloku pozicija

*/
bool Board::IsPossibleMovement (int pX, int pY, int pPiece, int pRotation)
{
	for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++)
	{
		for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++)
		{	
			// Patikrinti ar figura uz ribu
			if (	i1 < 0 			|| 
				i1 > BOARD_WIDTH  - 1	||
				j1 > BOARD_HEIGHT - 1)
			{
				if (mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0)
					return 0;		
			}

			// Patikrinti ar figura liecia kita figura lauke
			if (j1 >= 0)	
			{
				if ((mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0) &&
					(!IsFreeBlock (i1, j1))	)
					return false;
			}
		}
	}

	// Nera susidurimu
	return true;
}
