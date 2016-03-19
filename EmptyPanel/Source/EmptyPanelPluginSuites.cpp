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


/**
* Reza Adhitya Saputra
* radhitya@uwaterloo.ca
*/

#include "EmptyPanelPluginSuites.h"
#include "Suites.hpp"

extern "C"
{
	AIArtSuite					*sAIArt;
	AIMatchingArtSuite			*sAIMatchingArt;
	AIUnicodeStringSuite		*sAIUnicodeString;
	SPBlocksSuite				*sSPBlocks;	
	AIMenuSuite					*sAIMenu;
	AIStringFormatUtilsSuite	*sAIStringFormatUtils;

	//AIPanelSuite				*sAIPanel;
	//AIPanelFlyoutMenuSuite	*sAIPanelFlyoutMenu;
	//AIControlBarSuite			*sAIControlBar;

	/* Added suites - Reza */
	AIDrawArtSuite				*sAIDrawArtSuite;
	AIPathSuite					*sAIPath;		  // reading path	
	AIDocumentSuite				*sAIDocument;
	AITimerSuite				*sAITimer;
	AIActionManagerSuite		*sAIActionManager;
	AIDataFilterSuite			*sAIDataFilter;
	AILayerSuite				*sAILayer;
	AIImageOptSuite				*sAIImageOpt;
	//AISwatchListSuite			*sAISwatchList;
	//AINotifierSuite			*sAINotifier;		// it's already is Suites.cpp
}

ImportSuite		gImportSuites[] = {
	kAIArtSuite,			   kAIArtSuiteVersion,				 &sAIArt,
	kAIMatchingArtSuite,	   kAIMatchingArtSuiteVersion,	     &sAIMatchingArt,
	kAIUnicodeStringSuite,	   kAIUnicodeStringSuiteVersion,	 &sAIUnicodeString,
	kSPBlocksSuite,			   kSPBlocksSuiteVersion,			 &sSPBlocks,	
	kAIMenuSuite,			   kAIMenuSuiteVersion,				 &sAIMenu,	
	kAIStringFormatUtilsSuite, kAIStringFormatUtilsSuiteVersion, &sAIStringFormatUtils,
	//kAIPanelSuite,		   kAIPanelSuiteVersion,			 &sAIPanel,
	//kAIPanelFlyoutMenuSuite, kAIPanelFlyoutMenuSuiteVersion,   &sAIPanelFlyoutMenu,
	//kAIControlBarSuite,	   kAIControlBarSuiteVersion,		 &sAIControlBar,
	
	/* Added suites - Reza */
	kAIDocumentSuite,		   kAIDocumentSuiteVersion,			 &sAIDocument,
	kAITimerSuite,			   kAITimerVersion,					 &sAITimer,	
	kAIDrawArtSuite,		   kAIDrawArtSuiteVersion,			 &sAIDrawArtSuite,	
	kAIPathSuite,			   kAIPathVersion,					 &sAIPath,
	kAIActionManagerSuite,	   kAIActionManagerVersion,			 &sAIActionManager,
	kAIDataFilterSuite,		   kAIDataFilterSuiteVersion,		 &sAIDataFilter,
	kAILayerSuite,			   kAILayerSuiteVersion,			 &sAILayer,
	kAIImageOptSuite,		   kAIImageOptSuiteVersion,			 &sAIImageOpt,
	//kAISwatchListSuite,	   kAISwatchListSuiteVersion,		 &sAISwatchList,
	nil, 0, nil
};
