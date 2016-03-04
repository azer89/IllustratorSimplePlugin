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

// sAIUser->MessageAlert(ai::UnicodeString("Your message here"));

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
	my_qt_app(0),
	my_qt_window(0)
{
	strncpy(fPluginName, kEmptyPanelPluginName, kMaxStringLength);
}

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
		//sAIUser->MessageAlert(ai::UnicodeString("Timer"));
		//error = TimerInAction(message);
		//my_qt_window->GetTextEdit()->append("Timer");
	}

	return error;
}

// --------------------------------------------------------------------
// Called when plugin is initially loaded
// --------------------------------------------------------------------
ASErr EmptyPanelPlugin::StartupPlugin(SPInterfaceMessage *message)
{
	AIErr error = kNoErr;
	
	// Call base class routine
	error = Plugin::StartupPlugin(message);
	if (error) { return error; }
		
	// don't delete
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
	error = sAINotifier->AddNotifier(fPluginRef, "AI Application Shutdown Notifier", kAIApplicationShutdownNotifier, &appShutDownNotifier);
	if (error) { return error; }
	
	//AIErr error = kNoErr;

	// Add menu item
	error = sAIMenu->AddMenuItemZString(fPluginRef, "<Plugin>", kOtherPalettesMenuGroup, ZREF("<Plugin>"),
										kMenuItemNoOptions, &fEmptyPanelPanelMenuItemHandle);
	if (error) { return error; }

	return error;
}

ASErr EmptyPanelPlugin::ShutdownPlugin(SPInterfaceMessage *message)
{
	AIErr error = kNoErr;

	// don't delete
	// added by Reza
	//error = sAITimer->SetTimerActive(timerHandle, false);

	// added by Reza
	// Delete Qt window
	if (my_qt_window)
	{
		my_qt_window->close();
		delete my_qt_window;
	}

	// added by Reza
	// Delete Qt instance
	if (my_qt_app) 
	{ 
		my_qt_app->quit();
		delete my_qt_app; 
	}	

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

		// get pixels
		// error = sAIDrawArtSuite->GetImagePixelData(port.port, &pixelData, &length, width, height);

		AIDrawArtAGMPort port;
		error = sAIDrawArtSuite->CreateImagePort(50, 50, &port.port);

		AIDrawColorData colorData;
		AIColor color;
		AISwatchRef swatchRef = sAISwatchList->GetSwatchByName(NULL, ai::UnicodeString("CMYK Red"));
		error = sAISwatchList->GetAIColor(swatchRef, &color);
		colorData.color = color;
		colorData.output.port = port;
		colorData.type = 2;
		colorData.style = 0;
		colorData.rect.bottom = 50;
		colorData.rect.right = 50;
		colorData.rect.left = 0;
		colorData.rect.top = 0;
		colorData.options = 0;
		colorData.width = 0;

		colorData.color = color;
		colorData.output.port = port;

		// THIS ONE !
		error = sAIDrawArtSuite->DrawColorSwatch(&colorData);

		size_t length = 0;
		ai::uint32* width = 0;
		ai::uint32* height = 0;
		const ai::uint8* pixelData = NULL;
		error = sAIDrawArtSuite->GetImagePixelData(port.port, &pixelData, &length, width, height);

		std::vector<QColor> colorList;

		length = length / 4;
		for (size_t i = 0; i < length; i++)
		{
			// How to get the individual values
			const ai::uint8* a = pixelData++;
			const ai::uint8* r = pixelData++;
			const ai::uint8* g = pixelData++;
			const ai::uint8* b = pixelData++;

			colorList.push_back(QColor(QString::number(*r).toInt(), 
									   QString::number(*g).toInt(), 
									   QString::number(*b).toInt(), 
									   QString::number(*a).toInt()));
		}

		my_qt_window->SendData(50, 50, colorList);

		/* we show our UI*/
		my_qt_window->show();
		my_qt_window->setFocus();	// should call this or the window will be hidden behind
		//my_qt_app->exec();		// Note that I don't use QApplication.exec()

		error = sAIDrawArtSuite->DestroyImagePort(port.port);

		// Apparently this will give you error if you don't have an active document
		if (error) { sAIUser->MessageAlert(ai::UnicodeString("Error !")); }

		/* SAVE IMAGE*/
		// Takes too long and png file can't be read
		// The code is from here: https://forums.adobe.com/thread/915322?tstart=0
		/*
		ASErr result;
		AIActionParamValueRef valueParameterBlock = NULL;
		ActionDialogStatus dialogStatus = kDialogOff;

		result = sAIActionManager->AINewActionParamValue(&valueParameterBlock);
		if (valueParameterBlock)
		{
			// see AIDocumentation.h 
			result = sAIActionManager->AIActionSetString(valueParameterBlock, 'name', "D:\\Code\\IllustratorSimplePlugin\\MyQTUI\\image.png");
			result = sAIActionManager->AIActionSetString(valueParameterBlock, 'frmt', "Adobe PNG Format");
			result = sAIActionManager->AIActionSetString(valueParameterBlock, 'extn', "png");
			result = sAIActionManager->PlayActionEvent("adobe_exportDocument", dialogStatus, valueParameterBlock);
			result = sAIActionManager->AIDeleteActionParamValue(valueParameterBlock);
		}
		*/

		// see this: https://github.com/mikeswanson/Ai2Canvas/blob/master/Source/Canvas.cpp

		/*
		AIErr result = kNoErr;
		AIDataFilter* dstFilter = 0;
		AIDataFilter* filter = 0;
		ai::UnicodeString file("file.png");   //file path c
		ai::FilePath fileP(file);

		try
		{

			result = sAIDataFilter->NewFileDataFilter(fileP, "write", 'prw', 'PNGf', &filter);
			aisdk::check_ai_error(result);

			result = sAIDataFilter->LinkDataFilter(dstFilter, filter);
			aisdk::check_ai_error(result);

			dstFilter = filter;

			// still to be configured, with your own values!!
			AIImageOptPNGParams2 params;
			params.versionOneSuiteParams.interlaced = ;
			params.versionOneSuiteParams.numberOfColors = ;
			params.versionOneSuiteParams.transparentIndex = ;
			params.versionOneSuiteParams.resolution = ;
			params.versionOneSuiteParams.outAlpha = ;
			params.versionOneSuiteParams.outWidth = ;
			params.versionOneSuiteParams.outHeight = ;
			params.antialias = ;

			// A cropping box for the art. If empty or degenerate, do not crop. 
			params.cropBox = ;
			params.backgroundIsTransparent = ;

			result = sAIImageOpt->MakePNG24(art, dstFilter, params, MyRasterizeProgressProc);
			aisdk::check_ai_error(result);

			if (dstFilter)
			{
				result = sAIDataFilter->UnlinkDataFilter(dstFilter, &dstFilter);
				aisdk::check_ai_error(result);
			}
		}
		catch (ai::Error& ex)
		{
			//Handle error
		}
		*/
		//return result;
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

ASErr EmptyPanelPlugin::Notify(AINotifierMessage *message)
{
	AIErr result = kNoErr;
	if (strcmp(message->type, kAIApplicationShutdownNotifier) == 0)
	{
	}
	return result;
}