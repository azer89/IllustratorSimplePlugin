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

#include <AIImageOptimization.h>

//QT
#include <QTextEdit>
#include <iostream>
#include "myqtui.h"
#include <QtWidgets/QApplication>
#include "SystemParams.h"

extern "C" SPBasicSuite*  sSPBasic;

#ifdef MAC_ENV
NSView* nibView = nil;
NSView* controlPanelNibView = nil;
#endif

// stolen from http://blog.mikeswanson.com/ai2canvas
AIBoolean ProgressProc(ai::int32 current, ai::int32 total);

// stolen from http://blog.mikeswanson.com/ai2canvas
// Outside of namespace
// TODO: Fix this
AIBoolean ProgressProc(ai::int32 current, ai::int32 total)
{
	(void)current;
	(void)total;
	return true;
}

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
		kMenuItemNoOptions, &_menuItemHandle);
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
	ASErr error = kNoErr;

	if (message->menuItem == _menuItemHandle)
	{	
		error = DrawArtExample();
		error = RenderDocument2();

		/* we show our UI*/
		my_qt_window->show();
		my_qt_window->setFocus();	// should call this or the window will be hidden behind
		//my_qt_app->exec();		// Note that I don't use QApplication.exec()		

		
	}	

	return error;
}

ASErr EmptyPanelPlugin::DrawArtExample()
{
	ASErr error = kNoErr;

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

	error = sAIDrawArtSuite->DestroyImagePort(port.port);

	// Apparently this will give you error if you don't have an active document
	if (error) { sAIUser->MessageAlert(ai::UnicodeString("Error !")); }

	return error;
}

ASErr EmptyPanelPlugin::RenderDocument1()
{
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

	return kNoErr;
}

ASErr EmptyPanelPlugin::RenderDocument2()
{
	/*
	Rules:
		- Should exactly has one layer
		- All paths are grouped
	*/

	ai::int32 layerCount = 0;

	// How many layers in this document?
	sAILayer->CountLayers(&layerCount);

	int intLayerCount = layerCount;
	my_qt_window->GetTextEdit()->append("Num of layers: " + QString::number(intLayerCount));
	
	/* only the first layer */
	AILayerHandle layerHandle = 0;
	sAILayer->GetNthLayer(0, &layerHandle);

	/* Get the first art in this layer */
	AIArtHandle artHandle = 0;
	sAIArt->GetFirstArtOfLayer(layerHandle, &artHandle);

	//if (artHandle)
	//{
	//	my_qt_window->GetTextEdit()->append("Getting an art");
	//}

	RasterizeArtToPNG(artHandle, SystemParams::temp_png_location);

	return kNoErr;
}

/*
Code is stolen from https://github.com/mikeswanson/Ai2Canvas

Given an art handle, rasterizes to a file at the given path
NOTE: While width and height are passed, the resulting file is often of a different size, which negatively affects positioning
See discussion thread: http://forums.adobe.com/thread/603776?tstart=0
*/
void EmptyPanelPlugin::RasterizeArtToPNG(AIArtHandle artHandle, const std::string& path)
{
	ai::FilePath filePath;
	filePath.Set(ai::UnicodeString(path));

	AIRealRect bounds;
	sAIArt->GetArtBounds(artHandle, &bounds);
	AIReal width = bounds.right - bounds.left;
	AIReal height = bounds.top - bounds.bottom;

	my_qt_window->GetTextEdit()->append("bounds.right: " + QString::number(bounds.right));
	my_qt_window->GetTextEdit()->append("bounds.left: " + QString::number(bounds.left));
	my_qt_window->GetTextEdit()->append("bounds.top: " + QString::number(bounds.top));
	my_qt_window->GetTextEdit()->append("bounds.bottom: " + QString::number(bounds.bottom));

	AIErr result = kNoErr;
	AIDataFilter *dstFilter = NULL;
	AIDataFilter *filter = NULL;
	if (!result)
	{
		result = sAIDataFilter->NewFileDataFilter(filePath, "write", 'prw', 'PNGf', &filter);
	}

	if (!result) 
	{
		result = sAIDataFilter->LinkDataFilter(dstFilter, filter);
		dstFilter = filter;
	}

	// Set PNG parameters
	AIImageOptPNGParams2 params;
	params.versionOneSuiteParams.interlaced = false;
	params.versionOneSuiteParams.numberOfColors = 16777216;
	params.versionOneSuiteParams.transparentIndex = 0;
	//params.versionOneSuiteParams.resolution = 72.0f;
	params.versionOneSuiteParams.resolution = 1000.0f;
	params.versionOneSuiteParams.outAlpha = true;
	params.versionOneSuiteParams.outWidth = (ASInt32)width;
	params.versionOneSuiteParams.outHeight = (ASInt32)height;

	//We assume that the basic resolution of illustrator is 72 dpi
	AIReal resolutionRatio = 1.0f;
	AIReal minDim = min(width, height) * resolutionRatio;
	AIReal maxDim = max(width, height) * resolutionRatio;
	AIReal ratio = 1;

	if (minDim < 1)
	{
		ratio = 1 / minDim;
		minDim *= ratio;
		maxDim *= ratio;
	}

	if (maxDim > 65535)
	{
		ratio *= 65535 / maxDim;
	}

	//Here we tune the resolution parameter to comply to minRasterizationDimension and
	//maxRasterizationDimension constraints
	//We assume that the basic resolution of illustrator is 72 dpi
	params.versionOneSuiteParams.resolution *= (AIFloat)ratio;

	params.antialias = true;
	/* A cropping box for the art. If empty or degenerate, do not crop. */
	AIRealRect crop;
	crop.left = 0.0f;
	crop.top = 0.0f;
	crop.right = 0.0f;
	crop.bottom = 0.0f;
	params.cropBox = crop;
	params.backgroundIsTransparent = true;
	/* When backgroundIsTransparent is false, rasterize against this matte color. */
	/*params.matteColor.red = 1.0f;
	params.matteColor.green = 1.0f;
	params.matteColor.blue = 1.0f; */

	// Make PNG
	result = sAIImageOpt->MakePNG24(artHandle, dstFilter, params, ProgressProc);

	if (dstFilter)
	{
		AIErr tmpresult = sAIDataFilter->UnlinkDataFilter(dstFilter, &dstFilter);
		if (!result)
			result = tmpresult;
	}
}

ASErr EmptyPanelPlugin::Notify(AINotifierMessage *message)
{
	AIErr result = kNoErr;
	if (strcmp(message->type, kAIApplicationShutdownNotifier) == 0)
	{
	}
	return result;
}