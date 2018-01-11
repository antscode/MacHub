

extern "C"
{
	pascal void MyLDEF(short message, Boolean selected, Rect* cellRect, Cell theCell, short dataOffset, short dataLen, ListHandle theList);
	pascal void MyLDEFInit(ListHandle theList);
	pascal void MyLDEFDraw(Boolean selected, Rect* cellRect, Cell theCell, short dataOffset, short dataLen, ListHandle theList);
	pascal void MyLDEFHighlight(Boolean selected, Rect* cellRect, Cell theCell, short dataOffset, short dataLen, ListHandle theList);
	pascal void MyLDEFClose(ListHandle theList);
}


