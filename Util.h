#include <MacTypes.h>

class Util
{
public:
	static char* PtoCStr(unsigned char *s);
	static unsigned char* CtoPStr(char *s);
	static double MicrosecondToDouble(register const UnsignedWide *epochPtr);
	static bool HasColour();
};