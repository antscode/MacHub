#include <Quickdraw.h>
#include <Lists.h>
#include <ToolUtils.h>
#include <Resources.h>
#include "IconListDef.h"


extern "C"
{






	pascal void MyLDEFInit(ListHandle theList)
	{

	}

	pascal void MyLDEFHighlight(Boolean selected, Rect* cellRect, Cell theCell, short dataOffset, short dataLen, ListHandle theList)
	{
		// use color highlighting if possible
		//BitClr((Ptr)LMGetHiliteMode(), pHiliteBit);
		MacInvertRect(cellRect); // highlight cell rectangle
	}

	pascal void MyLDEFDraw(Boolean selected, Rect* cellRect, Cell theCell, short dataOffset, short dataLen, ListHandle theList)
	{
		GrafPtr savedPort; // old graphics port
		RgnHandle savedClip; // old clip region
		PenState savedPenState; // old pen state



		PicHandle myPicture; // handle to a picture

		// set up the drawing environment
		GetPort(&savedPort); // remember the port
		MacSetPort((**theList).port); // set port to list's port
		savedClip = NewRgn(); // create new region
		GetClip(savedClip); // set region to clip region
		ClipRect(cellRect); // set clip region to cell 
		//  rectangle
		GetPenState(&savedPenState); // remember pen state
		PenNormal(); // use normal pen type
		// draw the cell if it contains data
		EraseRect(cellRect); // erase before drawing

		if (dataLen == sizeof(PicHandle))
		{
			// get handle to picture
			LGetCell(&myPicture, (short*)&dataLen, theCell, theList);

			// draw the picture
			DrawPicture(myPicture, cellRect);
		}




		// select the cell if necessary
		if (selected) //  highlight cell
		{
			MyLDEFHighlight(selected, cellRect, theCell, dataOffset,
				dataLen, theList);
		}

		// restore graphics environment
		MacSetPort(savedPort); // restore saved port
		SetClip(savedClip); // restore clip region
		DisposeRgn(savedClip); // free region memory
		SetPenState(&savedPenState); // restore pen state
	}



	pascal void MyLDEFClose(ListHandle theList)
	{
		Cell aCell; // cell in the list
		PicHandle myPicHandle; // handle stored as cell data
		int myDataLength; // length in bytes of cell data

		SetPt(&aCell, 0, 0);
		if (MacPtInRect(aCell, &(**theList).dataBounds))
		{
			do
			{
				// free memory only if cell's data is 4 bytes long
				myDataLength = sizeof(PicHandle);
				LGetCell(&myPicHandle, (short*)&myDataLength, aCell, theList);
				if (myDataLength == sizeof(PicHandle))
					KillPicture(myPicHandle);
			} while (LNextCell(TRUE, TRUE, &aCell, theList));
		}
	}

	pascal void MyLDEF(short message, Boolean selected, Rect* cellRect, Cell theCell, short dataOffset, short dataLen, ListHandle theList)
	{
		//RETRO68_RELOCATE();
		//Retro68Relocate();
		//Retro68CallConstructors();

		switch (message)
		{
		case lInitMsg:
			MyLDEFInit(theList);
			break;
		case lDrawMsg:
			MyLDEFDraw(selected, cellRect, theCell, dataOffset, dataLen, theList);
			break;
		case lHiliteMsg:
			MyLDEFHighlight(selected, cellRect, theCell, dataOffset, dataLen, theList);
			break;
		case lCloseMsg:
			MyLDEFClose(theList);
			break;
		}

		//Retro68FreeGlobals();
	}



}