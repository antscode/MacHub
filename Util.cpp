#include <string.h>
#include <Gestalt.h>
#include <QuickDraw.h>

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