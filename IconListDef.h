extern "C"
{
	pascal void IconListDef(short message, Boolean selected, Rect* cellRect, Cell cell, short dataOffset, short dataLen, ListHandle list);
	pascal void DrawCell(Boolean selected, Rect* cellRect, Cell cell, short dataOffset, short dataLen, ListHandle list);
	pascal void Dispose(ListHandle list);
}

struct ListIcon
{
	short recourceId;
	Str255 label;
};
