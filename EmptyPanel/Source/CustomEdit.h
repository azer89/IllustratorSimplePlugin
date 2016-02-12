#ifndef __CUSTOMEDIT__
#define __CUSTOMEDIT__

#include "windows.h"
#include "winuser.h"

#define CustomEditClassName L"CustomEdit"

namespace CustomEdit
{
	HWND CreateCustomEdit(DWORD inExStyle,  LPCTSTR inWindowName, DWORD inStyle, int x, int y, int inWidth, int inHeight, 
									HWND inParent, HMENU inMenu, HINSTANCE inHinstance, LPVOID inLpParam);
}

#endif