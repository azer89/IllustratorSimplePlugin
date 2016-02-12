#include "CustomEdit.h"

namespace
{

	/* Initialize static variables */
	static WNDPROC defWndProc = NULL;
	static bool	registered = false;

	/* Declaration */
	LRESULT CALLBACK CustomEditWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void RegisterWithOS(HINSTANCE inAppInstance)
	{
		if(!registered)
		{
			WNDCLASSEX customEditClass;
			customEditClass.cbSize = sizeof(customEditClass);

			::GetClassInfoEx(NULL, L"EDIT", &customEditClass);

			customEditClass.hInstance = inAppInstance;
			customEditClass.lpszClassName = CustomEditClassName;
			defWndProc = customEditClass.lpfnWndProc;
			customEditClass.lpfnWndProc = CustomEditWndProc;

			::RegisterClassEx(&customEditClass);

			registered = true;
		}
	}


	LRESULT CALLBACK CustomEditWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch(msg)
		{
			case WM_KEYDOWN:
			{
				/* Process only TAB and SHIFT + TAB */
				if( wParam == VK_TAB )
				{
					HWND parent = ::GetParent(hWnd);
					/* Poor implementation - Assumes that parent of edit knows about next focusable control */
					HWND nextFocusableItem = ::GetNextDlgTabItem(parent, hWnd, (::GetKeyState(VK_SHIFT) & 0x8000) != 0 ? true : false);
					if(nextFocusableItem)	::SetFocus(nextFocusableItem);
				
					/* Tell that we processed the message */
					return 0;
				}
			}
		}

		/* For all other messages call default window proc */
		return CallWindowProc(defWndProc, hWnd, msg, wParam, lParam);
	}

} /*  Anonymous namespace */


HWND CustomEdit::CreateCustomEdit(DWORD inExStyle, LPCTSTR inWindowName, DWORD inStyle, int x, int y, int inWidth, int inHeight, 
									HWND inParent, HMENU inMenu, HINSTANCE inHinstance, LPVOID inLpParam)
{
	if(!registered)
	{
		RegisterWithOS(inHinstance);
	}

	return ::CreateWindowEx(	inExStyle
						,CustomEditClassName
						,inWindowName
						,inStyle
						,x
						,y
						,inWidth
						,inHeight
						,inParent
						,inMenu
						,inHinstance
						,inLpParam
						);
	
}