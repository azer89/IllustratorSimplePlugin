//========================================================================================
//  
//  $File: //ai/mainline/devtech/sdk/public/samplecode/EmptyPanel/source/EmptyPanelPlugin.cpp $
//
//  $Revision: #2 $
//
//  Copyright 1987 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

/**
* Reza Adhitya Saputra
* radhitya@uwaterloo.ca
*/


/**
 * Some important functions:
 *     GoMenuItem
 *     StartupPlugin
 *     SHutdownPlugin
 */

#ifdef MAC_ENV
#include <Cocoa/Cocoa.h>
#include "CalcController.h"
#include "BarController.h"
#endif

#ifdef WIN_ENV
#include <WindowsX.h>
#include "CustomEdit.h"
#endif

#include "IllustratorSDK.h"
#include "EmptyPanelPlugin.h"
#include "EmptyPanelPluginSuites.h"

// moved from EmptyPanelPluginSuites
#include "IllustratorSDK.h"
#include "Suites.hpp"
//

//
#include "SDKDef.h"
#include "SDKAboutPluginsHelper.h"
//

#include "EmptyPanleID.h"

//QT
#include <QTextEdit>
#include <iostream>
#include "myqtui.h"
#include <QtWidgets/QApplication>


#define bufMax 1024
#define controlBarHeight	40
#define controlBarWidth		800
#define controlBarWidthMin	50
#define controlBarWidthMax	1200

extern "C" SPBasicSuite*  sSPBasic;

#ifdef MAC_ENV
NSView* nibView = nil;
NSView* controlPanelNibView = nil;
#endif

Plugin *AllocatePlugin(SPPluginRef pluginRef)
{
	return new EmptyPanelPlugin(pluginRef);
}

void FixupReload(Plugin *plugin)
{
	EmptyPanelPlugin::FixupVTable( static_cast<EmptyPanelPlugin*>( plugin ) );
}

EmptyPanelPlugin::EmptyPanelPlugin(SPPluginRef pluginRef)
	: Plugin(pluginRef),
	//fPanel(NULL),
	//hDlg(NULL),
	my_qt_app(0),
	my_qt_window(0)
{
	strncpy(fPluginName, kEmptyPanelPluginName, kMaxStringLength);
	//#ifdef WIN_ENV
	//	fDefaultWindProc = NULL;
	//#endif
}

/*
static void flyoutMenuPreVisFunc(AIPanelRef inPanel)
{
	//sAIUser->MessageAlert(ai::UnicodeString("pre visiblity"));
}
*/

void PanelFlyoutMenuProc(AIPanelRef inPanel, ai::uint32 itemID)
{
	AIErr error = kNoErr;
	AIPanelFlyoutMenuRef flyoutMenu = NULL;
	error = sAIPanel->GetFlyoutMenu(inPanel, flyoutMenu);
	AIPanelFlyoutMenuItemMark currentItemMark;
	switch(itemID)
	{
	case 1:
		error = sAIPanelFlyoutMenu->GetItemMark(flyoutMenu, 1 , currentItemMark);
		error = sAIPanelFlyoutMenu->SetItemMark(flyoutMenu, 1 , currentItemMark ? kAIPanelFlyoutMenuItemMark_NONE : kAIPanelFlyoutMenuItemMark_BULLET);
		break;
	case 2:
		error = sAIPanelFlyoutMenu->GetItemMark(flyoutMenu, 2 , currentItemMark);
		error = sAIPanelFlyoutMenu->SetItemMark(flyoutMenu, 2 , currentItemMark ? kAIPanelFlyoutMenuItemMark_NONE : kAIPanelFlyoutMenuItemMark_CHECK);
		break;
	case 3:
		error = sAIPanelFlyoutMenu->GetItemMark(flyoutMenu, 3 , currentItemMark);
		error = sAIPanelFlyoutMenu->SetItemMark(flyoutMenu, 3 , currentItemMark ? kAIPanelFlyoutMenuItemMark_NONE : kAIPanelFlyoutMenuItemMark_DASH);
		break;
	}
}

void PanelVisibilityChangedNotifyProc(AIPanelRef inPanel, AIBoolean isVisible)
{
	AIPanelUserData ud = NULL;
	sAIPanel->GetUserData(inPanel, ud);
	EmptyPanelPlugin* sPlugin = reinterpret_cast<EmptyPanelPlugin*>(ud);
	//sPlugin->UpdateMenu(isVisible, PANEL);
}

void PanelSizeChangedNotifyProc(AIPanelRef inPanel)
{
#ifdef MAC_ENV
	AISize panelSize= {0,0};
	AIErr error = kNoErr;
	
	error = sAIPanel->GetSize(inPanel, panelSize);
	
	if(!error)
	{
		NSRect newRect = NSMakeRect(0,0,panelSize.width,panelSize.height);
		[nibView setFrame:newRect];
	}
#endif
}	

/*
void PanelStateChangedNotifyProc(AIPanelRef inPanel, ai::int16 newState)
{
	AIErr err = kNoErr;
	AISize prefSize;
	switch(newState)
	{
	case 1:
		prefSize.height = prefSize.width = 300;
		break;
	case 2:
		prefSize.height = prefSize.width = 500;
		break;
	case 3:
		prefSize.height = prefSize.width = 700;
		break;
	}
	
	err = sAIPanel->SetPreferredSizes(inPanel, prefSize);
}
*/

/*
void PanelClosedNotifyProc(AIPanelRef inPanel)
{
	sAIUser->MessageAlert(ai::UnicodeString("Panel Closed"));
}
*/

/*
void PanelOpenedNotifyProc(AIPanelRef inPanel)
{
	sAIUser->MessageAlert(ai::UnicodeString("Panel Opened"));
}
*/

//--------------------------------------------------------------------
//Callback Procedures for Control Bar
//--------------------------------------------------------------------
/*
void ControlBarVisibilityChangedNotifyProc(AIControlBarRef inControlBar, AIBoolean isVisible)
{
	AIErr err = kNoErr;

	AIControlBarUserData userData = NULL;
	err = sAIControlBar->GetUserData(inControlBar, userData);
	if(err == kNoErr && userData)
	{
		EmptyPanelPlugin* plugin = reinterpret_cast<EmptyPanelPlugin*>(userData);
		plugin->UpdateMenu(isVisible, CTRL_BAR);
	}
}

void ControlBarSizeChangedNotifyProc(AIControlBarRef inControlBar)
{
}
*/

// Shouldn't be used
ASErr EmptyPanelPlugin::TimerInAction(void *message)
{
	ASErr error = kUnhandledMsgErr;
	sAIDocument->RedrawDocument();
	return error;
}

ASErr EmptyPanelPlugin::Message(char *caller, char *selector, void *message)
{
	ASErr error = Plugin::Message(caller, selector, message);

	my_qt_window->GetTextEdit()->append(caller);

	// kCallerAITimer
	if (strcmp(caller, kCallerAITimer) == 0)
	{
		//sAIUser->MessageAlert(ai::UnicodeString("Timer YOLO"));
		//error = TimerInAction(message);
		//my_qt_window->GetTextEdit()->append("timer");
	}

	return error;
}

// --------------------------------------------------------------------
// Called when plugin is initially loaded
// --------------------------------------------------------------------
ASErr EmptyPanelPlugin::StartupPlugin(SPInterfaceMessage *message)
{
	AIErr err = kNoErr;
	
	// Call base class routine
	err = Plugin::StartupPlugin(message);
	if (err)
		return err;
		
	// Timer, it is not used
	//err = sAITimer->AddTimer(message->d.self, "Time for Timer", kTicksPerSecond, &timerHandle);
	
	// added by Reza
	// About QApplication: http://doc.qt.io/qt-5/qapplication.html
	char *my_argv[] = { "program name", "arg1", "arg2", NULL };
	int my_argc = sizeof(my_argv) / sizeof(char*) - 1;
	my_qt_app = new QApplication (my_argc, my_argv);
	my_qt_window = new MyQTUI();
	//my_qt_app->exec();

	AINotifierHandle appShutDownNotifier;
	err = sAINotifier->AddNotifier(fPluginRef, "AI Application Shutdown Notifier", kAIApplicationShutdownNotifier, &appShutDownNotifier);
	if(err)
		return err;
	
	AIErr error = kNoErr;

	// Add About Plugins menu item for this plug-in.
	/*
	SDKAboutPluginsHelper aboutPluginsHelper;
	error = aboutPluginsHelper.AddAboutPluginsMenuItem(message, 
				kSDKDefAboutSDKCompanyPluginsGroupName, 
				ai::UnicodeString(kSDKDefAboutSDKCompanyPluginsGroupNameString), 
				"EmptyPanel...", 
				&fAboutPluginMenu);
	*/
	if (error)
		return error;

	// Add menu item
	error = sAIMenu->AddMenuItemZString(fPluginRef, "<Plugin>", kOtherPalettesMenuGroup, ZREF("<Plugin>"),
										kMenuItemNoOptions, &fEmptyPanelPanelMenuItemHandle);
	if (error)
		return error;

	/*
	fPanelFlyoutMenu = NULL;
	error = sAIPanelFlyoutMenu->Create(fPanelFlyoutMenu);
	if (error)
		return error;

	error = sAIPanelFlyoutMenu->AppendItem(fPanelFlyoutMenu, 1, ai::UnicodeString("First Item"));
	error = sAIPanelFlyoutMenu->AppendItem(fPanelFlyoutMenu, 3, ai::UnicodeString("Third Item"));
	error = sAIPanelFlyoutMenu->InsertItem(fPanelFlyoutMenu, 3, 2, ai::UnicodeString("Second Item"));
	error = sAIPanelFlyoutMenu->InsertSeparator(fPanelFlyoutMenu, 3, 5);
	error = sAIPanelFlyoutMenu->AppendItem(fPanelFlyoutMenu, 4, ai::UnicodeString("Fourth Item"));

	error = sAIPanelFlyoutMenu->SetItemEnabled(fPanelFlyoutMenu, 4, false);
	error = sAIPanelFlyoutMenu->SetItemMark(fPanelFlyoutMenu, 1 , kAIPanelFlyoutMenuItemMark_BULLET);
	error = sAIPanelFlyoutMenu->SetItemMark(fPanelFlyoutMenu, 2 , kAIPanelFlyoutMenuItemMark_CHECK);
	error = sAIPanelFlyoutMenu->SetItemMark(fPanelFlyoutMenu, 3 , kAIPanelFlyoutMenuItemMark_DASH);
	*/

	/*
	AISize pnSize = {240, 320};
	error = sAIPanel->Create(fPluginRef, ai::UnicodeString("Third Party Panel"), ai::UnicodeString("Third Party Panel"), 3, pnSize, true, fPanelFlyoutMenu, this, fPanel);
	if (error)
		return error;
	*/

	/*
	AISize minSize = {50, 50};
	AISize maxSize = {800, 800};
	AISize prefConstSize = {100, 100};
	AISize prefUnconstSize = {600, 600};

	error = sAIPanel->SetSizes(fPanel, minSize, prefUnconstSize, prefConstSize, maxSize);

	error = sAIPanel->Show(fPanel, true);
	error = sAIPanel->SetFlyoutMenuPreVisibilityProc(fPanel, flyoutMenuPreVisFunc);
	error = sAIPanel->SetFlyoutMenuProc(fPanel, PanelFlyoutMenuProc);
	error = sAIPanel->SetVisibilityChangedNotifyProc(fPanel, PanelVisibilityChangedNotifyProc);
	error = sAIPanel->SetSizeChangedNotifyProc(fPanel, PanelSizeChangedNotifyProc);
	error = sAIPanel->SetStateChangedNotifyProc(fPanel, PanelStateChangedNotifyProc);
	error = sAIPanel->SetClosedNotifyProc(fPanel, PanelClosedNotifyProc);
	//error = sAIPanel->SetClosedNotifyProc(fPanel, PanelClosedNotifyProc);
	*/

	//error = SetIcon();

	//error = AddWidgets();
	
	//Add Menu Item for Control Bar
	//if(!error)
	//	error = sAIMenu->AddMenuItemZString(fPluginRef, "Third Party Control Bar", kOtherPalettesMenuGroup, ZREF("Third Party Control Bar"),
	//										kMenuItemNoOptions, &fEmptyPanelControlBarMenuItemHandle);
	
	//Create Control Bar
	// AISize sizeControlBar = {controlBarWidth, controlBarHeight};
	// if(!error)
	// 	   error = sAIControlBar->Create(fPluginRef, sizeControlBar, controlBarWidthMin, controlBarWidthMax,NULL/*Userdata*/,fControlBar);
	// if(!error)
	//     error = sAIControlBar->SetUserData(fControlBar, this);
	
	//Set Callbacks
	/*
	if(!error)
		error = sAIControlBar->SetVisibilityChangedNotifyProc(fControlBar, ControlBarVisibilityChangedNotifyProc);
	if(!error)
		error = sAIControlBar->SetSizeChangedNotifyProc(fControlBar, ControlBarSizeChangedNotifyProc);
	*/

	//Add Different Widgets to Control Bar
	// if(!error)
	// 	  AddWidgetsToControlBar();

	return error;
}

/*
AIErr EmptyPanelPlugin::AddWidgets()
{
	AIErr error = kNoErr;
	AIPanelPlatformWindow hDlg = NULL;
	error = sAIPanel->GetPlatformWindow(fPanel, hDlg);

	//sAIUser->MessageAlert(ai::UnicodeString("add widget"));

#ifdef WIN_ENV

	HWND hwndXStaticText = CreateWindowEx( 
		0, L"STATIC",   // Predefined class; Unicode assumed. 
		L"X",		//  
		WS_VISIBLE | WS_CHILD | ES_LEFT,  // Styles. 
		10,         // x position. 
		40,         // y position. 
		45,        // width.
		20,        // height.
		hDlg,       // Parent window.
		NULL,
		(HINSTANCE)GetWindowLongPtr(hDlg, GWLP_HINSTANCE), 
		NULL);      // Pointer not needed.

	fHWndXEdit = CustomEdit::CreateCustomEdit( 
		0, //L"EDIT", // Predefined class; Unicode assumed. 
		L"",		//  
		WS_VISIBLE | WS_CHILD | ES_RIGHT | ES_NUMBER | WS_TABSTOP,  // Styles. 
		60,         // x position. 
		40,         // y position. 
		100,        // width.
		20,         // height.
		hDlg,       // Parent window.
		(HMENU) ID_XEdit,
		(HINSTANCE)GetWindowLongPtr(hDlg, GWLP_HINSTANCE), 
		NULL);      // Pointer not needed.

	Edit_LimitText(fHWndXEdit, 9);
	
	HWND hwndYStaticText = CreateWindowEx( 
		0, L"STATIC",   // Predefined class; Unicode assumed. 
		L"Y",		//  
		WS_VISIBLE | WS_CHILD | ES_LEFT,  // Styles. 
		10,         // x position. 
		70,         // y position. 
		45,         // width.
		20,         // height.
		hDlg,       // Parent window.
		NULL,
		(HINSTANCE)GetWindowLongPtr(hDlg, GWLP_HINSTANCE), 
		NULL);      // Pointer not needed.

	fHwndYEdit = CustomEdit::CreateCustomEdit( 
		0, //L"EDIT",   // Predefined class; Unicode assumed. 
		L"",		//  
		WS_VISIBLE | WS_CHILD | ES_RIGHT | ES_NUMBER | WS_TABSTOP,  // Styles. 
		60,         // x position. 
		70,         // y position. 
		100,        // width.
		20,        // height.
		hDlg,       // Parent window.
		(HMENU) ID_YEdit,
		(HINSTANCE)GetWindowLongPtr(hDlg, GWLP_HINSTANCE), 
		NULL);      // Pointer not needed.

	Edit_LimitText(fHwndYEdit, 9);

	HWND hwndSumStaticText = CreateWindowEx( 
		0, L"STATIC",   // Predefined class; Unicode assumed. 
		L"Sum",		//  
		WS_VISIBLE | WS_CHILD | ES_LEFT,  // Styles. 
		10,         // x position. 
		100,         // y position. 
		45,        // width.
		20,        // height.
		hDlg,       // Parent window.
		NULL,
		(HINSTANCE)GetWindowLongPtr(hDlg, GWLP_HINSTANCE), 
		NULL);      // Pointer not needed.

	fHwndResultEdit = CustomEdit::CreateCustomEdit( 
		0, //L"EDIT",   // Predefined class; Unicode assumed. 
		L"",		//  
		WS_VISIBLE | WS_CHILD | ES_RIGHT | ES_NUMBER | WS_TABSTOP,  // Styles. 
		60,         // x position. 
		100,         // y position. 
		100,        // width.
		20,        // height.
		hDlg,       // Parent window.
		(HMENU) ID_ResultEdit,
		(HINSTANCE)GetWindowLongPtr(hDlg, GWLP_HINSTANCE), 
		NULL);      // Pointer not needed.


	HWND HwndButtonAdd = CreateWindowEx( 
		0, L"BUTTON",   // Predefined class; Unicode assumed. 
		L"Add",		//  
		WS_VISIBLE | WS_CHILD | ES_LEFT,  // Styles. 
		30,         // x position. 
		130,         // y position. 
		100,        // width.
		20,        // height.
		hDlg,       // Parent window.
		(HMENU) ID_ButtonAdd,
		(HINSTANCE)GetWindowLongPtr(hDlg, GWLP_HINSTANCE), 
		NULL);      // Pointer not needed.

	HWND HwndButtonShow = CreateWindowEx( 
		0, L"BUTTON",   // Predefined class; Unicode assumed. 
		L"Show Dialog",		//  
		WS_VISIBLE | WS_CHILD | ES_LEFT,  // Styles. 
		30,         // x position. 
		160,         // y position. 
		100,        // width.
		20,        // height.
		hDlg,       // Parent window.
		(HMENU) ID_ButtonShow,
		(HINSTANCE)GetWindowLongPtr(hDlg, GWLP_HINSTANCE), 
		NULL);      // Pointer not needed.

	SendMessage(fHWndXEdit, (UINT) WM_SETTEXT, 0, (LPARAM)L"50"); 

	SendMessage(fHwndYEdit, (UINT) WM_SETTEXT, 0, (LPARAM)L"50");

	SendMessage(fHwndResultEdit, (UINT) WM_SETTEXT, 0, (LPARAM)L"100"); 

	::SetPropA(hDlg, "TPNL", this);
	fDefaultWindProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(hDlg, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(EmptyPanelPlugin::NewWindowProc)));
#endif
	
#ifdef MAC_ENV
	// Get our own bundle
	NSBundle* bundle = [NSBundle bundleWithIdentifier:@"com.adobe.illustrator.plugins.EmptyPanel"];
	//load the nib file
	CalcController* calculator = [CalcController alloc];
	[calculator initWithNibName:@"View" bundle:bundle];
	//set panel to be our nibs view
	NSView* newView = [calculator view];
	[hDlg setFrame:[newView frame]];
	[hDlg addSubview:newView];
	
#endif
	return error;
}
*/


/*
#ifdef WIN_ENV
LRESULT CALLBACK EmptyPanelPlugin::NewWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	EmptyPanelPlugin* panel = (EmptyPanelPlugin*)GetPropA(hWnd, "TPNL");
	LRESULT result = 0;
	bool handled = panel->PanelWindowProc(result, hWnd, msg, wParam, lParam);
	if(!handled)
		result =  panel->CallDefaultWindowProc(hWnd, msg, wParam, lParam);
	return result;
}

bool EmptyPanelPlugin::PanelWindowProc(LRESULT& result, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	bool handled = false;
	switch (msg) 
	{
	case WM_COMMAND: 
		{
			if(wParam == ID_ButtonAdd)
			{
				TCHAR XStr[255] ;
				SendMessage(fHWndXEdit, (UINT) WM_GETTEXT, 255, (LPARAM)XStr); 

				TCHAR YStr[255];
				SendMessage(fHwndYEdit, (UINT) WM_GETTEXT, 255, (LPARAM)YStr); 
				
				ai::NumberFormat numFormat;
				ASInt32 x = 0;
				sAIStringFormatUtils->StringToInteger(numFormat, ai::UnicodeString(XStr), x);
				ASInt32 y = 0;
				sAIStringFormatUtils->StringToInteger(numFormat, ai::UnicodeString(YStr), y);

				ASInt32 result = x + y;
				ai::UnicodeString strResult;
				sAIStringFormatUtils->IntegerToString(numFormat, result, strResult);
				SendMessage(fHwndResultEdit, (UINT) WM_SETTEXT, 0, (LPARAM)strResult.as_ASUnicode().c_str());

				handled = true;
			}
			else if(wParam == ID_ButtonShow)
			{
				sAIUser->MessageAlert(ai::UnicodeString("This is a Dialog"));
				handled = true;
			}
		}
	}
	return handled;
}

LRESULT CALLBACK EmptyPanelPlugin::CallDefaultWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if(fDefaultWindProc)
		return ::CallWindowProc(fDefaultWindProc, hWnd, msg, wParam, lParam);
	else
	{
		return 0; 
	}
}
*/

/*
LRESULT CALLBACK EmptyPanelPlugin::StaticCtrlBarWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	EmptyPanelPlugin* pluginPtr = reinterpret_cast<EmptyPanelPlugin*>(GetProp(hWnd, L"PLUGINPTR"));
	if(pluginPtr)
		return pluginPtr->CtrlBarWindowProc(hWnd, msg, wParam, lParam);
	else
		return NULL;
}
*/

/*
LRESULT EmptyPanelPlugin::CtrlBarWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_COMMAND:
		{
			AIErr error = kNoErr;
			switch(LOWORD(wParam))
			{
			case Min_Width_Button:
				{ 
					int minWidth = 0;
					error = GetIntegerFromEditText(hWnd, Min_Width_Edit_Text, minWidth);					
					if(!error)
					{
						error = sAIControlBar->SetMinimumWidth(fControlBar, minWidth);
						if(error)
							MessageBoxEx(hWnd, L"Invariant Failed : 0 <= newMinWidth <= currentWidth <= maxWidth", 
										 L"Invalid Minimum Width Value", MB_OK | MB_ICONSTOP | MB_SYSTEMMODAL, 0 );
					}
					break;
				}
			case Max_Width_Button:
				{
					int max_Width = 0;
					error = GetIntegerFromEditText(hWnd, Max_Width_Edit_Text, max_Width);
					if(!error)
					{
						error = sAIControlBar->SetMaximumWidth(fControlBar, max_Width);
						if(error)
							MessageBoxEx(hWnd, L"Invariant Failed : 0 <= minWidth <= currentWidth <= newMaxWidth", 
										 L"Invalid Maximum Width Value", MB_OK | MB_ICONSTOP | MB_SYSTEMMODAL, 0 );
					}
					break;
				}
			case Width_Button:
				{
					int width = 0;
					error = GetIntegerFromEditText(hWnd, Width_Edit_Text, width);
					if(!error)
					{
						error = sAIControlBar->SetWidth(fControlBar, width);
						if(error)
							MessageBoxEx(hWnd, L"Invariant Failed : 0 <= minWidth <= newWidth <= maxWidth", 
										 L"Invalid Width Value", MB_OK | MB_ICONSTOP | MB_SYSTEMMODAL, 0 );
					}
					break;
				}
			case Move_Button:
				{
					int X = 0, Y = 0;
					error = GetIntegerFromEditText(hWnd, X_Edit_Text, X);
					if(!error)
						error = GetIntegerFromEditText(hWnd, Y_Edit_text, Y);
					AIPoint point = {X,Y};
					if(!error)
					{	
						error = sAIControlBar->Move(fControlBar, point);
						if(error)
							MessageBoxEx(hWnd, L"Error occurred in Move", L"Error", MB_OK | MB_ICONSTOP | MB_SYSTEMMODAL, 0);
					}
					break;
				}
			case Get_Button:
				{
					AIReal minWidth = 0, maxWidth = 0, width = 0;
					error = sAIControlBar->GetMinimumWidth(fControlBar, minWidth);
					if(!error)
						error = sAIControlBar->GetMaximumWidth(fControlBar, maxWidth);
					if(!error)
						error = sAIControlBar->GetWidth(fControlBar, width);

					std::ostringstream info;
					info <<"Minimum Width = "<< minWidth <<"\nMaximum Width = "<< maxWidth <<"\nCurrent Width = "<<width;
					if(!error)
						MessageBoxExA(hWnd, info.str().c_str(),"Control Bar Information", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL, 0);
					break;
				}
			}
			break;
		}
	default:
		return CallWindowProc(fDefaultWindProc, hWnd, msg, wParam, lParam);
	}
}
*/

/*
AIErr EmptyPanelPlugin::GetIntegerFromEditText(HWND hWNDContainingEditText, int idEditText, int& outIntText)
{
	BOOL success = FALSE;
	outIntText = GetDlgItemInt(hWNDContainingEditText, idEditText, &success, false);
	return (success == TRUE) ? kNoErr : kCantHappenErr;
}

#endif
*/
ASErr EmptyPanelPlugin::ShutdownPlugin(SPInterfaceMessage *message)
{
	AIErr error = kNoErr;

	// added by Reza
	//error = sAITimer->SetTimerActive(timerHandle, false);

	// added by Reza
	if (my_qt_window)
	{
		my_qt_window->close();
		delete my_qt_window;
	}

	// added by Reza
	if (my_qt_app) 
	{ 
		my_qt_app->quit();
		delete my_qt_app; 
	}	
	
	/*if(fPanel)
	{
		error = sAIPanel->Destroy(fPanel);
		fPanel = NULL;
	}*/
	/*
	if(fPanelFlyoutMenu)
	{
		error = sAIPanelFlyoutMenu->Destroy(fPanelFlyoutMenu);
		fPanelFlyoutMenu = NULL;
	}
	*/
	return kNoErr;
}

ASErr EmptyPanelPlugin::GoMenuItem(AIMenuMessage *message)
{
	AIErr error = kNoErr;
	/*if (message->menuItem == fAboutPluginMenu) 
	{
		SDKAboutPluginsHelper aboutPluginsHelper;
		aboutPluginsHelper.PopAboutBox(message, "About EmptyPanel", kSDKDefAboutSDKCompanyPluginsAlertString);
	}
	else*/ 
	if (message->menuItem == fEmptyPanelPanelMenuItemHandle)
	{	
		//if(fPanel)
		//{
		//AIBoolean isShown = false;
		//error = sAIPanel->IsShown(fPanel, isShown);
		//error = sAIPanel->Show(fPanel, !isShown);

		//if (!isShown) // dunno why it is !not
		//{

		// Note that I don't use QApplication.exec()
		my_qt_window->show();
		my_qt_window->setFocus();	// should call this or the window will be hidden behind
		my_qt_app->exec();
		//sAIDocument->RedrawDocument();
		//}
		//}
	}
	
	/*
	else if (message->menuItem == fEmptyPanelControlBarMenuItemHandle)
	{
		if(fControlBar)
		{
			AIBoolean isShown = false;
			error = sAIControlBar->IsShown(fControlBar,isShown);
			error = sAIControlBar->Show(fControlBar, !isShown);
		}
	}
	*/

	return error;
}

/*
void EmptyPanelPlugin::UpdateMenu(AIBoolean isVisible, ItemType item)
{
	if (item == PANEL)
	{
		sAIMenu->CheckItem (fEmptyPanelPanelMenuItemHandle , isVisible);
		//sAIUser->MessageAlert(ai::UnicodeString("panel"));
	}
	else if (item == CTRL_BAR)
	{
		//sAIMenu->CheckItem (fEmptyPanelControlBarMenuItemHandle, isVisible);
		//sAIUser->MessageAlert(ai::UnicodeString("bar"));
	}
}
*/

ASErr EmptyPanelPlugin::Notify(AINotifierMessage *message)
{
	//->MessageAlert(ai::UnicodeString(message->type));

	AIErr result = kNoErr;
	if(strcmp(message->type, kAIApplicationShutdownNotifier) == 0)
	{		
		/*if(fPanel)
		{
		#ifdef WIN_ENV
			
			AIPanelPlatformWindow panelPlatfromWindow = NULL;
			result = sAIPanel->GetPlatformWindow(fPanel, panelPlatfromWindow);

			if(panelPlatfromWindow)
			{
				RemovePropA(panelPlatfromWindow, "TPNL");
				SetWindowLongPtr(panelPlatfromWindow, GWLP_WNDPROC, (LONG_PTR)(fDefaultWindProc));
				DestroyWindow(panelPlatfromWindow);
			}
		#endif

			result = sAIPanel->Destroy(fPanel);
			fPanel = NULL;
		}*/

		/*
		if(fPanelFlyoutMenu)
		{
			result = sAIPanelFlyoutMenu->Destroy(fPanelFlyoutMenu);
			fPanelFlyoutMenu = NULL;
		}
		*/
		/*
		if (fControlBar != NULL)
		{
#ifdef WIN_ENV
			AIControlBarPlatformWindow ctrlBarPlatformWindow = NULL;
			
			result = sAIControlBar->GetPlatformWindow(fControlBar, ctrlBarPlatformWindow);
					
			if(ctrlBarPlatformWindow)
			{
				
				RemoveProp(ctrlBarPlatformWindow, L"PLUGINPTR");
				SetWindowLongPtr(ctrlBarPlatformWindow, GWLP_WNDPROC, (LONG_PTR)(fDefCtrlBarWndProc));
				DestroyWindow(ctrlBarPlatformWindow);
			}
#endif
			result = sAIControlBar->Destroy(fControlBar);
			fControlBar = NULL;
		}
		*/
	}
	return result;
}

/*ASErr EmptyPanelPlugin::SetIcon()
{
	AIErr error = kNoErr;
	AIDataFilterSuite* sAIDataFilter = NULL;
	error = sSPBasic->AcquireSuite(kAIDataFilterSuite, kAIDataFilterVersion, (const void **)&sAIDataFilter);
	if (sAIDataFilter)
	{
		AIDataFilter *dataFilter(NULL);
		error = sAIDataFilter->NewResourceDataFilter(fPluginRef, 'PNGI', 0, "PL_Artboards_N", &dataFilter);	
		if (error == kNoErr && dataFilter)
		{
			error = sAIDataFilter->LinkDataFilter(NULL, dataFilter);
			
			size_t len = 0;
			char buf[bufMax];
			string buffStr;
			
			for(;;)
			{
				size_t count = bufMax;
				const ASErr error = sAIDataFilter->ReadDataFilter(dataFilter, buf, &count);
				if (error)
				{
					return error;
				}
				len += count;
				buffStr.append(buf, count);
				if (count != bufMax)
				{
					break;
				}
			}

			error = sAIPanel->SetIcon(fPanel, (ai::uint8 *)buffStr.c_str(), len, NULL, NULL);
		}
		
		error = sAIDataFilter->UnlinkDataFilter(dataFilter, NULL);
		sSPBasic->ReleaseSuite(kAIDataFilterSuite, kAIDataFilterVersion);
	}
	return error;
}
*/