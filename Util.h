#include <string> 
#include <MacTypes.h>
#include <Dialogs.h>

class Util
{
public:
	static char* PtoCStr(unsigned char *s);
	static unsigned char* CtoPStr(char *s);
	static double MicrosecondToDouble(register const UnsignedWide *epochPtr);
	static bool HasColour();
	static void DrawTextToWidth(std::string text, int width, int lineHeight, int newLineHPos = -1);
	static void FrameDefaultButton(DialogPtr dialog, short itemNo, bool active);
};