#include "Game.h"
#ifndef LINUX
#include <windows.h>
#endif


#ifndef LINUX
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main()
#endif
{
	IO mIO;
	int mScreenHeight = mIO.GetScreenHeight();

	// Figuros
	Pieces mPieces;

	// Zaidimo laukas
	Board mBoard (&mPieces, mScreenHeight);

	// Zaidimas
	Game mGame (&mBoard, &mPieces, &mIO, mScreenHeight);

	// Laikas
	unsigned long mTime1 = SDL_GetTicks();

	// Pagrindinis ciklas
	while (!mIO.IsKeyDown (SDLK_ESCAPE))
	{
		mIO.ClearScreen (); 		
		mGame.DrawScene ();			
		mIO.UpdateScreen ();		

		// Valdymas

		int mKey = mIO.Pollkey();

		switch (mKey)
		{
			case (SDLK_RIGHT): 
			{
				if (mBoard.IsPossibleMovement (mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
					mGame.mPosX++;
					break;
			}

			case (SDLK_LEFT): 
			{
				if (mBoard.IsPossibleMovement (mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
					mGame.mPosX--;	
				break;
			}

			case (SDLK_DOWN):
			{
				if (mBoard.IsPossibleMovement (mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
					mGame.mPosY++;	
				break;
			}

			case (SDLK_x):
			{
				// Patikrinti ar nera susidurymu
				while (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation)) { mGame.mPosY++; }
	
				mBoard.StorePiece (mGame.mPosX, mGame.mPosY - 1, mGame.mPiece, mGame.mRotation);

				mBoard.DeletePossibleLines ();

				if (mBoard.IsGameOver())
				{
					mIO.Getkey();
					exit(0);
				}

				mGame.CreateNewPiece();

				break;
			}

			case (SDLK_z):
			{
				if (mBoard.IsPossibleMovement (mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRotation + 1) % 4))
					mGame.mRotation = (mGame.mRotation + 1) % 4;

				break;
			}
		}

		// Vertikalus judejimas

		unsigned long mTime2 = SDL_GetTicks();

		if ((mTime2 - mTime1) > WAIT_TIME)
		{
			if (mBoard.IsPossibleMovement (mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
			{
				mGame.mPosY++;
			}
			else
			{
				mBoard.StorePiece (mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);

				mBoard.DeletePossibleLines ();

				if (mBoard.IsGameOver())
				{
					mIO.Getkey();
					exit(0);
				}

				mGame.CreateNewPiece();
			}

			mTime1 = SDL_GetTicks();
		}
	}

	return 0;
}
