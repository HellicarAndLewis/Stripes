/*
 *  BasicStripe.h
 *  uniqloHAndL
 *
 *  Created by Joel Gethin Lewis on 22/11/2010.
 *  Copyright 2010 Hellicar&Lewis. All rights reserved.
 *
 */

#pragma once;

#include "ofMain.h"

#include "BaseStripe.h"

class BasicStripe: public BaseStripe{ //initally from ofRectangle, without the cruft
	
public:
	BasicStripe(){ x = y = width = height = 0.0f; colour.r = colour.g = colour.b = colour.a = 255;}; //constructor;
	virtual ~BasicStripe(){} //destructor
	
	BasicStripe(float _x, float _y, float _w, float _h, ofColor c){
		x = _x;
		y = _y;
		width = _w;
		height = _h;
		colour = c;
	}
	
	void set(float px, float py, float w, float h, ofColor c){
		x		= px;
		y		= py;
		width	= w;
		height	= h;
		colour = c;
	}
	
	void setColour(ofColor c){
		colour = c;
	}
	
	ofPoint getCenter(){
		return ofPoint(x + width * 0.5f, y + height * 0.5f, 0);
	}
	
	bool inside (ofPoint p){
		return inside(p.x, p.y);
	}
	
	bool inside(float px, float py){
		if( px > x && py > y && px < x + width && py < y + height ){
		    return true;
		}
		return false;
	}
	
	void update(float timeElapsed, float highPointOfDiffRelativeValue, float extraEnergy){
			//nothing
	}
	
	void draw(){
		
		//cout << "Drawing a basic stripe" << endl;
		
		ofPushStyle();
		
		ofSetColor(colour.r, colour.g, colour.b);
		
		ofRect(x, y, width, height);
		
		ofPopStyle();
	}
	
	void mouseMoved(int x, int y ){
//		colour.set(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255));
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
	
		//Set
//	BasicStripe & operator=( const BasicStripe& stripe ){
//		x = stripe.x;
//		y = stripe.y;
//		width = stripe.width;
//		height = stripe.height;
//		return *this;
//	}

private:
	
	ofColor colour;
};