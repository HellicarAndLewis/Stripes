/*
 *  EnergyGradientStripeColourChange.h
 *  uniqloHAndL
 *
 *  Created by Joel Gethin Lewis on 28/11/2010.
 *  Copyright 2010 Hellicar&Lewis. All rights reserved.
 *
 */

#pragma once;

#include "BaseStripe.h"

class EnergyGradientStripeColourChange: public BaseStripe{
public:
	EnergyGradientStripeColourChange(){
		colour.r = 255;
		colour.g = 0;
		colour.b = 0;
		
		midColour.r = 255;
		midColour.g = 0;
		midColour.b = 0;	
		
		bottomColour.r = 255;
		bottomColour.g = 0;
		bottomColour.b = 0;			

		midColourPosition = 0.f;
		velocity = 0.01f;
	}; //constructor;
	
	virtual ~EnergyGradientStripeColourChange(){} //destructor
	
	EnergyGradientStripeColourChange(float _x, float _y, float _w, float _h, ofColor c1, ofColor c2, ofColor c3, float midPosition, float vel){
		x = _x;
		y = _y;
		width = _w;
		height = _h;
		colour = c1;
		midColour = c2;
		bottomColour = c3;	
		midColourPosition = midPosition;
		velocity = vel;
	}
	
	void set(float _x, float _y, float _w, float _h, ofColor c1, ofColor c2, ofColor c3, float midPosition, float vel){
		x = _x;
		y = _y;
		width = _w;
		height = _h;
		colour = c1;
		midColourPosition = midPosition;
		midColour = c2;
		bottomColour = c3;
		velocity = vel;
	}
	
	void setColour(ofColor c){
		colour = c;
	}	
	
	void setMidColour(ofColor c){
		midColour = c;
	}
	
	void setBotColour(ofColor c){
		bottomColour = c;
	}
	
	void setVelocity(float vel){
		velocity = vel;
	}
	
	void update(float timeElapsed, float highPointOfDiffRelativeValue, float extraEnergy){
		float energyScale = settings.ENERGY_SCALE;
		
		extraEnergy *= energyScale;
		
		
		midColourPosition += (timeElapsed+extraEnergy)*velocity; //take account of energy and time...
		
		if(midColourPosition > 1.f){
			midColourPosition = 0.f;
			
				//bit below is so that on change over, don't get a colour snap.
			
			ofColor tempBottomColour = bottomColour;
			
			ofColor newBottomColour;	
			
			newBottomColour.r = ofRandom(0,255);
			newBottomColour.g = ofRandom(0,255);
			newBottomColour.b = ofRandom(0,255);				
			
			bottomColour = midColour;
			midColour = colour;
				//colour = tempBottomColour; not any more
			colour = newBottomColour; //use the new random instead
		}
	}
	
	void draw(){
		
		float midHeight = midColourPosition*height;
		
		//cout << "Drawing gradient stripe!" << endl;
		
		ofPushStyle();
		
		glBegin(GL_QUAD_STRIP);
		
		glColor3f(colour.r/255.f,colour.g/255.f,colour.b/255.f);
		glVertex3f(x, y,0);
		glVertex3f(x+width,y,0);
		
		glColor3f(midColour.r/255.f,midColour.g/255.f,midColour.b/255.f);
		glVertex3f(x,y+midHeight,0);
		glVertex3f(x+width, y+midHeight,0);
		
		glColor3f(bottomColour.r/255.f,bottomColour.g/255.f,bottomColour.b/255.f);
		glVertex3f(x, y+height,0);
		glVertex3f(x+width, y+height,0);
		
		glEnd();
		
		ofPopStyle();
	}
	
	void mouseMoved(int x, int y ){
//		colour.set(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255));
//		midColour.set(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255));
//		bottomColour.set(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255));
		
//		ofColor oldTop = colour;
//		
//		colour = bottomColour;
//		
//		bottomColour = oldTop;
		
		midColourPosition = (float)y/ofGetHeight();
	}
	
	void mouseDragged(int x, int y, int button){
		
	}
	void mousePressed(int x, int y, int button){
		
	}
	void mouseReleased(int x, int y, int button){
		
	}	
	
	void blobMoved(ofxCvTrackedBlob* aBlob){
		
	}	
	
		//------ Operators:
	
//		//Set
//	EnergyGradientStripeColourChange & operator=( const BasicStripe& stripe ){
//		x = stripe.x;
//		y = stripe.y;
//		width = stripe.width;
//		height = stripe.height;
//		colour = stripe.colour;
//		midColourPosition = 0.5f;
//		midColour = stripe.colour;
//		bottomColour = stripe.colour;	
//		
//		return *this;
//	}
//	
//		//Set
//	EnergyGradientStripeColourChange & operator=( const EnergyGradientStripeColourChange& stripe ){
//		x = stripe.x;
//		y = stripe.y;
//		width = stripe.width;
//		height = stripe.height;
//		colour = stripe.colour;
//		midColourPosition = stripe.midColourPosition;
//		midColour = stripe.midColour;
//		bottomColour = stripe.bottomColour;	
//		
//		return *this;
//	}	
	
private:
	
	float midColourPosition;
	ofColor colour;
	ofColor midColour;
	ofColor bottomColour;
	float velocity;
};


