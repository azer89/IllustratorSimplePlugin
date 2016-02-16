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

#include "IllustratorSDK.h"
#include "Suites.hpp"

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

// Suite externs
extern "C" AIArtSuite				*sAIArt;
extern "C" AIMatchingArtSuite		*sAIMatchingArt;
extern "C" AIUnicodeStringSuite		*sAIUnicodeString;
extern "C" AIPanelSuite				*sAIPanel;
extern "C" AIPanelFlyoutMenuSuite	*sAIPanelFlyoutMenu;
extern "C" AIMenuSuite				*sAIMenu;
extern "C" AIStringFormatUtilsSuite *sAIStringFormatUtils;
extern "C" SPBlocksSuite			*sSPBlocks;
extern "C" AIControlBarSuite		*sAIControlBar;
extern "C" AIDocumentSuite			*sAIDocument;	// added by reza
extern "C" AITimerSuite				*sAITimer; // added by reza

#endif   // __EmptyPanelPluginSuites_H__
