/*
 *  BaseStripe.h
 *  uniqloHAndL
 *
 *  Created by Joel Gethin Lewis on 22/11/2010.
 *  Copyright 2010 Hellicar&Lewis. All rights reserved.
 *
 */

#pragma once;

#include "ofMain.h"

#include "ofxCvTrackedBlob.h"

#include "AppSettings.h"

class BaseStripe { //initally from ofRectangle, without the cruft
	
public:
	BaseStripe(){ x = y = width = height = 0.0f;}; //constructor;
	virtual ~BaseStripe(){} //destructor
	
	BaseStripe(float _x, float _y, float _w, float _h){
		x = _x;
		y = _y;
		width = _w;
		height = _h;
	}
	
	void set(float px, float py, float w, float h){
		x		= px;
		y		= py;
		width	= w;
		height	= h;
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
	
	virtual void update(float timeElapsed, float highPointOfDiffRelativeValue, float extraEnergy){
			//nothing for base class....
	}
	
	virtual void draw(){
	}
	
	virtual void mouseMoved(int x, int y ){
		
	}
	
	virtual void mouseDragged(int x, int y, int button){
		
	}
	
	virtual void mousePressed(int x, int y, int button){
		
	}
	
	virtual void mouseReleased(int x, int y, int button){
		
	}
	
	virtual void blobMoved(ofxCvTrackedBlob* aBlob){
		
	}
		//------ Operators:
	
		//Set
//	BaseStripe & operator=( const BaseStripe& stripe ){
//		x = stripe.x;
//		y = stripe.y;
//		width = stripe.width;
//		height = stripe.height;
//		return *this;
//	}
	
	float x;
	float y;
	float width;
	float height;
};