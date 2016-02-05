//========================================================================================
//  
//  $File: //ai/mainline/devtech/sdk/public/samplecode/Tutorial/Source/TutorialSuites.cpp $
//
//  $Revision: #1 $
//
//  Copyright 2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "IllustratorSDK.h"
#include "TutorialSuites.h"

extern "C"
{
	AIFilterSuite*				sAIFilter = nil;
	SPBlocksSuite*				sSPBlocks = nil;
	AIArtSuite*					sAIArt = nil;
	AIPathSuite*				sAIPath = nil;
	AIRealMathSuite*			sAIMath = nil;
	AIRandomSuite*				sAIRandom = nil;
	AIDocumentViewSuite*		sAIDocumentView = nil;
	AIToolSuite*				sAITool = nil;
	AIMatchingArtSuite*			sAIMatchingArt = nil;
	AIActionManagerSuite*		sAIActionManager = nil;
	AIMenuSuite*				sAIMenu = nil;
	AIUnicodeStringSuite*		sAIUnicodeString = nil;
	AIMdMemorySuite*			sAIMDMemory = nil;
	AIStringFormatUtilsSuite*	sAIStringFormatUtils = nil;
};

ImportSuite gImportSuites[] =
{
	kAIFilterSuite, kAIFilterVersion, &sAIFilter,
	kSPBlocksSuite, kSPBlocksSuiteVersion, &sSPBlocks,
	kAIArtSuite, kAIArtVersion, &sAIArt,
	kAIPathSuite, kAIPathVersion, &sAIPath,
	kAIRealMathSuite, kAIRealMathVersion, &sAIMath,
	kAIRandomSuite, kAIRandomVersion, &sAIRandom,
	kAIDocumentViewSuite, kAIDocumentViewVersion, &sAIDocumentView,
	kAIToolSuite, kAIToolVersion, &sAITool,
	kAIMatchingArtSuite, kAIMatchingArtVersion, &sAIMatchingArt,
	kAIActionManagerSuite, kAIActionManagerSuiteVersion, &sAIActionManager,
	kAIMenuSuite, kAIMenuSuiteVersion, &sAIMenu,
	kAIUnicodeStringSuite, kAIUnicodeStringSuiteVersion, &sAIUnicodeString,
	kAIMdMemorySuite, kAIMdMemorySuiteVersion, &sAIMDMemory,
	kAIStringFormatUtilsSuite, kAIStringFormatUtilsSuiteVersion, &sAIStringFormatUtils,
	nil, 0, nil
};
