/*
 *  StripesController.cpp
 *  uniqloHAndL
 *
 *  Created by Joel Gethin Lewis on 22/11/2010.
 *  Copyright 2010 Hellicar&Lewis. All rights reserved.
 *
 */

#include "StripesController.h"

StripesController::StripesController(){
	totalTimeElapsed = 0.f;
	timeOfLastReset = 0.f;
}

StripesController::~StripesController(){
	
	for(int i = 0; i < stripes.size(); i++){
		if( stripes[i] != NULL ){
			delete (stripes[i]);
			stripes[i] = NULL;
		}
	}
	
	stripes.clear();
}

void StripesController::update(float timeElapsed, CPUImageFilter* greyDifferenceImage, ofxCvOpticalFlowLK* opticalFlow){
	
	
	for(int i=0; i < stripes.size(); i++){
		float highPointOfDiffRelativeValue = relativeHighPointOfDiffInStripe(i, greyDifferenceImage);
		
		float extraEnergy = absoluteNewEnergyInStripe(i, opticalFlow);
		
		stripes[i]->update(timeElapsed, highPointOfDiffRelativeValue, extraEnergy);
	}
	
	totalTimeElapsed += timeElapsed;
	
	if((totalTimeElapsed-timeOfLastReset) > settings.TIME_BETWEEN_CYCLES){
		resizeStripes(stripes.size());
	}
}

void StripesController::draw(){
	for(int i=0; i < stripes.size(); i++){
		//cout << "Drawing the " << i << "th stripe" << endl;
		stripes[i]->draw();
	}	
}

void StripesController::resizeStripes(int newStripes){
	timeOfLastReset = totalTimeElapsed;
		// clear out the old
	
	float totalWidth = settings.STRIPES_WIDTH;
	float totalHeight = settings.STRIPES_HEIGHT;
	
	for(int i = 0; i < stripes.size(); i++){
		if( stripes[i] != NULL ){
			delete (stripes[i]);
			stripes[i] = NULL;
		}
	}
	
	stripes.clear();
	
		//in with the new, set up some values first
	float currentX = 0.f;
	float currentY = 0.f;
	
	float currentWidth = totalWidth / (float)newStripes;
	float currentHeight = totalHeight;
	
	float colourChange = 255.f/(float) newStripes; //just gradient for now
	
	ofColor currentColour;	
	
	int selector = ofRandom(0,6); ////ofRandomuf returns float between 0 and 1	
	
	for(int i =0; i < newStripes; i++){
		
		currentColour.r = ofRandom(0,255);
		currentColour.g = ofRandom(0,255);
		currentColour.b = ofRandom(0,255);
		
		switch (selector){
			case 0:{
				//make a tall four colour hard gradient stripe
				ofColor c2;	
				
				c2.r = ofRandom(0,255);
				c2.g = ofRandom(0,255);
				c2.b = ofRandom(0,255);	
			
				ofColor c3;	
				
				c3.r = ofRandom(0,255);
				c3.g = ofRandom(0,255);
				c3.b = ofRandom(0,255);	
				
				ofColor c4;	
				
				c4.r = ofRandom(0,255);
				c4.g = ofRandom(0,255);
				c4.b = ofRandom(0,255);				
				
				TallFourColourHardGradientStripe * tfchgs = new TallFourColourHardGradientStripe(currentX, currentY,currentWidth, 
													 currentHeight, currentColour, c2, c3, c4, 0.f, ofRandom(0.01f, 0.2f));
				stripes.push_back(tfchgs);	
				break;				
			}
			case 1:{
					//make an  energy four colour hard gradient stripe
				ofColor c2;	
				
				c2.r = ofRandom(0,255);
				c2.g = ofRandom(0,255);
				c2.b = ofRandom(0,255);	
				
				ofColor c3;	
				
				c3.r = ofRandom(0,255);
				c3.g = ofRandom(0,255);
				c3.b = ofRandom(0,255);	
				
				ofColor c4;	
				
				c4.r = ofRandom(0,255);
				c4.g = ofRandom(0,255);
				c4.b = ofRandom(0,255);				
				
				EnergyFourColourHardGradientStripe * efchgs = new EnergyFourColourHardGradientStripe(currentX, currentY,currentWidth, 
																									 currentHeight, currentColour, c2, c3, c4, 0.f, ofRandom(0.01f, 0.2f));
				stripes.push_back(efchgs);	
				break;
			}
			case 2:{
					//make an energy gradient stripe
				ofColor c2;	
				
				c2.r = ofRandom(0,255);
				c2.g = ofRandom(0,255);
				c2.b = ofRandom(0,255);	
				
				ofColor c3;	
				
				c3.r = ofRandom(0,255);
				c3.g = ofRandom(0,255);
				c3.b = ofRandom(0,255);	
						
				EnergyGradientStripe * egs = new EnergyGradientStripe(currentX, currentY,currentWidth,
																	  currentHeight, currentColour, c2, c3, 0.f, 0.1f);	
					//same vel for all stripes
				
				stripes.push_back(egs);	
				break;
			} 
			case 3:{
					//make an energy gradient stripe colour chagnge
				ofColor c2;	
				
				c2.r = ofRandom(0,255);
				c2.g = ofRandom(0,255);
				c2.b = ofRandom(0,255);	
				
				ofColor c3;	
				
				c3.r = ofRandom(0,255);
				c3.g = ofRandom(0,255);
				c3.b = ofRandom(0,255);	
				
					//same vel for all stripes			
				EnergyGradientStripeColourChange * egscc = new EnergyGradientStripeColourChange(currentX, currentY,currentWidth,
																								currentHeight, currentColour, c2, c3, 0.f, 0.1f);
					//same vel for all stripes
				
				stripes.push_back(egscc);	
				break;
			}
			case 4:{
					//make an  energy fills four colour hard gradient stripe
				ofColor c2;	
				
				c2.r = ofRandom(0,255);
				c2.g = ofRandom(0,255);
				c2.b = ofRandom(0,255);	
				
				ofColor c3;	
				
				c3.r = ofRandom(0,255);
				c3.g = ofRandom(0,255);
				c3.b = ofRandom(0,255);	
				
				ofColor c4;	
				
				c4.r = ofRandom(0,255);
				c4.g = ofRandom(0,255);
				c4.b = ofRandom(0,255);				
				
				EnergyFillsFourColourHardGradientStripeColourChange * effchgscc = new EnergyFillsFourColourHardGradientStripeColourChange(currentX, currentY,currentWidth, 
																									 currentHeight, currentColour, c2, c3, c4, 0.f, ofRandom(0.01f, 0.2f));
				stripes.push_back(effchgscc);	
				break;
			}				
			default:{
					//make an EnergyFillsFourColourHardGradientStripeColourChange
				ofColor c2;	
				
				c2.r = ofRandom(0,255);
				c2.g = ofRandom(0,255);
				c2.b = ofRandom(0,255);	
				
				ofColor c3;	
				
				c3.r = ofRandom(0,255);
				c3.g = ofRandom(0,255);
				c3.b = ofRandom(0,255);	
				
				ofColor c4;	
				
				c4.r = ofRandom(0,255);
				c4.g = ofRandom(0,255);
				c4.b = ofRandom(0,255);				
				
				EnergyFillsFourColourHardGradientStripeColourChange * effchgscc = new EnergyFillsFourColourHardGradientStripeColourChange(currentX, currentY,currentWidth, 
																								 currentHeight, currentColour, c2, c3, c4, 0.f, ofRandom(0.01f, 0.2f));
				stripes.push_back(effchgscc);	
				break;
			}
		}
		
		currentX += currentWidth;
	}
}

void StripesController::mouseMoved(int x,int y){
	
	float xPositionNormalised = (float)x/ofGetWidth();
	
	xPositionNormalised = ofClamp(xPositionNormalised, 0.f, 1.f);
	
	int indexOfTheStripeToMouseMove = xPositionNormalised*(stripes.size()-1);
	
	stripes[indexOfTheStripeToMouseMove]->mouseMoved(x,y);
}

void StripesController::blobMoved(ofxCvTrackedBlob* aBlob){
		//more for constant perfrormance drain and simplicity than elegance, in contrast to above
	
	for(int i = 0; i < stripes.size(); i++){
		stripes[i]->blobMoved(aBlob);
	}	
}

float StripesController::relativeHighPointOfDiffInStripe(int stripe, CPUImageFilter* greyDifferenceImage){
	float relativeStripeX = stripes[stripe]->x / settings.STRIPES_WIDTH;
	float relativeStripeWidth = stripes[stripe]->width / settings.STRIPES_WIDTH;
	
		//go through the image 
	
	int startX	= relativeStripeX * greyDifferenceImage->width;
	int endX	= startX + (relativeStripeWidth * greyDifferenceImage->width);
	
	int currentY = 0;
	
	bool stop = false;
	
	for(int j = 0; (j < greyDifferenceImage->height) && !stop; j++){
		for(int i = startX; (i < endX) && !stop; i++){
			int pixelValue = greyDifferenceImage->getPixels()[(j*greyDifferenceImage->width)+i];
			
			if(pixelValue > 0){
				stop = true;
			}
		}
		
		currentY++;
	}
	
	return ((float)currentY)/greyDifferenceImage->height;
}

float StripesController::absoluteNewEnergyInStripe(int stripe, ofxCvOpticalFlowLK* opticalFlow){
	float absoluteNewEnergy = 0.f;

	float relativeStripeX = stripes[stripe]->x / settings.STRIPES_WIDTH;
	float relativeStripeWidth = stripes[stripe]->width / settings.STRIPES_WIDTH;
	
	float stripeXInOpticalFlow = relativeStripeX * opticalFlow->getWidth();
	float stripeYInOpticalFlow = 0;
	float stripeWidthInOpticalFlow = relativeStripeWidth * opticalFlow->getWidth();
	float stripeHeightInOpticalFlow = opticalFlow->getHeight();
	
	ofPoint averageMotion = opticalFlow->flowInRegion(stripeXInOpticalFlow,stripeYInOpticalFlow,stripeWidthInOpticalFlow,stripeHeightInOpticalFlow);
	
	ofxVec2f vecOfAverageMotion = ofxVec2f(averageMotion);
	
	absoluteNewEnergy = vecOfAverageMotion.length();
	
	return absoluteNewEnergy;
}




