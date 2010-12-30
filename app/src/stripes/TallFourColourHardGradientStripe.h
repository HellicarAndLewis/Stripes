/*
 *  TallFourColourHardGradientStripe.h
 *  uniqloHAndL
 *
 *  Created by Joel Gethin Lewis on 23/11/2010.
 *  Copyright 2010 Hellicar&Lewis. All rights reserved.
 *
 */

#pragma once;

#include "BaseStripe.h"

class TallFourColourHardGradientStripe: public BaseStripe{
public:
	TallFourColourHardGradientStripe(){
		colour.r = 255;
		colour.g = 0;
		colour.b = 0;
		
		midTopColour.r = 255;
		midTopColour.g = 0;
		midTopColour.b = 0;
		
		midBottomColour.r = 255;
		midBottomColour.g = 0;
		midBottomColour.b = 0;	
		
		bottomColour.r = 255;
		bottomColour.g = 0;
		bottomColour.b = 0;	
		
		stripeBoundaryVerticalPosition = 0.f;
		velocity = 0.01f;
		gravity = 0.05f;
		coefficientOfRestitution = 0.3f;
		
	}; //constructor;
	
	virtual ~TallFourColourHardGradientStripe(){} //destructor
	
	TallFourColourHardGradientStripe(float _x, float _y, float _w, float _h, ofColor c1, ofColor c2, ofColor c3, ofColor c4, float midPosition, float vel){
		x = _x;
		y = _y;
		width = _w;
		height = _h;
		colour = c1;
		midTopColour = c2;
		midBottomColour = c3;
		bottomColour = c4;
		stripeBoundaryVerticalPosition = midPosition;
		velocity = vel;
		gravity = 0.05f;
		coefficientOfRestitution = 0.3f;		
	}
	
	void set(float _x, float _y, float _w, float _h, ofColor c1, ofColor c2, ofColor c3, ofColor c4, float midPosition, float vel){
		x = _x;
		y = _y;
		width = _w;
		height = _h;
		colour = c1;
		midTopColour = c2;
		midBottomColour = c3;
		bottomColour = c4;
		stripeBoundaryVerticalPosition = midPosition;
		velocity = vel;
		gravity = 0.05f;
		coefficientOfRestitution = 0.3f;		
	}

	void setColour(ofColor c){
		colour = c;
	}

	void setMidTopColour(ofColor c){
		midTopColour = c;
	}
	
	void setMidBottomColour(ofColor c){
		midBottomColour = c;
	}
	
	void setBottomColour(ofColor c){
		bottomColour = c;
	}		
	
	void setVelocity(float vel){
		velocity = vel;
	}
	
	void update(float timeElapsed, float highPointOfDiffRelativeValue, float extraEnergy){
		
		if(highPointOfDiffRelativeValue < stripeBoundaryVerticalPosition){
			stripeBoundaryVerticalPosition = highPointOfDiffRelativeValue;
			velocity = 0.f;
		}else{
			stripeBoundaryVerticalPosition += timeElapsed*velocity;
			
			velocity += gravity;
			
			if(stripeBoundaryVerticalPosition > 1.f){
				velocity = -velocity;
				velocity *= coefficientOfRestitution;
				stripeBoundaryVerticalPosition = 1.f;
			}			
		}
	}
	
	void draw(){
		
		float divisionHeight = stripeBoundaryVerticalPosition*height;
		
		ofPushStyle();
		
		glBegin(GL_QUAD_STRIP);
		
		glColor3f(colour.r/255.f, colour.g/255.f, colour.b/255.f);
		glVertex3f(x, y,0);
		glVertex3f(x+width,y,0);
		
		glColor3f(midTopColour.r/255.f, midTopColour.g/255.f, midTopColour.b/255.f);
		glVertex3f(x,y+divisionHeight,0);
		glVertex3f(x+width, y+divisionHeight,0);
		
		glColor3f(midBottomColour.r/255.f,midBottomColour.g/255.f,midBottomColour.b/255.f);
		glVertex3f(x,y+divisionHeight,0);
		glVertex3f(x+width, y+divisionHeight,0);		
		
		glColor3f(bottomColour.r/255.f,bottomColour.g/255.f,bottomColour.b/255.f);
		glVertex3f(x, y+height,0);
		glVertex3f(x+width, y+height,0);
		
		glEnd();
		
		ofPopStyle();
	}
	
	void mouseMoved(int x, int y ){
		stripeBoundaryVerticalPosition = (float)y/ofGetHeight();
	}
	
	void mouseDragged(int x, int y, int button){
		
	}
	void mousePressed(int x, int y, int button){
		
	}
	void mouseReleased(int x, int y, int button){
		
	}	
	
	void blobMoved(ofxCvTrackedBlob* aBlob){
		
		ofRectangle blobCameraRelative = aBlob->boundingRect; 
				
		float cameraWidth = settings.CAMERA_WIDTH;
		float cameraHeight = settings.CAMERA_HEIGHT;
		
		float overAllStripesWidth = settings.STRIPES_WIDTH;
		float overAllStripesHeight = settings.STRIPES_HEIGHT;
		
		float scaleX = overAllStripesWidth/cameraWidth;
		float scaleY = overAllStripesHeight/cameraHeight;
		
		ofRectangle blobStripeRelative = ofRectangle(blobCameraRelative.x * scaleX, blobCameraRelative.y * scaleY,
													 blobCameraRelative.width * scaleX, blobCameraRelative.height * scaleY);

		if(rectOverLapsStripe(blobStripeRelative)){
			float topBlobRelativeToStripe = blobStripeRelative.y;
			float verticalPositionInStripeSize = stripeBoundaryVerticalPosition * height;
			
			
			if(topBlobRelativeToStripe < verticalPositionInStripeSize){
				stripeBoundaryVerticalPosition = topBlobRelativeToStripe/overAllStripesHeight;
			}
		}
	}
		   
	bool rectOverLapsStripe(ofRectangle rectToTest){
		return ((x < (rectToTest.x + rectToTest.width)) 
				&& ((x+width) > rectToTest.x) 
				&& (y < (rectToTest.y+rectToTest.height)) 
				&& (y+height > rectToTest.y));
		
			//http://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other (-;
	}
	
private:
	
	float stripeBoundaryVerticalPosition;
	ofColor colour;
	ofColor midTopColour;
	ofColor midBottomColour;
	ofColor bottomColour;
	float velocity;
	float gravity;
	float coefficientOfRestitution;
};


