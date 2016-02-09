//========================================================================================
//  
//  $File: //ai/mainline/devtech/sdk/public/samplecode/Tutorial/Source/TutorialPlugin.cpp $
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

#include "TutorialPlugin.h"
#include "TutorialSuites.h"
#include "TutorialID.h"
#include "SDKAboutPluginsHelper.h"
#include "AICSXS.h"
#include "TutorialPanelController.h"

#include <iostream>
#include "myqtui.h"
#include <QtWidgets/QApplication>

TutorialPlugin*	gPlugin = NULL;

/*
*/
Plugin* AllocatePlugin(SPPluginRef pluginRef)
{
	return new TutorialPlugin(pluginRef);
}

/*
*/
void FixupReload(Plugin* plugin)
{
	TutorialPlugin::FixupVTable((TutorialPlugin*) plugin);
}

/*
*/
ASErr TutorialPlugin::SetGlobal(Plugin *plugin)
{
	gPlugin = (TutorialPlugin *) plugin;
	return kNoErr;
}

TutorialPlugin::TutorialPlugin(SPPluginRef pluginRef) 
	: Plugin(pluginRef),
	fAboutPluginMenu(NULL),
	fApplyFilterNotifier(NULL),
	fCSXSPlugPlugSetupCompleteNotifier(NULL),
	fPanelController(NULL),
    fResourceManagerHandle(NULL),
	fShutdownApplicationNotifier(NULL)
{
	strncpy(fPluginName, kTutorialPluginName, kMaxStringLength);
}

ASErr TutorialPlugin::StartupPlugin(SPInterfaceMessage* message)
{
	ASErr error = kNoErr;
	error = Plugin::StartupPlugin(message);

	if (!error) {
		error = AddMenu(message);
	}
	if (!error) {	
		error = AddFilter(message);
	}
	if (!error) {
		error = AddTool(message);
	}
	if (!error) {
		error = AddAction(message);
	}
	if (!error) {
		error = AddNotifiers(message);
	}

	//sAIUser->MessageAlert(ai::UnicodeString("Hello World, by Reza"));

	/*
	// do something
	sAIUser->MessageAlert(ai::UnicodeString("Hello World, by Reza"));
	// https://forums.adobe.com/thread/1353898?tstart=0
	
	char *my_argv[] = { "program name", "arg1", "arg2", NULL };
	int my_argc = sizeof(my_argv) / sizeof(char*) - 1;

	QApplication a(my_argc, my_argv);
	MyQTUI w;
	w.show();
	
	a.exec();
	*/

	return error;
}

ASErr TutorialPlugin::PostStartupPlugin()
{
	ASErr result = kNoErr;

	// Create flash controller
	if (fPanelController == NULL)
	{
		fPanelController = new TutorialPanelController();
		result = Plugin::LockPlugin(true);
	}
    if(!result)
        sAIUser->CreateCursorResourceMgr(fPluginRef,&fResourceManagerHandle);

	//sAIUser->MessageAlert(ai::UnicodeString("Hello World, by Reza"));

	
	/*
	char *my_argv[] = { "program name", "arg1", "arg2", NULL };
	int my_argc = sizeof(my_argv) / sizeof(char*) - 1;

	QApplication a(my_argc, my_argv);
	MyQTUI w;
	w.show();
	a.exec();
	*/

	return result;
}

ASErr TutorialPlugin::ShutdownPlugin(SPInterfaceMessage* message)
{
	if (fPanelController != NULL)
	{
		fPanelController->RemoveEventListeners();
		delete fPanelController;
		fPanelController = NULL;
	}

	return Plugin::ShutdownPlugin(message);
}

ASErr TutorialPlugin::AddNotifiers(SPInterfaceMessage* message)
{
	AIErr result;
	result = sAINotifier->AddNotifier(message->d.self, "Tutorial " kAICSXSPlugPlugSetupCompleteNotifier,
										kAICSXSPlugPlugSetupCompleteNotifier,
										&fCSXSPlugPlugSetupCompleteNotifier);
	
	result = sAINotifier->AddNotifier(message->d.self, kTutorialPluginName,
										kTutorialApplyFilterNotifier,
										&fApplyFilterNotifier);

	result = sAINotifier->AddNotifier(fPluginRef, kTutorialPluginName, 
										kAIApplicationShutdownNotifier, 
										&fShutdownApplicationNotifier);
	return result;
}

ASErr TutorialPlugin::Notify(AINotifierMessage *message)
{
	//sAIUser->MessageAlert(ai::UnicodeString("Notify!!!"));

	if ( message->notifier == fCSXSPlugPlugSetupCompleteNotifier )
	{
		if (fPanelController != NULL)
		{
			fPanelController->RegisterCSXSEventListeners();
		}
	}
	else if ( message->notifier == fApplyFilterNotifier )
	{
		TutorialFilterParameters* params = (TutorialFilterParameters*)message->notifyData;
		ActuallyGoFilter(*params);
	}
	
	if (message->notifier == fShutdownApplicationNotifier)
	{
		if(fResourceManagerHandle != NULL)
		{
			sAIUser->DisposeCursorResourceMgr(fResourceManagerHandle);
			fResourceManagerHandle = NULL;
		}
	}

	return kNoErr;
}

/* Adds this plug-in's menus.
*/
AIErr TutorialPlugin::AddMenu ( SPInterfaceMessage* message )
{
	ASErr error = kNoErr;

	// Add About Plugins menu item for this plug-in.
	SDKAboutPluginsHelper aboutPluginsHelper;
	error = aboutPluginsHelper.AddAboutPluginsMenuItem(message, 
				kSDKDefAboutSDKCompanyPluginsGroupName, 
				ai::UnicodeString(kSDKDefAboutSDKCompanyPluginsGroupNameString), 
				kTutorialPluginName "...", 
				&fAboutPluginMenu);
	return error;
}

/* Handles this plug-in's menus.
*/
AIErr TutorialPlugin::GoMenuItem ( AIMenuMessage* message )
{
	SDKAboutPluginsHelper aboutPluginsHelper;
	aboutPluginsHelper.PopAboutBox(message, "About Tutorial", kSDKDefAboutSDKCompanyPluginsAlertString);

	return kNoErr;
}

/* Adds this plug-in's filter.
*/
AIErr TutorialPlugin::AddFilter ( SPInterfaceMessage* message )
{
	AIErr error = kNoErr;
	AIMenuItemHandle menuItem = nil;

	// Set the filter Category and Title from string resources
	PlatformAddFilterData filterData;
	filterData.category = (unsigned char*)kSDKFilterString;
	filterData.title = (unsigned char*)kTutorialFilterString;
  
	// Add the filter.
	error = sAIFilter->AddFilter( message->d.self, "Tutorial", &filterData,
								kToolWantsToTrackCursorOption, &fFilterHandle);
	if ( !error ) {
		// Only enable the filter's menu item if a document is open.
		error = sAIFilter->GetFilterMenuItem(fFilterHandle, &menuItem);
		if ( !error ) {
			error = sAIMenu->UpdateMenuItemAutomatically(menuItem,
				kAutoEnableMenuItemAction,
				0, 0,	// don't care about what's in artwork
				0, 0,	// don't care about selection
				kIfOpenDocument, 0 );	// Enable if a document is open
		}
	}

	return error;
}

/* Prompts for input parameters for this plug-in's filter.
*/
AIErr TutorialPlugin::GetFilterParameters( AIFilterMessage* message ) 
{
	
	char *my_argv[] = { "program name", "arg1", "arg2", NULL };
	int my_argc = sizeof(my_argv) / sizeof(char*) - 1;

	QApplication a(my_argc, my_argv);
	MyQTUI w;
	w.show();
	a.exec();

	

	//sAIUser->MessageAlert(ai::UnicodeString("YOLO"));

	/*
	if (fPanelController != NULL)
		fPanelController->LoadExtension();
	*/
	message->parameters = NULL;

	return kNoErr;
}

/* Filter if there are parameters already taken
*/
AIErr TutorialPlugin::GoFilter( AIFilterMessage* message )
{
	AIErr error = kNoErr;
	if(message->parameters != NULL)
	{
		TutorialFilterParameters* params = (TutorialFilterParameters*) message->parameters;
		this->ActuallyGoFilter(*params);
	}
	return error;
}

/* Applies this plug-in's filter.
*/
AIErr TutorialPlugin::ActuallyGoFilter(TutorialFilterParameters params)
{
	AIErr 	error = kNoErr;

	// Do your stuff here, for example...

	// Create a new path.
	AIArtHandle path;
	error = sAIArt->NewArt( kPathArt, kPlaceAboveAll, nil, &path );
	
	// Find the point on the page that's in the middle of the window.
	AIRealPoint center;
	if ( !error ) {
		error = sAIDocumentView->GetDocumentViewCenter( nil, &center );
	}

	// Create the polygon points, randomly located around the center.
	if ( !error )
	{
		ASInt32  corners = params.corners;
		ASInt32  size = params.size;
		AIPathSegment segment;
		// All of the segments are corners
		segment.corner = true;
		for (short i = 0; i < corners; ++i )
		{
			segment.p.h = center.h +
						  sAIMath->AIRealMul( sAIRandom->FloatRnd() - kAIRealHalf, (AIReal) size );
			segment.p.v = center.v +
						  sAIMath->AIRealMul( sAIRandom->FloatRnd() - kAIRealHalf, (AIReal) size );
			segment.in = segment.out = segment.p;
			error = sAIPath->SetPathSegments( path, i, 1, &segment );
			if ( error ) 
				break;
		}
	}

	// Close the path.
	if ( !error )
	{
		error = sAIPath->SetPathClosed( path, true );
	}

	// Allow the filter to be recorded as an action event.
	if ( !error )
	{
		error = RecordFilterAction(params);
	}
	
	if ( !error )
	{
		error = sAIArt->SetArtUserAttr(path, kArtSelected, kArtSelected);
	}

	return error;
}

/* Adds this plug-in's tool to Illustrator.
*/
AIErr TutorialPlugin::AddTool( SPInterfaceMessage* message ) 
{
	AIErr error = kNoErr;
	AIAddToolData toolData;
	toolData.title = "Tutorial Line Tool"; 
	toolData.tooltip = "Tutorial Line Tool";
	toolData.sameGroupAs = kNoTool;
	toolData.sameToolsetAs = kNoTool;
	toolData.normalIconResID = kTutorialToolIconResourceID;
	toolData.darkIconResID = kTutorialToolIconResourceID;

	ai::int32	options = kToolWantsToTrackCursorOption;

	error = sAITool->GetToolNumberFromName(kTutorialTool, &toolData.sameGroupAs); // the Crop Area tool is now the first in its group
	if (error) return error;

	error = sAITool->GetToolNumberFromName(kTutorialTool, &toolData.sameToolsetAs); // and at the top of its tool stack
	if (error) return error;


	if (!error) {
		error = sAITool->AddTool( message->d.self, kTutorialTool, &toolData,
					options, &fToolHandle);
	}

	return error;
}

ASErr TutorialPlugin::TrackToolCursor( AIToolMessage* message )
{
    AIErr error = kNoErr;
	error = sAIUser->SetCursor(kTutorialToolIconResourceID, fResourceManagerHandle);
	return error;
}

ASErr TutorialPlugin::DeselectTool( AIToolMessage* message )
{
    return kNoErr;   
}
		
/* Handles mouse down event for this plug-in's tool.
*/
AIErr TutorialPlugin::ToolMouseDown( AIToolMessage* message ) 
{
	AIErr 	error = kNoErr;
	AIArtHandle path;
	AIPathSegment segment;	
	ai::int32 	count = 0;
	AIMatchingArtSpec spec[1];
	AIArtHandle **matches;
	short segmentCount = 0;

	// Get the current selection (if any).
	if ( !error ) {
		spec[0].type = kPathArt;
		spec[0].whichAttr = kArtSelected;
		spec[0].attr = kArtSelected;
		error = sAIMatchingArt->GetMatchingArt( spec, 1, &matches, &count );
	}

	bool addPoint = false;
	if ( !error ) {
		if ( count == 0 ) {
			addPoint = true;
			// There is no selection, so make a new path.
			error = sAIArt->NewArt( kPathArt, kPlaceAboveAll, nil, &path );
			
			// Select it so we find it later.
			if (!error) {
				error = sAIArt->SetArtUserAttr( path, kArtSelected, kArtSelected );
			}
		}
		else if ( count == 1 ) {
			addPoint = true;
			path = (*matches)[0];
		}
	}

	//  Add point to the path at the mouse down location.
	if ( !error && addPoint) {
		error = sAIPath->GetPathSegmentCount( path, &segmentCount );
		// All of the segments are corners
		if ( !error) {
			segment.corner = true;  
			segment.p.h = message->cursor.h;
			segment.p.v = message->cursor.v;
			segment.in = segment.out = segment.p;
			error = sAIPath->SetPathSegments( path, segmentCount, 1, &segment );
		}
	}

	return error;
}

/* Registers this plug-in's action with Illustrator.
*/
AIErr TutorialPlugin::AddAction ( SPInterfaceMessage* message )
{
	AIErr 	error = kNoErr;

	// This is your opportunity to register your plug-in to the Action Manager and
	// describe its parameter block.
	// verify that the sAIActionManager suite pointer is valid
	// if the Action plug-in was disabled (taken from the Plug-ins folder)
	// then the sAIActionManager suite pointer would not be valid.
	// We acquire and release this suite individually during reload and unload
	if (sAIActionManager)
	{
		AIActionParamTypeRef actionParam = nil;
		SPPluginRef	pluginRef = message->d.self;

		// Create a new Type Parameter Block (TPB)
		sAIActionManager->AINewActionParamType(&actionParam);	
		
		if (actionParam && pluginRef)
		{
			// Fill in the TPB.
			// This describes which parameters your filter requires.

			// Set the 'Corners' parameter in the Type Parameter Block (TPB)
			sAIActionManager->AIActionSetTypeKey(actionParam, 'crnr', kActionNumberString, actionTypeInteger, true);
			// Set the 'Size' parameter in the TPB
			sAIActionManager->AIActionSetTypeKey(actionParam, 'size', kActionSizeString, actionTypeInteger, true);
			
			// Register the your plug-in to the Action Manager
			// The kActionTitleString parameter is the name of the Action which
			// will be shown in the Action Palette.
			error = sAIActionManager->RegisterActionEvent("AISDK_Tutorial", kActionTitleString,
															1, 0, nil, pluginRef,
															nil, 
															actionParam);

			// Dispose the TPB. The Action Manager has already made a copy of it internally.
			sAIActionManager->AIDeleteActionParamType(actionParam);		
		}
	}
	return error;
}

/*
*/
AIErr TutorialPlugin::RecordFilterAction(const TutorialFilterParameters& parameters)
{
	ASErr error = kNoErr;
	AIActionParamValueRef valueParameterBlock = nil;

	// Record Action if InRecordMode
	// If the user is InRecordMode (the Record button was pressed in the Action Palette),
	// your plug-in must report user parameters to the Action Manager so that it can
	// replay this at a later time.
	// Your plug-in will receive a kActionCaller/kDoActionSelector when the Action Manager
	// wants you to replay this action.
	if (sAIActionManager && sAIActionManager->InRecordMode()) {
		
		// create a new Value Parameter Block (VPB)
		error = sAIActionManager->AINewActionParamValue(&valueParameterBlock);		
		if (!error && valueParameterBlock) {
			// Set the 'crnr' parameter in the VPB
			sAIActionManager->AIActionSetInteger(valueParameterBlock, 'crnr', parameters.corners);
			// Set the 'size' parameter in the VPB
			sAIActionManager->AIActionSetInteger(valueParameterBlock, 'size', parameters.size);
			// Record this action with parameters contained in the VPB
			sAIActionManager->RecordActionEvent("AISDK_Tutorial", kDialogOn, valueParameterBlock);
			// Delete the VPB, the Action Manager makes an internal copy of it.
			sAIActionManager->AIDeleteActionParamValue(valueParameterBlock);		
		}
	}
	return error;
}

/* Executes this plug-in's action. 
 * This routine gets called when your plug-in gets called with kActionCaller/kDoActionSelector
 * Your plug-in is being run by the Actions panel.
*/
AIErr TutorialPlugin::GoAction(DoActionMessage* doActionMessage)
{
	ASErr error = kNoErr;
	TutorialFilterParameters** params_handle;
	AIFilterMessage filterMessageStruct, *filterMessage;

	// Allocate instance of struct MyFilterParameters
	if (!error) {
		filterMessage = &filterMessageStruct;
		filterMessage->d = doActionMessage->d;
		error = sAIMDMemory->MdMemoryNewHandle( sizeof( TutorialFilterParameters ), ( AIMdMemoryHandle *)&filterMessage->parameters);
		if ( !error && !filterMessage->parameters ) {
			error = kOutOfMemoryErr;
		}
	}

	// Extract parameter values from the the Value Parameter Block (VPB). 
	if (!error) {
		AIActionParamValueRef valueParameterBlock = doActionMessage->param;
		params_handle = ( TutorialFilterParameters **) filterMessage->parameters;
		error = sAIActionManager->AIActionGetInteger(valueParameterBlock, 'crnr', &(*params_handle)->corners);
		if (!error) {
			error = sAIActionManager->AIActionGetInteger(valueParameterBlock, 'size', &(*params_handle)->size);
		}
	}

	// Pop filter parameters dialog if asked to.
	if (!error && doActionMessage->showDialog) 
	{

		char *my_argv[] = { "program name", "arg1", "arg2", NULL };
		int my_argc = sizeof(my_argv) / sizeof(char*) - 1;

		QApplication a(my_argc, my_argv);
		MyQTUI w;
		w.show();
		a.exec();
		
		filterMessage->parameters = NULL;
		error = kNoErr;
		
		
		//error = GetFilterParameters( filterMessage );
	} 

	/*
	// Apply the filter.
	if (!error) {
		error = GoFilter( filterMessage );
	}
	*/

	return error;
}

AIFilterHandle TutorialPlugin::getFilterHandle()
{
	return fFilterHandle;
}
