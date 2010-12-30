#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

#include "AppSettings.h"

#include "ofxOpenCv.h"


	// from theo github https://github.com/ofTheo/ofxControlPanel , with some new bits from JGL

#include "ofxControlPanel.h"

#include "StripesController.h"

	//from Theo OpenFrameworks post: http://www.openframeworks.cc/forum/viewtopic.php?f=9&t=371&start=15

#include "renderManager.h"

	//all from openTSPS: https://github.com/labatrockwell/openTSPS

 /*
 *  TSPSPeopleVision
 *
 *  Created by Joshua Walton on 12/7/09.
 *  Copyright 2009 Lab at Rockwell Group. All rights reserved.
 *
 
 Portions of this software are distributed under the GPL and the MIT license.
 
 The MIT License
 
 Copyright (c) 2010 Rockwell Group LLC
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 */

#include "CPUImageFilter.h"
#include "ofxCvOpticalFlowLK.h"
#include "ofxCvBlobTracker.h"

class testApp : public ofBaseApp{ //, ofxCvBlobListener{

public:

	void setup();	
	void update();
	void draw();

	void keyPressed  (int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
		//new events on blobs, ported from OpenTSPS
//	void blobOn( int x, int y, int id, int order);
//	void blobMoved( int x, int y, int id, int order);
//	void blobOff( int x, int y, int id, int order);
	
public:

	ofxControlPanel gui;	

	int camWidth, camHeight; 

		//mouse in my house
	bool bShowMouse;	
	
	StripesController stripesController;
	
	float timeOfStartup;
	float timeOfLastFrame;
	
		//FBO warping now
	renderManager rm;
	
	ofRectangle guiIn;
	ofRectangle guiOut;	
	
		//camera
	
	ofVideoGrabber 		videoGrabber;	
	
		//cv
	ofxCvColorImage		videoColourCvImage;
	
	ofxCvGrayscaleImage		videoGreyscaleCvImage;
	
		//camera cropping
	ofxCvGrayscaleImage		videoGreyscaleCvImagePreWarp;
	ofPoint		srcPts[4];
	ofPoint		dstPts[4];	
	
		//new objects needed for OpenTSPS port
	ofxCvGrayscaleImage greyBackground;	
	ofxCvShortImage		shortBgImg;
	CPUImageFilter		greyDiff;
	ofxCvOpticalFlowLK	opticalFlow;	
	
//	ofxCvContourFinder 	contourFinder;
//	ofxCvBlobTracker persistentTracker;	
	
	ofxCvGrayscaleImage greySmallImage;
	ofxCvGrayscaleImage previousgreySmallImage;
};

#endif
