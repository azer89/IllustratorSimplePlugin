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
//#include "AIPanel.h"
//#include "AIControlBar.h"
//#include "SDKDef.h"
//#include "SDKAboutPluginsHelper.h"

// Qt (Forward Declaration)
class QApplication;
class MyQTUI;

Plugin *AllocatePlugin(SPPluginRef pluginRef);
void FixupReload(Plugin *plugin);

class EmptyPanelPlugin : public Plugin
{
// added by Reza
// Qt
public:
	QApplication* my_qt_app;
	MyQTUI* my_qt_window;

public:

	EmptyPanelPlugin(SPPluginRef pluginRef);
	virtual ~EmptyPanelPlugin() {}
	
	virtual ASErr StartupPlugin(SPInterfaceMessage *message); 
	virtual ASErr ShutdownPlugin(SPInterfaceMessage *message); 	

	ASErr GoMenuItem(AIMenuMessage *message);
	ASErr Notify(AINotifierMessage *message);

	// added by Reza
	virtual ASErr Message(char *caller, char *selector, void *message);
	ASErr TimerInAction(void *message);
	ASErr DrawArtExample();
	ASErr RenderDocument1();
	ASErr RenderDocument2();

	FIXUP_VTABLE_EX(EmptyPanelPlugin, Plugin);

private:	
	// added by Reza
	AITimerHandle timerHandle;

	/* Handle for menu item in Window > Third Party Panel menu item. */
	//AIMenuItemHandle fEmptyPanelPanelMenuItemHandle;
	AIMenuItemHandle _menuItemHandle;
};

#endif	// __EmptyPanelPlugin_H__
