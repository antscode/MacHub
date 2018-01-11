#include "Retro68.r"

type 'LDEF' {
	RETRO68_CODE_TYPE
};

resource 'LDEF' (128) {
	dontBreakAtEntry, $$read("IconListDef.flt");
};
