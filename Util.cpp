#include <string.h>
#include <stdio.h>
#include <Gestalt.h>
#include <QuickDraw.h>
#include <FixMath.h>
#include "Util.h"

#define kTwoPower32 (4294967296.0)      /* 2^32 */

char* Util::PtoCStr(unsigned char *s)
{
	int theLen;
	int t;

	theLen = s[0];

	for (t = 0; t<theLen; t++)
		s[t] = s[t + 1];

	s[theLen] = '\0';

	return (char *)s;
}

unsigned char* Util::CtoPStr(char *s)
{
	int theLen;
	int t;

	theLen = strlen(s);

	for (t = theLen; t >= 1; t--)
		s[t] = s[t - 1];

	s[0] = (char)theLen;

	return (unsigned char *)s;
}

unsigned char* Util::StrToPStr(std::string str)
{
	char* s = (char*)str.c_str();

	int theLen;
	int t;

	theLen = strlen(s);

	for (t = theLen; t >= 1; t--)
		s[t] = s[t - 1];

	s[0] = (char)theLen;

	return (unsigned char *)s;
}


// From: http://www.mactech.com/articles/develop/issue_26/minow.html
double Util::MicrosecondToDouble(register const UnsignedWide *epochPtr)
{
	register double result;

	result = (((double)epochPtr->hi) * kTwoPower32) + epochPtr->lo;
	return (result);
}

bool Util::HasColour()
{
	OSErr err;
	long response;

	err = Gestalt(gestaltQuickdrawVersion, &response);

	if (err == noErr)
	{
		return (response != gestaltOriginalQD);
	}

	return false;
}

void Util::DrawTextToWidth(std::string text, int width, int lineHeight, int newLineHPos)
{
	const char* cText = text.c_str();
	long textLen = strlen(cText);
	long textStart = 0;
	long textOffset = 1;
	Fixed widthPixels = Long2Fix(width);
	Fixed textWidth;
	StyledLineBreakCode ans;
	Ptr textPtr;
	Point curPos;

	GetPen(&curPos);

	if (newLineHPos > -1)
	{
		curPos.h = newLineHPos;
	}

	while (true)
	{
		textPtr = (char*)&cText[textStart];
		textWidth = widthPixels;

		ans = StyledLineBreak(textPtr, textLen, 0, textLen, 0, &textWidth, &textOffset);

		MacDrawText(cText, textStart, textOffset);

		if (ans == smBreakOverflow)
		{
			break;
		}

		textStart += textOffset;
		textLen -= textOffset;
		textOffset = 0; // Always 0 after first call

		curPos.v += lineHeight;
		MoveTo(curPos.h, curPos.v);
	}
}

void Util::FrameDefaultButton(DialogPtr dialog, short itemNo, bool active)
{
	DialogItemType type;
	ControlRef control;
	Handle itemH;
	Rect box;

	GetDialogItem(dialog, itemNo, &type, &itemH, &box);
	InsetRect(&box, -4, -4);
	PenSize(3, 3);

	if (!active)
	{
		RGBColor color;
		PixPatHandle pp;

		color.red = 0x8000;
		color.green = 0x8000;
		color.blue = 0x8000;

		pp = NewPixPat();
		MakeRGBPat(pp, &color);
		PenPixPat(pp);
		FrameRoundRect(&box, 16, 16);
		DisposePixPat(pp);
		PenNormal();
		HiliteControl((ControlRef)itemH, 255);
	}
	else
	{
		FrameRoundRect(&box, 16, 16);
		HiliteControl((ControlRef)itemH, 0);
	}
}

void Util::DebugStr(std::string msg)
{
	FILE *fp;
	fp = fopen("Mac HD (68K):log.txt", "a");

	if (fp)
	{
		fprintf(fp, msg.c_str());
		fflush(fp);
	}

	fclose(fp);
}