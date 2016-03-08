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
// _my_qt_window->GetTextEdit()->append("Your message here");

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

//#include "SDKDef.h"
//#include "SDKAboutPluginsHelper.h"
//#include "EmptyPanleID.h"

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
	_my_qt_app(0),
	_my_qt_window(0)
{
	//strncpy(fPluginName, kEmptyPanelPluginName, kMaxStringLength);
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

	// kCallerAITimer
	if (strcmp(caller, kCallerAITimer) == 0)
	{
		// timer is triggered, do something
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
	_my_qt_app = new QApplication (my_argc, my_argv);
	_my_qt_window = new MyQTUI();
	//_my_qt_app->exec();

	AINotifierHandle appShutDownNotifier;
	error = sAINotifier->AddNotifier(fPluginRef, "AI Application Shutdown Notifier", kAIApplicationShutdownNotifier, &appShutDownNotifier);
	if (error) { return error; }
	
	//AIErr error = kNoErr;

	// Add menu item
	error = sAIMenu->AddMenuItemZString(fPluginRef, "<Plugin>", kOtherPalettesMenuGroup, ZREF("<Plugin>"), kMenuItemNoOptions, &_menuItemHandle);
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
	if (_my_qt_window)
	{
		_my_qt_window->close();
		delete _my_qt_window;
	}

	// added by Reza
	// Delete Qt instance
	if (_my_qt_app) 
	{ 
		_my_qt_app->quit();
		delete _my_qt_app; 
	}	

	return kNoErr;
}

ASErr EmptyPanelPlugin::GoMenuItem(AIMenuMessage *message)
{
	ASErr error = kNoErr;
	if (message->menuItem == _menuItemHandle)
	{	
		//error = DrawArtExample();
		error = RenderDocument();

		/* we show our UI*/
		_my_qt_window->show();
		_my_qt_window->setFocus();	// should call this or the window will be hidden behind
		//_my_qt_app->exec();		// Note that I don't use QApplication.exec()			
	}	
	return error;
}

/*
Rules:
- Should exactly has one layer (TBD...)
- All paths are in a single layer
*/
ASErr EmptyPanelPlugin::RenderDocument()
{
	/* Clear data */
	this->_paths.clear();

	/* How many layers in this document? */
	ai::int32 layerCount = 0;
	
	sAILayer->CountLayers(&layerCount);
	int intLayerCount = layerCount;
	_my_qt_window->GetTextEdit()->append("Num of layers: " + QString::number(intLayerCount));
	_my_qt_window->GetTextEdit()->append("   ");
	
	/* only the first layer */
	AILayerHandle layerHandle = 0;
	sAILayer->GetNthLayer(0, &layerHandle);

	/* Get the first art in this layer */
	AIArtHandle artHandle = 0;
	sAIArt->GetFirstArtOfLayer(layerHandle, &artHandle);

	/* Fun things */
	RasterizeArtToPNG(artHandle, SystemParams::temp_png_location);
	RenderPathGroup(artHandle);

	return kNoErr;
}

/*
Input should be a LAYER
*/
void EmptyPanelPlugin::RenderPathGroup(AIArtHandle artHandle)
{
	// Get the first art element in the group
	AIArtHandle aArtHandle = nil;
	sAIArt->GetArtFirstChild(artHandle, &aArtHandle);

	std::vector<AIArtHandle> artHandles;
	do
	{

		ParsePath(aArtHandle);

		// Add this art handle
		artHandles.push_back(aArtHandle);

		// Find the next sibling
		sAIArt->GetArtSibling(aArtHandle, &aArtHandle);
	} 
	while (aArtHandle != nil);

	//_my_qt_window->GetTextEdit()->append("number of child: " + QString::number(artHandles.size()));
	_my_qt_window->GetTextEdit()->append("number of paths: " + QString::number(_paths.size()));
}

/*
Code is stolen from https://github.com/mikeswanson/Ai2Canvas
This function parses a single path art
*/
void EmptyPanelPlugin::ParsePath(AIArtHandle artHandle)
{
	// get art name
	ai::UnicodeString artName;
	AIBoolean isDefaultName = false;
	sAIArt->GetArtName(artHandle, artName, &isDefaultName);
	_my_qt_window->GetTextEdit()->append("art name: " + QString::fromStdString(artName.as_UTF8()));

	// get art type
	short artType = 0;
	sAIArt->GetArtType(artHandle, &artType);
	//my_qt_window->GetTextEdit()->append("art type: " + QString::number(artType));
	if (artType == kPathArt)
	{
		// Create your own Path
		APath aPath(true);

		// is closed ?
		AIBoolean pathClosed = false;
		sAIPath->GetPathClosed(artHandle, &pathClosed);
		//if (pathClosed) { my_qt_window->GetTextEdit()->append("a closed path !"); }

		// number of segments
		short segmentCount = 0;
		sAIPath->GetPathSegmentCount(artHandle, &segmentCount);
		_my_qt_window->GetTextEdit()->append("segmentCount: " + QString::number(segmentCount));		

		/* Get the path starting point */
		AIPathSegment segment;
		sAIPath->GetPathSegments(artHandle, 0, 1, &segment);
		/* Remember the first segment, in case we have to create an extra segment to close the figure */
		AIPathSegment firstSegment = segment;

		// Track the last out point
		// y is negative ?
		AIPathSegment previousSegment = segment;
		//_my_qt_window->GetTextEdit()->append("x: " + QString::number(previousSegment.p.h) + " y: " + QString::number(-previousSegment.p.v));
		aPath.points.push_back(AVector(previousSegment.p.h, -previousSegment.p.v));

		// Loop through each segment
		for (short segmentIndex = 1; segmentIndex < segmentCount; segmentIndex++)
		{
			sAIPath->GetPathSegments(artHandle, segmentIndex, 1, &segment);
			//RenderSegment(previousSegment, segment, depth);
			previousSegment = segment;
			// y is negative ?
			//_my_qt_window->GetTextEdit()->append("x: " + QString::number(previousSegment.p.h) + " y: " + QString::number(-previousSegment.p.v));
			aPath.points.push_back(AVector(previousSegment.p.h, -previousSegment.p.v));
		}
		
		_paths.push_back(aPath);

		_my_qt_window->GetTextEdit()->append("   ");
	}	
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

	/*
	my_qt_window->GetTextEdit()->append("width: " + QString::number(width));
	my_qt_window->GetTextEdit()->append("height: " + QString::number(height));

	my_qt_window->GetTextEdit()->append("bounds.right: " + QString::number(bounds.right));
	my_qt_window->GetTextEdit()->append("bounds.left: " + QString::number(bounds.left));
	my_qt_window->GetTextEdit()->append("bounds.top: " + QString::number(bounds.top));
	my_qt_window->GetTextEdit()->append("bounds.bottom: " + QString::number(bounds.bottom));
	*/

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
	params.versionOneSuiteParams.resolution = 72.0f; // in DPI
	//params.versionOneSuiteParams.resolution = 1000.0f;
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

// from original sample code
ASErr EmptyPanelPlugin::Notify(AINotifierMessage *message)
{
	AIErr result = kNoErr;
	if (strcmp(message->type, kAIApplicationShutdownNotifier) == 0)
	{
	}
	return result;
}