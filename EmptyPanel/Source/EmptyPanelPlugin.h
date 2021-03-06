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

// Illustrator API plugin, do not edit, do not remove
#include "Plugin.hpp"

// Custom
#include <vector>
#include "APath.h"

// Qt (Forward Declaration) - added by Reza
class QApplication;
class MyQTUI;

Plugin *AllocatePlugin(SPPluginRef pluginRef);
void FixupReload(Plugin *plugin);

class EmptyPanelPlugin : public Plugin
{ 
// Qt - added by Reza
public:
	QApplication* _my_qt_app;
	MyQTUI* _my_qt_window;
	std::vector<APath> _paths;

public:
	EmptyPanelPlugin(SPPluginRef pluginRef);
	virtual ~EmptyPanelPlugin() {}
	
	virtual ASErr StartupPlugin(SPInterfaceMessage *message); 
	virtual ASErr ShutdownPlugin(SPInterfaceMessage *message); 	

	ASErr GoMenuItem(AIMenuMessage *message);
	ASErr Notify(AINotifierMessage *message);

	FIXUP_VTABLE_EX(EmptyPanelPlugin, Plugin);	// I don't know what is this

	// added by Reza
	virtual ASErr Message(char *caller, char *selector, void *message);
	ASErr TimerInAction(void *message);
	ASErr RenderDocument();
	void RasterizeArtToPNG(AIArtHandle artHandle, const std::string& path);
	void RenderPathGroup(AIArtHandle artHandle);
	void ParsePath(AIArtHandle artHandle);

private:	
	// added by Reza
	AITimerHandle timerHandle;
	AIMenuItemHandle _menuItemHandle; // for displaying Qt window
	AIMenuItemHandle _grabItemHandle; // grabbing data from QT
};

#endif	// __EmptyPanelPlugin_H__
