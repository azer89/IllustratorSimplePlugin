//========================================================================================
//  
//  $File: $
//
//  $Revision: $
//
//  Copyright 2012 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#import <Cocoa/Cocoa.h>
#include "AIControlBar.h"
#include "AITypes.h"
#include "EmptyPanelPluginSuites.h"

struct Opaque;

@interface BarController : NSViewController 
{
	IBOutlet NSTextField *current_width;
	IBOutlet NSButton *commit_current_width;
	IBOutlet NSTextField *max_width;
	IBOutlet NSButton *commit_max_width;
	IBOutlet NSTextField *min_width;
	IBOutlet NSButton *commit_min_width;
	IBOutlet NSTextField *x;
	IBOutlet NSTextField *y;
	IBOutlet NSButton *move;
	AIControlBarRef fControlBar;
}


- (void)commit_current_width:(id)sender;
- (void)commit_min_width:(id)sender;
- (void)commit_max_width:(id)sender;
- (void)move:(id)sender;
- (void)get:(id)sender;
- (void)setControlBarRef:(AIControlBarRef) input;

@end
