//========================================================================================
//  
//  $File: //ai/mainline/devtech/sdk/public/samplecode/Tutorial/Source/TutorialPlugin.h $
//
//  $Revision: #1 $
//
//  Copyright 2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __TUTORIALPLUGIN_H__
#define __TUTORIALPLUGIN_H__

#include "IllustratorSDK.h"
#include "Plugin.hpp"
#include "TutorialFilterParameters.h"
#include "TutorialId.h"

class TutorialPanelController;

void FixupReload(Plugin* plugin);

class TutorialPlugin : public Plugin
{
public:
	/**	Constructor.
		@param pluginRef IN reference to this plugin.
	*/
	TutorialPlugin(SPPluginRef pluginRef);

	/** Applies this plug-in's filter.
	*/
	AIErr ActuallyGoFilter(TutorialFilterParameters params);

	FIXUP_VTABLE_EX(TutorialPlugin, Plugin);

public:	AIFilterHandle getFilterHandle(void);

protected:
	
	virtual ASErr SetGlobal(Plugin *plugin);

	virtual ASErr StartupPlugin(SPInterfaceMessage *message); 
	virtual ASErr PostStartupPlugin(); 
	virtual ASErr ShutdownPlugin(SPInterfaceMessage* message);
    virtual ASErr TrackToolCursor( AIToolMessage* message );
    virtual ASErr DeselectTool( AIToolMessage * message );
	virtual ASErr Notify(AINotifierMessage *message);

	/** Handles this plug-in's menu items.
	*/
	virtual AIErr GoMenuItem ( AIMenuMessage* message );

	/** Prompts the user for the parameters used by this plug-in's filter.
	*/
	virtual AIErr GetFilterParameters( AIFilterMessage* message );

	/** Stub method
	*/
	virtual AIErr GoFilter( AIFilterMessage* message );

	/** Handles mouse down messages for this plug-in's tool.
	*/
	virtual AIErr ToolMouseDown( AIToolMessage* message );

	/** Executes this plug-in's filter as an action event.
	*/
	virtual AIErr GoAction( DoActionMessage* message);
    
    

private:
	/** Records this plug-in's filter as an action event.
	*/
	AIErr RecordFilterAction(const TutorialFilterParameters& myParameters);

	/** Adds this plug-in's menu items to Illustrator.
	*/
	AIErr AddMenu(SPInterfaceMessage* message);

	/** Adds this plug-in's action event to Illustrator.
	*/
	AIErr AddAction(SPInterfaceMessage* message);

	/** Adds this plug-in's filter to Illustrator.
	*/
	AIErr AddFilter(SPInterfaceMessage* message);

	/** Adds this plug-in's tool to Illustrator.
	*/
	AIErr AddTool(SPInterfaceMessage* message);

	/** Adds the listeners for the notifications we are interested in
	*/
	ASErr AddNotifiers(SPInterfaceMessage* message);

	AIFilterHandle fFilterHandle;
	AIToolHandle fToolHandle;

	/** Menu item handle for this plug-ins About menu.
	*/
	AIMenuItemHandle fAboutPluginMenu;

	/** Handle for the apply filter notifier dispatched by the flash UI
	*/
	AINotifierHandle fApplyFilterNotifier;
	
	/** Handle for CSXS plugplug setup complete notifier.
	*/
	AINotifierHandle fCSXSPlugPlugSetupCompleteNotifier;

	/** The controller for the flash dialog
	*/
	TutorialPanelController* fPanelController;
    
    /** Handle for resource manager (used to set cursor icon)
     */
    AIResourceManagerHandle fResourceManagerHandle;

	/** Handle for illustrator shutdown notifier.
	*/
	AINotifierHandle fShutdownApplicationNotifier;
};

#endif
