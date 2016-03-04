//========================================================================================
//  
//  $File: //ai/mainline/devtech/sdk/public/samplecode/EmptyPanel/source/EmptyPanelPluginSuites.h $
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

#ifndef __EmptyPanelPluginSuites_H__
#define __EmptyPanelPluginSuites_H__

// moved to cpp
//#include "IllustratorSDK.h"
//#include "Suites.hpp"

// AI suite headers
#include "AIArt.h"
#include "AIMatchingArt.h"
#include "AIUnicodeString.h"
#include "AIUser.h"
#include "AIPanel.h"
#include "AIMenu.h"
#include "AIStringFormatUtils.h"
#include "SPBlocks.h"
#include "AIControlBar.h"
#include "AIDrawArt.h"		// added by Reza
#include "AISwatchList.h"	// added by Reza
#include "AIDataFilter.h"
#include "AIActionManager.h"

#include "AIDocument.h"
#include "AiTimer.h"


// Suite externs
extern "C" AIArtSuite				*sAIArt;

// This suite allows you to get lists of art objects that are currently selected, 
// or that match specified criteria, from among all available art objects, 
// or from artwork in a particular set of layers.

extern "C" AIMatchingArtSuite		*sAIMatchingArt;
extern "C" AIUnicodeStringSuite		*sAIUnicodeString;
extern "C" AIPanelSuite				*sAIPanel;
extern "C" AIPanelFlyoutMenuSuite	*sAIPanelFlyoutMenu;
extern "C" AIMenuSuite				*sAIMenu;
extern "C" AIStringFormatUtilsSuite *sAIStringFormatUtils;
extern "C" SPBlocksSuite			*sSPBlocks;
extern "C" AIControlBarSuite		*sAIControlBar;

extern "C"  AIDrawArtSuite			*sAIDrawArtSuite; // reading drawing data
extern "C"  AISwatchListSuite		*sAISwatchList;   // reading drawing data

extern "C" AIDocumentSuite			*sAIDocument;	 // what is this I don't know
extern "C" AITimerSuite				*sAITimer;       // for periodic timer
extern "C" AIDataFilterSuite		*sAIDataFilter;  // for writing png ?

extern "C" AIActionManagerSuite		*sAIActionManager;

#endif   // __EmptyPanelPluginSuites_H__
