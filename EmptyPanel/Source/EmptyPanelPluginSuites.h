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



/* AI suite headers */
#include "AIArt.h"
#include "AIMatchingArt.h"
#include "AIUnicodeString.h"
#include "AIUser.h"
#include "AIStringFormatUtils.h"
#include "SPBlocks.h"

/* Added suites - Reza */
#include "AIDrawArt.h"
#include "AISwatchList.h"	
#include "AIDataFilter.h"
#include "AIActionManager.h"
#include "AIDocument.h"
#include "AiTimer.h"

/* not used */
//#include "AIPanel.h"
//#include "AIMenu.h"
//#include "AIControlBar.h"

/* moved to cpp */
//#include "IllustratorSDK.h"
//#include "Suites.hpp"

// Suite externs
extern "C" AIUnicodeStringSuite		*sAIUnicodeString;
extern "C" AIMenuSuite				*sAIMenu;
extern "C" AIStringFormatUtilsSuite *sAIStringFormatUtils;
extern "C" SPBlocksSuite			*sSPBlocks;

//extern "C" AIPanelSuite			*sAIPanel;
//extern "C" AIPanelFlyoutMenuSuite	*sAIPanelFlyoutMenu;
//extern "C" AIControlBarSuite		*sAIControlBar;

/* Added suites - Reza */
extern "C" AIArtSuite				*sAIArt;
extern "C" AIMatchingArtSuite		*sAIMatchingArt;
extern "C"  AIDrawArtSuite			*sAIDrawArtSuite; // reading drawing data
extern "C"  AISwatchListSuite		*sAISwatchList;   // reading drawing data
extern "C" AIDocumentSuite			*sAIDocument;	  // what is this I don't know
extern "C" AITimerSuite				*sAITimer;        // for periodic timer
extern "C" AIDataFilterSuite		*sAIDataFilter;   // for writing png ?
extern "C" AILayerSuite				*sAILayer;		  // handling layers
extern "C" AIActionManagerSuite		*sAIActionManager;

#endif   // __EmptyPanelPluginSuites_H__
