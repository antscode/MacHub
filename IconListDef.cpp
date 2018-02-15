#include <Quickdraw.h>
#include <Lists.h>
#include <ToolUtils.h>
#include <Resources.h>
#include "IconListDef.h"

extern "C"
{
	pascal void IconListDef(short message, Boolean selected, Rect* cellRect, Cell cell, short dataOffset, short dataLen, ListHandle list)
	{
		switch (message)
		{
			case lDrawMsg:
			case lHiliteMsg:
				DrawCell(selected, cellRect, cell, dataOffset, dataLen, list);
				break;
			case lCloseMsg:
				Dispose(list);
				break;
		}
	}

	pascal void DrawCell(Boolean selected, Rect* cellRect, Cell cell, short dataOffset, short dataLen, ListHandle list)
	{
		const int cellWidth = 56;
		const int iconSize = 32;
		const int iconOffsetLeft = 12;
		const int iconOffsetTop = 5;

		if (dataLen == sizeof(ListIcon))
		{
			// Snapshot drawing environment
			GrafPtr savedPort;
			RgnHandle savedClip;
			PenState savedPenState;

			GetPort(&savedPort); 
			MacSetPort((**list).port);
			savedClip = NewRgn();
			GetClip(savedClip);
			ClipRect(cellRect);
			GetPenState(&savedPenState);

			PenNormal();
			EraseRect(cellRect);

			ListIcon listIcon;
			LGetCell(&listIcon, (short*)&dataLen, cell, list);

			Rect iconRect;
			MacSetRect(&iconRect, 
				cellRect->left + iconOffsetLeft, 
				cellRect->top + iconOffsetTop, 
				cellRect->left + iconOffsetLeft + iconSize,
				cellRect->top + iconOffsetTop + iconSize);

			IconTransformType transform = ttNone;
			short textMode = srcCopy;

			if (selected) 
			{
				transform = ttSelected;
				textMode = notSrcCopy;
			}

			// Draw the icon
			PlotIconID(&iconRect, kAlignNone, transform, listIcon.recourceId);

			// Draw the label
			TextFont(1);
			TextSize(9);

			int labelWidth = StringWidth((ConstStr255Param)listIcon.label);
			int startPos = (cellWidth - labelWidth) / 2;

			MoveTo(cellRect->left + startPos, cellRect->top + 47);

			TextMode(textMode);
			DrawString((ConstStr255Param)listIcon.label);
			
			// Restore graphics environment
			MacSetPort(savedPort);
			SetClip(savedClip);
			DisposeRgn(savedClip);
			SetPenState(&savedPenState);
			TextFont(0);
		}
	}

	pascal void Dispose(ListHandle list)
	{
		Cell cell;
		ListIcon listIcon;
		int dataLength;

		SetPt(&cell, 0, 0);
		if (MacPtInRect(cell, &(**list).dataBounds))
		{
			do
			{
				dataLength = sizeof(ListIcon);
				LGetCell(&listIcon, (short*)&dataLength, cell, list);
				if (dataLength == sizeof(ListIcon))
				{
					delete &listIcon;
				}
			} while (LNextCell(true, true, &cell, list));
		}
	}
}