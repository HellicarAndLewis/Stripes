/*
 *  StripesController.h
 *  uniqloHAndL
 *
 *  Created by Joel Gethin Lewis on 22/11/2010.
 *  Copyright 2010 Hellicar&Lewis. All rights reserved.
 *
 */

#pragma once;

#include "ofMain.h"

#include <vector>

#include "BaseStripe.h"
#include "BasicStripe.h"
#include "GradientStripe.h"
#include "TwoColourHardStripe.h"
#include "TallFourColourHardGradientStripe.h"
#include "EnergyGradientStripe.h"
#include "EnergyGradientStripeColourChange.h"
#include "EnergyFourColourHardGradientStripe.h"
#include "EnergyFillsFourColourHardGradientStripeColourChange.h"

#include "ofxCvTrackedBlob.h"

#include "CPUImageFilter.h"

#include "ofxCvOpticalFlowLK.h"

#include "ofxVec2f.h"

class StripesController { //initally from ofRectangle, without the cruft
	
public:
	StripesController(); //constructor;
	~StripesController(); //destructor;
	
	void update(float timeElapsed, CPUImageFilter* greyDifferenceImage, ofxCvOpticalFlowLK* opticalFlow);
	void draw();
	
	void resizeStripes(int newStripes);
	
	void mouseMoved(int x,int y);
	
	void blobMoved(ofxCvTrackedBlob* aBlob);
	
	float relativeHighPointOfDiffInStripe(int stripe, CPUImageFilter* greyDifferenceImage);
	float absoluteNewEnergyInStripe(int stripe, ofxCvOpticalFlowLK* opticalFlow);
	
public:
	vector <BaseStripe *> stripes; //vector of stripes
private:
	float totalTimeElapsed;
	float timeOfLastReset;
};