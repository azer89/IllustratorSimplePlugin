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
}

ImportSuite		gImportSuites[] = {
	kAIArtSuite, kAIArtSuiteVersion, &sAIArt,
	kAIMatchingArtSuite, kAIMatchingArtSuiteVersion, &sAIMatchingArt,
	kAIUnicodeStringSuite, kAIUnicodeStringSuiteVersion, &sAIUnicodeString,
	kSPBlocksSuite,	kSPBlocksSuiteVersion,	&sSPBlocks,
	kAIPanelSuite, kAIPanelSuiteVersion, &sAIPanel,
	kAIMenuSuite, kAIMenuSuiteVersion, &sAIMenu,
	kAIPanelFlyoutMenuSuite, kAIPanelFlyoutMenuSuiteVersion, &sAIPanelFlyoutMenu,
	kAIStringFormatUtilsSuite, kAIStringFormatUtilsSuiteVersion, &sAIStringFormatUtils,
	kAIControlBarSuite, kAIControlBarSuiteVersion, &sAIControlBar,
	nil, 0, nil
};
