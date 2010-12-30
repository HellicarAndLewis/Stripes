/*
 *  AppGlobals.h
 *  emptyExample
 *
 *  Created by Todd Vanderlin on 3/30/10.
 *  Copyright 2010 Interactive Design. All rights reserved.
 *
 */

#pragma once
#include "ofxXmlSettings.h"

class AppSettings {

protected:
	ofxXmlSettings xml;
public:
	
	int TRACKING_SCALE_FACTOR; //scales down tracking images for improved performance
	int CAMERA_WIDTH;
	int CAMERA_HEIGHT;
	int STRIPES_WIDTH;
	int STRIPES_HEIGHT;	
	float ENERGY_SCALE;
	int TIME_BETWEEN_CYCLES;

	AppSettings() {
	}
	
	void loadSettings(string file) {
		if(xml.loadFile(file)) {
			TRACKING_SCALE_FACTOR = xml.getValue("TRACKING_SCALE_FACTOR", 2);
			CAMERA_WIDTH = xml.getValue("CAMERA_WIDTH", 320);
			CAMERA_HEIGHT = xml.getValue("CAMERA_HEIGHT", 240);
			STRIPES_WIDTH = xml.getValue("STRIPES_WIDTH", 2048);
			STRIPES_HEIGHT = xml.getValue("STRIPES_HEIGHT", 768);	
			ENERGY_SCALE = xml.getValue("ENERGY_SCALE", 0.001f);
			TIME_BETWEEN_CYCLES = xml.getValue("TIME_BETWEEN_CYCLES", 60);
		}
		
	}
};


// so other apps can see it...
extern AppSettings settings;