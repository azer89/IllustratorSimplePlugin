//========================================================================================
//  
//  $File: //ai/cs6/devtech/sdk/public/samplecode/common/source/Main.cpp $
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

/*

mouse click:
https://forums.adobe.com/message/4297109#4297109

AINotifierSuite
AITimerSuite

a timer discussion:
https://forums.adobe.com/message/6867591#6867591

*/

#include "Plugin.hpp"

#include <string.h>
#include <stdio.h>

#include <iostream>
#include "myqtui.h"
#include <QtWidgets/QApplication>

#ifndef NDEBUG
#ifdef MAC_ENV
#include <MacTypes.h>
#else
#include <Windows.h>
#endif
#endif

extern "C"
{
	SPBasicSuite *sSPBasic;
}

extern Plugin *AllocatePlugin(SPPluginRef pluginRef);
extern void FixupReload(Plugin *plugin);


extern "C" ASAPI ASErr PluginMain(char* caller, char* selector, void* message)
{
	ASErr error = kNoErr;
	SPMessageData *msgData = (SPMessageData *)message;
	
	Plugin *plugin = (Plugin *)msgData->globals;
	
	sSPBasic = msgData->basic;
	
	if (strcmp(caller, kSPInterfaceCaller) == 0) 
	{	
		if (strcmp( selector, kSPInterfaceStartupSelector) == 0)
		{
			plugin = AllocatePlugin(msgData->self);
			if (plugin)
			{
				msgData->globals = (void *)plugin;
				error = plugin->StartupPlugin((SPInterfaceMessage *)message);

				if (error != kNoErr)
				{
					// Make sure to delete in case startup failed
					delete plugin;
					plugin = nil;
					msgData->globals = nil;
				}
			}
			else
			{
				error = kOutOfMemoryErr;
			}
		}
		else if (strcmp(selector, kSPInterfaceShutdownSelector) == 0)
		{
			if (plugin)
			{
				error = plugin->ShutdownPlugin((SPInterfaceMessage *)message);				
				delete plugin;
				plugin = nil;
				msgData->globals = nil;
			}
		}
	}
	
	if (plugin)
	{
		if (Plugin::IsReloadMsg(caller, selector))
		{
			// Call this before calling any virtual functions (like Message)
			FixupReload(plugin);
			error = plugin->ReloadPlugin((SPInterfaceMessage *)message);
		}
		else
		{
			// If a load or reload failed because the suites could not be acquired, we released
			// any partially acquired suites and returned an error.  However, SuitePea still might
			// call us, so protect against this situation.
			if (plugin->SuitesAcquired())
			{
				error = plugin->Message(caller, selector, message);
				std::cout << "Messsage\n";
			}
			else
				error = kNoErr;
		}

		if (error == kUnhandledMsgErr)
		{
			error = kNoErr;
#ifndef NDEBUG
#ifdef MAC_ENV
			fprintf(stderr, "Warning: Unhandled plugin message: caller \"%s\" selector \"%s\"\n", caller, selector);
#else
			char buf[1024];
			
			sprintf(buf+1, "Warning: Unhandled plugin message: caller \"%s\" selector \"%s\"\n", caller, selector);
			OutputDebugStringA(buf+1);
#endif
#endif
		}
	}	

	if (error)
	{
		if (plugin)
			plugin->ReportError(error, caller, selector, message);
		else
			Plugin::DefaultError(msgData->self, error);
	}
	
	return error;
}
