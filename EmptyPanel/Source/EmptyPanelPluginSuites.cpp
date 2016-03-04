//========================================================================================
//  
//  $File: //ai/mainline/devtech/sdk/public/samplecode/EmptyPanel/source/EmptyPanelPluginSuites.cpp $
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

#include "EmptyPanelPluginSuites.h"

#include "Suites.hpp"

extern "C"
{
	AIArtSuite					*sAIArt;
	AIMatchingArtSuite			*sAIMatchingArt;
	AIUnicodeStringSuite		*sAIUnicodeString;
	SPBlocksSuite				*sSPBlocks;
	AIPanelSuite				*sAIPanel;
	AIPanelFlyoutMenuSuite		*sAIPanelFlyoutMenu;
	AIMenuSuite					*sAIMenu;
	AIStringFormatUtilsSuite	*sAIStringFormatUtils;
	AIControlBarSuite			*sAIControlBar;
	AIDrawArtSuite				*sAIDrawArtSuite;	// added by Reza
	AISwatchListSuite			*sAISwatchList;		// added by Reza
	AIDocumentSuite				*sAIDocument;		// added by Reza
	AITimerSuite				*sAITimer;			// added by Reza
	AIActionManagerSuite		*sAIActionManager;	// added by Reza
	AIDataFilterSuite			*sAIDataFilter;		// added by Reza
	//AINotifierSuite			*sAINotifier;		// it's already is Suites.cpp
}

ImportSuite		gImportSuites[] = {
	kAIArtSuite,			   kAIArtSuiteVersion,				 &sAIArt,
	kAIMatchingArtSuite,	   kAIMatchingArtSuiteVersion,	     &sAIMatchingArt,
	kAIUnicodeStringSuite,	   kAIUnicodeStringSuiteVersion,	 &sAIUnicodeString,
	kSPBlocksSuite,			   kSPBlocksSuiteVersion,			 &sSPBlocks,
	kAIPanelSuite,			   kAIPanelSuiteVersion,			 &sAIPanel,
	kAIMenuSuite,			   kAIMenuSuiteVersion,				 &sAIMenu,
	kAIPanelFlyoutMenuSuite,   kAIPanelFlyoutMenuSuiteVersion,   &sAIPanelFlyoutMenu,
	kAIStringFormatUtilsSuite, kAIStringFormatUtilsSuiteVersion, &sAIStringFormatUtils,
	kAIControlBarSuite,		   kAIControlBarSuiteVersion,		 &sAIControlBar,
	kAIDocumentSuite,		   kAIDocumentSuiteVersion,			 &sAIDocument,				// added by Reza
	kAITimerSuite,			   kAITimerVersion,					 &sAITimer,					// added by Reza
	kAIDrawArtSuite,		   kAIDrawArtSuiteVersion,			 &sAIDrawArtSuite,		    // added by Reza
	kAISwatchListSuite,		   kAISwatchListSuiteVersion,		 &sAISwatchList,			// added by Reza
	kAIActionManagerSuite,	   kAIActionManagerVersion,			 &sAIActionManager,			// added by Reza
	kAIDataFilterSuite,		   kAIDataFilterSuiteVersion,		 &sAIDataFilter,			// added by Reza
	//kAINotifierSuite,        kAINotifierVersion,               &sAINotifier,			    // added by Reza
	nil, 0, nil
};
