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


#import "BarController.h"

@implementation BarController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) 
	{
    }
    
    return self;
}

- (IBAction)move:(id)sender
{
	int xIn = [x intValue];
	int yIn = [y intValue];
	AIPoint point = {xIn,yIn};
	sAIControlBar->Move(fControlBar,point);
}

- (IBAction)get:(id)sender
{
	AIReal width, minWidth, maxWidth;
	sAIControlBar->GetWidth(fControlBar,width);
	sAIControlBar->GetMinimumWidth(fControlBar,minWidth);
	sAIControlBar->GetMaximumWidth(fControlBar,maxWidth);
	[current_width setIntValue:width];
	[min_width setIntValue:minWidth];
	[max_width setIntValue:maxWidth];
}

- (IBAction)commit_min_width:(id)sender
{
	int min = [min_width intValue];
	sAIControlBar->SetMinimumWidth(fControlBar,min);
}

- (IBAction)commit_max_width:(id)sender
{
	int max = [max_width intValue];
	sAIControlBar->SetMaximumWidth(fControlBar,max);
}

- (IBAction)commit_current_width:(id)sender
{
	int current = [current_width intValue];
	sAIControlBar->SetWidth(fControlBar,current);
}

- (void)setControlBarRef:(AIControlBarRef)input
{
	fControlBar = input;
}

@end
