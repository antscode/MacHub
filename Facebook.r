#include "Dialogs.r"

resource 'DLOG' (129, purgeable) {
	{ 0, 0, 124, 340 },
	movableDBoxProc,
	visible,
	goAway,
	0,
	129,
	"",
	centerMainScreen
};

data 'dctb' (129, purgeable) {
   $"0000 0000 0000 FFFF"
};

resource 'DITL' (129, purgeable) {
	{
		{ 90, 340-170, 90+20, 340-110 },
		Button { enabled, "Cancel" };

		{ 90, 340-10-80-4, 90+20, 340-10-4 },
		Button { enabled, "Continue" };
	}
};

resource 'ALRT' (130, purgeable ) {
   { 0, 0, 110, 400 },
   130,
   {
      OK, visible, silent,
      OK, visible, silent,
      OK, visible, silent,
      OK, visible, silent
   },
   centerMainScreen
};

resource 'DITL' (130, purgeable) {
	{
		{ 80, 300, 80+20, 380 },
		Button { enabled, "OK" };

		{8, 72, 70, 380},
		StaticText { disabled, "It looks like you haven't connected MacHub to your ^0 account. Please ensure you follow all of the steps your smartphone before clicking Continue." };
	}
};

resource 'ALRT' (131, purgeable ) {
   { 0, 0, 110, 400 },
   131,
   {
      OK, visible, silent,
      OK, visible, silent,
      OK, visible, silent,
      OK, visible, silent
   },
   centerMainScreen
};

resource 'DITL' (131, purgeable) {
	{
		{ 76, 300, 76+20, 380 },
		Button { enabled, "OK" };

		{8, 72, 70, 380},
		StaticText { disabled, "Sorry, something went wrong.\r^0" };
	}
};