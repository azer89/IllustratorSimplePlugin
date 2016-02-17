//========================================================================================
//  
//  $File: //ai/mainline/devtech/sdk/public/samplecode/EmptyPanel/source/EmptyPanelPlugin.h $
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

#ifndef __EmptyPanelPlugin_H__
#define __EmptyPanelPlugin_H__

#include "Plugin.hpp"
#include "AIPanel.h"
#include "AIControlBar.h"
#include "SDKDef.h"
#include "SDKAboutPluginsHelper.h"

// Qt
#include <iostream>
#include "myqtui.h"
#include <QtWidgets/QApplication>

#ifdef WIN_ENV
	#include "windows.h"

	// Panel
	#define ID_XEdit				1
	#define ID_YEdit				2
	#define ID_ResultEdit			3
	#define ID_ButtonAdd			4
	#define ID_ButtonShow			5

	//Control Bar Buttons
	#define Min_Width_Button		6
	#define Max_Width_Button		7
	#define Width_Button			8
	#define Move_Button				9
	#define Get_Button				10
	#define Min_Width_Edit_Text		11
	#define Max_Width_Edit_Text		12
	#define Width_Edit_Text			13
	#define X_Edit_Text				14
	#define Y_Edit_text				15
#endif

Plugin *AllocatePlugin(SPPluginRef pluginRef);
void FixupReload(Plugin *plugin);

enum ItemType {
	PANEL,
	CTRL_BAR
};

class EmptyPanelPlugin : public Plugin
{

// Qt
public:
	QApplication* my_qt_app;
	MyQTUI* my_qt_window;

public:

	EmptyPanelPlugin(SPPluginRef pluginRef);
	virtual ~EmptyPanelPlugin() {}
	
	virtual ASErr StartupPlugin(SPInterfaceMessage *message); 
	virtual ASErr ShutdownPlugin(SPInterfaceMessage *message); 
	virtual ASErr Message(char *caller, char *selector, void *message);

	// added by Reza
	ASErr TimerInAction(void *message);

	void UpdateMenu(AIBoolean isVisible, ItemType item);
	ASErr GoMenuItem(AIMenuMessage *message);
	ASErr Notify(AINotifierMessage *message);

	

	FIXUP_VTABLE_EX(EmptyPanelPlugin, Plugin);

private:
	
	AITimerHandle timerHandle;

	/**	Handle for the About SDK Plug-ins menu item.
	*/
	AIMenuItemHandle fAboutPluginMenu;

	/** Handle for menu item in Window > Third Party Panel menu item.
	*/
	AIMenuItemHandle fEmptyPanelPanelMenuItemHandle;

	/** Pointer to instance of Panel.
	*/
	//AIPanelRef fPanel;

	AIPanelFlyoutMenuRef fPanelFlyoutMenu;

	//AIControlBarRef fControlBar;

	AIMenuItemHandle fEmptyPanelControlBarMenuItemHandle;
	
	ASErr SetIcon();

	ASErr AddWidgets();
	
	ASErr AddWidgetsToControlBar();

	AIPanelPlatformWindow hDlg;
#ifdef WIN_ENV
	//Panel related
	/*
	static LRESULT CALLBACK NewWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	bool PanelWindowProc(LRESULT& result, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK CallDefaultWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	WNDPROC fDefaultWindProc;
	HWND fHWndXEdit;
	HWND fHwndYEdit;
	HWND fHwndResultEdit;
	*/

	//Control Bar Related
	/*
	WNDPROC fDefCtrlBarWndProc;
	static LRESULT CALLBACK StaticCtrlBarWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CtrlBarWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	AIErr GetIntegerFromEditText(HWND hWNDContainingEditText, int idEditText, int& outIntText);
	*/

#endif
};

#endif	// __EmptyPanelPlugin_H__
