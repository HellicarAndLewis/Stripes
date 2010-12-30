/*
 *  TwoColourHardStripe.h
 *  uniqloHAndL
 *
 *  Created by Joel Gethin Lewis on 22/11/2010.
 *  Copyright 2010 Hellicar&Lewis. All rights reserved.
 *
 */

#pragma once;

#include "BaseStripe.h"

class TwoColourHardStripe: public BaseStripe{
public:
	TwoColourHardStripe(){
		colour.r = 255;
		colour.g = 0;
		colour.b = 0;

		bottomColour.r = 255;
		bottomColour.g = 0;
		bottomColour.b = 0;			
		
		stripeBoundaryVerticalPosition = 0.f;
		velocity = 0.01f;
		gravity = 0.05f;
		coefficientOfRestitution = 0.3f;
		
	}; //constructor;
	
	virtual ~TwoColourHardStripe(){} //destructor
	
	TwoColourHardStripe(float _x, float _y, float _w, float _h, ofColor c1, ofColor c2, float midPosition, float vel){
		x = _x;
		y = _y;
		width = _w;
		height = _h;
		colour = c1;
		bottomColour = c2;	
		stripeBoundaryVerticalPosition = midPosition;
		velocity = vel;
		gravity = 0.05f;
		coefficientOfRestitution = 0.3f;		
	}
	
	void set(float _x, float _y, float _w, float _h, ofColor c1, ofColor c2, float midPosition, float vel){
		x = _x;
		y = _y;
		width = _w;
		height = _h;
		colour = c1;
		bottomColour = c2;	
		stripeBoundaryVerticalPosition = midPosition;
		velocity = vel;
		gravity = 0.05f;
		coefficientOfRestitution = 0.3f;		
	}
	
	void setColour(ofColor c){
		colour = c;
	}
	
	void setBotColour(ofColor c){
		bottomColour = c;
	}
	
	void setVelocity(float vel){
		velocity = vel;
	}
	
	void update(float timeElapsed, float highPointOfDiffRelativeValue, float extraEnergy){
		stripeBoundaryVerticalPosition += timeElapsed*velocity;
		
		velocity += gravity;
		
		if(stripeBoundaryVerticalPosition > 1.f){
			velocity = -velocity;
			velocity *= coefficientOfRestitution;
			stripeBoundaryVerticalPosition = 1.f;
		}
	}
	
	void draw(){
		
		float divisionHeight = stripeBoundaryVerticalPosition*height;
		
		ofPushStyle();
		
		glBegin(GL_QUAD_STRIP);
		
		glColor3f(colour.r/255.f,colour.g/255.f,colour.b/255.f);
		glVertex3f(x, y,0);
		glVertex3f(x+width,y,0);
		
		glColor3f(colour.r/255.f,colour.g/255.f,colour.b/255.f);
		glVertex3f(x,y+divisionHeight,0);
		glVertex3f(x+width, y+divisionHeight,0);
		
		glColor3f(bottomColour.r/255.f,bottomColour.g/255.f,bottomColour.b/255.f);
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
		
	}	
	
private:
	
	float stripeBoundaryVerticalPosition;
	ofColor colour;
	ofColor midColour;
	ofColor bottomColour;
	float velocity;
	float gravity;
	float coefficientOfRestitution;
};


