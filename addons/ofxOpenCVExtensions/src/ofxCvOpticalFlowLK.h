	//
	// ofxCvOpticalFlowLK.h - a OpenCV cvOpticalFlowLK warpper for openFrameworks
	//
	// Copyright (C) 2008 Takashi Maekawa <takachin@generative.info> 
	//     All rights reserved.
	//     This is free software with ABSOLUTELY NO WARRANTY.
	//
	// You can redistribute it and/or modify it under the terms of 
	// the GNU Lesser General Public License.
	//

	// JGL extended to be drawable in the theo's gui  28/11/2010

#pragma once

#include "ofMain.h"
#include "ofxCvConstants.h"
#include "ofxCvGrayscaleImage.h"

class ofxCvOpticalFlowLK: public ofBaseDraws {

public:
	ofxCvOpticalFlowLK(void);
	~ofxCvOpticalFlowLK(void);
	
	void allocate(int _w, int _h);
	
	void calc( ofxCvGrayscaleImage & pastImage,
			  ofxCvGrayscaleImage & currentImage,
			  int size);
	
	void setCalcStep(int _cols, int _rows);
	
	void reset();
	
//	void draw();
//	void draw(int width, int height); removed for ofBaseDraws compatibility JGL
	
    virtual void  draw() { draw(0,0, (float)captureWidth, (float)captureHeight); };
    virtual void  draw( float x, float y ) { draw(x,y, (float)captureWidth, (float)captureHeight); };
    virtual void  draw( float x, float y, float w, float h );
	virtual void setAnchorPercent(float xPct, float yPct);
    virtual void setAnchorPoint(int x, int y);
	virtual void resetAnchor(); 
	
	virtual float getWidth() { return (float)captureWidth; };    //set after allocate
	virtual float getHeight() { return (float)captureHeight; };  //set after allocate		
	
	ofPoint flowAtPoint(int x, int y);
	ofPoint flowInRegion(float x, float y, float w, float h);
	ofPoint flowInRegion(ofRectangle roi);
	ofPoint averageFlowInRegion(float x, float y, float w, float h);
	ofPoint averageFlowInRegion(ofRectangle roi);
	
		//Used to filter noisey or erroneous vectors
	float minVector;
	float maxVector;
	
private:
	
	void boundsForRect(float x, float y, float w, float h, ofPoint* topLeft, ofPoint* bottomRight);
	
	static const int DEFAULT_CAPTURE_WIDTH = 320;
	static const int DEFAULT_CAPTURE_HEIGHT = 240;
	
//	int captureWidth;
//	int captureHeight;
	
	static const int DEFAULT_CAPTURE_COLS_STEP = 4;
	static const int DEFAULT_CAPTURE_ROWS_STEP = 4;
	
	int captureColsStep;
	int captureRowsStep;
	
	IplImage* vel_x;
	IplImage* vel_y;
	
protected:
	
    int  captureWidth;
    int  captureHeight;
    
    ofPoint  anchor;
    bool  bAnchorIsPct;    	
};