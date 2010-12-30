#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
		// load the settings
	settings.loadSettings("settings/appSettings.xml");
	
		//mouse house
	
	bShowMouse = false;
	ofHideCursor(); //hide it!
	
	ofSetFrameRate(60);
	ofSetVerticalSync(true); //vsync to stop tearing	
	
	camWidth 		= settings.CAMERA_WIDTH;	// try to grab at this size.
	camHeight 		= settings.CAMERA_HEIGHT;
	
		//Camera
	videoGrabber.setVerbose(true);
	videoGrabber.initGrabber(camWidth,camHeight);
	
		//computer vision images]
	videoColourCvImage.allocate(camWidth, camHeight);
	videoGreyscaleCvImage.allocate(camWidth, camHeight);
	greyBackground.allocate(camWidth, camHeight);
	shortBgImg.allocate(camWidth, camHeight);
	greyDiff.allocate(camWidth, camHeight);
	greySmallImage.allocate(camWidth/settings.TRACKING_SCALE_FACTOR, camHeight/settings.TRACKING_SCALE_FACTOR);
	previousgreySmallImage.allocate(camWidth/settings.TRACKING_SCALE_FACTOR, camHeight/settings.TRACKING_SCALE_FACTOR);
	
	opticalFlow.allocate(camWidth/settings.TRACKING_SCALE_FACTOR, camHeight/settings.TRACKING_SCALE_FACTOR); // width*TRACKING_SCALE_FACTOR, height*TRACKING_SCALE_FACTOR );
	opticalFlow.setCalcStep(5,5);
	
//	persistentTracker.allocate(camWidth, camHeight);
//	persistentTracker.setListener(this);	
	
		//camera cropping
	videoGreyscaleCvImagePreWarp.allocate(camWidth, camHeight);
	
	srcPts[0].set(0,0);
	srcPts[1].set(camWidth,0);
	srcPts[2].set(camWidth,camHeight);
	srcPts[3].set(0,camHeight);
	
	dstPts[0].set(0,0);
	dstPts[1].set(camWidth,0);
	dstPts[2].set(camWidth,camHeight);
	dstPts[3].set(0,camHeight);		
	
		//FBO
	
	ofBackground(0,0,0);
    rm.allocateForNScreens(2, 2048, 768);
    rm.loadFromXml("settings/FBOSettings.xml");
	
    guiIn   = ofRectangle(10, 40, 640, 240); //640, 240 analgous to 2048, 768 projection size
    guiOut  = ofRectangle(guiIn.x, guiIn.height + 40, 640, 240); //640, 240 analgous to 2048, 768 projection size
	
		//GUI
	
	gui.loadFont("fonts/monaco.ttf", 8);		
	gui.setup("Hellicar&Lewis - Uniqlo Stripes - H to hide GUI, M to toggle mouse, F to toggle fullscreen", 0, 0, 1024, 768);
	gui.addPanel("Stripe Settings", 4, false);
	gui.addPanel("Camera Crop Settings", 4, false);	
	gui.addPanel("Diff and Blob Settings", 4, false);		
	
	gui.setWhichPanel(0); //Stripe settings
	gui.setWhichColumn(0);
	gui.addSlider("Number of Stripes", "NUMBER_OF_STRIPES", 10, 5, 30, true);
//	gui.addSlider("Gravity", "GRAVITY", 0.2f, 0.f, 1.f, false);	
	
	gui.setWhichPanel(1); //Camera crop settings
						  
	//from Chris Sugrue warping tips on her site...
	
	gui.setWhichColumn(0);
	
	gui.addSlider2D("pta", "WARP_CV_MANAGER_PANEL_VIDEO_PTA", 0, 0, 0, camWidth, 0, camHeight, true);
	gui.addSlider2D("ptd", "WARP_CV_MANAGER_PANEL_VIDEO_PTD", 0, camHeight, 0, camWidth, 0, camHeight, true);
	
	gui.setWhichColumn(1);
	gui.addSlider2D("ptb", "WARP_CV_MANAGER_PANEL_VIDEO_PTB", camWidth, 0, 0, camWidth, 0, camHeight, true);
	gui.addSlider2D("ptc", "WARP_CV_MANAGER_PANEL_VIDEO_PTC", camWidth, camHeight, 0, camWidth, 0, camHeight, true);	
	
	gui.setWhichColumn(2);
	gui.addDrawableRect("pre warp", &videoGreyscaleCvImagePreWarp, 200, 150);
	gui.addDrawableRect("warped", &videoGreyscaleCvImage, 200, 150);		
	
	gui.setWhichPanel(2); //Diff and blob
		//from OpenTSPS
	
	gui.setWhichColumn(0);
	
	gui.addToggle("Gain video?)", "USE_AMPLIFICATION", false);
	gui.addSlider("Gain amount:", "AMPLIFICATION_AMOUNT", 1, 1, 100, true);
	
		//background settings
	gui.addToggle("Learn background?", "LEARN_BACKGROUND", false);
	gui.addToggle("Progressive relearn?", "RELEARN", false);
	gui.addSlider("Relearn rate :", "RELEARN_BACKGROUND", .1f, 0.0f, 2000.0f, false);	
	
		//differencing settings, from OpenTSPS
	
	gui.addSlider("threshold:", "THRESHOLD", 40, 0, 255, false);
	vector<string> multi;
	multi.push_back("light on dark");
	multi.push_back("dark on light");
	multi.push_back("absolute difference");
	gui.addMultiToggle("type of differencing:", "BLOB_TYPE", 0, multi);
	
	gui.setWhichColumn(1);
	
	gui.addToggle("highpass?", "USE_HIGHPASS", true);
	gui.addSlider("highpass blur:", "HIGHPASS_BLUR", 1, 1, 200, true);
	gui.addSlider("highpass noise:", "HIGHPASS_NOISE", 1, 1, 30, true);
	gui.addToggle("smooth?", "USE_SMOOTHING", false);
	gui.addSlider("smooth amount:", "SMOOTH_AMOUNT", 0, 0, 15, false);		
	
		//sensing
	
	gui.addSlider("min blob size ", "MIN_BLOB", 1.f, 0.01f, 2.0f, false);
	gui.addSlider("max blob size ", "MAX_BLOB", .50f, 0.1f, 100.f, false);
	gui.addToggle("ignore holes", "FIND_HOLES", false);	
	
		//flow bits
	gui.addSlider("min flow", "MIN_OPTICAL_FLOW", 0, 0, 5.0, false);
	gui.addSlider("max flow", "MAX_OPTICAL_FLOW", 10, 5.0, 200, false);	
	
	gui.setWhichColumn(2);
	gui.addDrawableRect("live", &videoGreyscaleCvImage, 200, 150);	
	gui.addDrawableRect("background", &greyBackground, 200, 150);
	gui.addDrawableRect("diff", &greyDiff, 200, 150);
	
	gui.setWhichColumn(3);
//	gui.addDrawableRect("contours", &contourFinder, 200, 150);	
//	gui.addDrawableRect("blobs", &persistentTracker, 200, 150);
	gui.addDrawableRect("flow", &opticalFlow, 200, 150);
	
		//load from xml!
	gui.loadSettings("settings/controlPanelSettings.xml");	
	
	timeOfStartup = timeOfLastFrame = ofGetElapsedTimef();	
}

//--------------------------------------------------------------
void testApp::update(){
	float elapsedTimeBetweenFrames = ofGetElapsedTimef() - timeOfLastFrame;
	float elapsedTimeSinceStart = ofGetElapsedTimef() - timeOfStartup;
	
	int guiNumberOfStripes = gui.getValueI("NUMBER_OF_STRIPES");
	
	if(guiNumberOfStripes != stripesController.stripes.size()){
		stripesController.resizeStripes(guiNumberOfStripes);	
	}	
	
	videoGrabber.update();
	
	srcPts[0].set( gui.getValueI("WARP_CV_MANAGER_PANEL_VIDEO_PTA", 0), gui.getValueI("WARP_CV_MANAGER_PANEL_VIDEO_PTA", 1));
	srcPts[1].set( gui.getValueI("WARP_CV_MANAGER_PANEL_VIDEO_PTB", 0), gui.getValueI("WARP_CV_MANAGER_PANEL_VIDEO_PTB", 1));
	srcPts[2].set( gui.getValueI("WARP_CV_MANAGER_PANEL_VIDEO_PTC", 0), gui.getValueI("WARP_CV_MANAGER_PANEL_VIDEO_PTC", 1));
	srcPts[3].set( gui.getValueI("WARP_CV_MANAGER_PANEL_VIDEO_PTD", 0), gui.getValueI("WARP_CV_MANAGER_PANEL_VIDEO_PTD", 1));	
	
	if(videoGrabber.isFrameNew()) {
		videoColourCvImage.setFromPixels(videoGrabber.getPixels(), camWidth, camHeight);
		videoColourCvImage.mirror(false, true); //flip it!
		
		videoGreyscaleCvImagePreWarp = videoColourCvImage; //automatic conversion...
		
		videoGreyscaleCvImage.warpIntoMe(videoGreyscaleCvImagePreWarp, srcPts, dstPts);
		
		greySmallImage.scaleIntoMe(videoGreyscaleCvImage);
		
		greyDiff = videoGreyscaleCvImage;
		
			//amplify (see cpuimagefilter class)
		if(gui.getValueB("USE_AMPLIFICATION")){
			greyDiff.amplify(greyDiff, gui.getValueI("AMPLIFICATION_AMOUNT")/15.0f);
		}
		
		videoGreyscaleCvImage = greyDiff;	
		
			//-------------------
			//BACKGROUND
			//-------------------
		
			//learn background (either in reset or additive)
		if (gui.getValueB("LEARN_BACKGROUND") || (elapsedTimeSinceStart < 2.f)){
			cout << "Learning Background" << endl;
			greyBackground = videoGreyscaleCvImage;
		}
		
			//progressive relearn background
		if (gui.getValueB("RELEARN")){
			if (gui.getValueB("LEARN_BACKGROUND")) shortBgImg = greyBackground;
			shortBgImg.addWeighted( videoGreyscaleCvImage, gui.getValueF("RELEARN_BACKGROUND") * .00001f);
			greyBackground = shortBgImg;		
		}
		
			//printf("track type %d from (%d,%d,%d)\n", p_Settings->trackType, TRACK_ABSOLUTE, TRACK_DARK, TRACK_LIGHT);
		if(gui.getValueI("BLOB_TYPE") == 2){
			greyDiff.absDiff(greyBackground, videoGreyscaleCvImage);
		}
		else{
			greyDiff = videoGreyscaleCvImage;
			if(gui.getValueI("BLOB_TYPE") == 1){ //think this is the right way around.. check!
				cvSub(greyBackground.getCvImage(), greyDiff.getCvImage(), greyDiff.getCvImage());
			}
			else if(gui.getValueI("BLOB_TYPE") == 0){ 
				cvSub(greyDiff.getCvImage(), greyBackground.getCvImage(), greyDiff.getCvImage());
			}
			greyDiff.flagImageChanged();
		}
		
			//-----------------------
			// IMAGE TREATMENT
			//-----------------------
		if(gui.getValueB("USE_SMOOTHING")){
			greyDiff.blur((gui.getValueI("SMOOTH_AMOUNT") * 2) + 1); //needs to be an odd number
		}
		
			//highpass filter (see cpuimagefilter class)	
		if(gui.getValueB("USE_HIGHPASS")){
			greyDiff.highpass(gui.getValueI("HIGHPASS_BLUR"), gui.getValueI("HIGHPASS_NOISE"));
		}
		
			//threshold	
		greyDiff.threshold(gui.getValueI("THRESHOLD"));
		
			//-----------------------
			// TRACKING
			//-----------------------	
		//find the optical flow
		opticalFlow.calc(previousgreySmallImage, greySmallImage,  11); //past, current, size
		
		opticalFlow.maxVector = gui.getValueF("MAX_OPTICAL_FLOW");
		opticalFlow.minVector = gui.getValueF("MIN_OPTICAL_FLOW");		
		
//		contourFinder.findContours(greyDiff, gui.getValueF("MIN_BLOB")*camWidth*camHeight, gui.getValueF("MAX_BLOB")*camWidth*camHeight, 50, gui.getValueF("FIND_HOLES"));
//		persistentTracker.trackBlobs(contourFinder.blobs);
		
		previousgreySmallImage = greySmallImage; //remember the last one
	}
	
	stripesController.update(elapsedTimeBetweenFrames, &greyDiff, &opticalFlow);
	
	gui.update();
	
	timeOfLastFrame = ofGetElapsedTimef();
	
	if(gui.getValueB("LEARN_BACKGROUND")){
		gui.setValueB("LEARN_BACKGROUND", false);
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0,0,0);
	
    ofSetColor(255, 255, 255, 255);
	
    rm.startOffscreenDraw();
	
	stripesController.draw();
	
    rm.endOffscreenDraw();
	
    ofSetColor(255, 255, 255, 255);
	
    rm.drawInputDiagnostically(guiIn.x, guiIn.y, guiIn.width, guiIn.height);
    rm.drawOutputDiagnostically(guiOut.x, guiOut.y, guiOut.width, guiOut.height);
	
    glPushMatrix();
	glTranslatef(1024, 0, 0); //translate past the gui....
	ofSetColor(255, 255, 255, 255);
	rm.drawScreen(0);
	rm.drawScreen(1);	
    glPopMatrix();	
	
    ofDrawBitmapString("internal texture points", 10, 228);
    ofDrawBitmapString("texture warping points", 535, 228);
	
    ofDrawBitmapString("s - to save to xml   l - to reload from xml    r - reset coordinates\n", 10, 16);
	
	gui.draw();
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	switch (key){
		case 'f':{
			ofToggleFullscreen();
			break;				
		}
		case 'h':{
			gui.toggleView();	
			break;
		}
		case 'm':{
			if(bShowMouse){
				ofHideCursor();
				bShowMouse = false;
			}else {
				ofShowCursor();
				bShowMouse = true;
			} 
			break;				
		} 
		case 'v':{
			videoGrabber.videoSettings(); 
			break;
		}
		case 's':{
			rm.saveToXml();	
			break;
		}
		case 'l':{
			rm.reloadFromXml();
			break;
		}
		case 'r':{
			rm.resetCoordinates();
			break;
		}
		default:{
			break;
		}
	}	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
		//	stripesController.mouseMoved(x,y); //all opencv interaction now, use for debug
}


	//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	if(!gui.hidden){
		gui.mouseDragged(x, y, button);		
	}else{
		rm.mouseDragInputPoint(guiIn, ofPoint(x, y));
		rm.mouseDragOutputPoint(guiOut, ofPoint( x, y));
	}
}

	//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	if(!gui.hidden){
		gui.mousePressed(x, y, button);		
	}else{
		if( !rm.mouseSelectInputPoint(guiIn, ofPoint(x, y)) ){
			rm.mouseSelectOutputPoint(guiOut, ofPoint( x,  y));
		}
	}	
}

	//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	if(!gui.hidden){
		gui.mouseReleased();		
	}	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//void testApp::blobOn( int x, int y, int id, int order ){
//}
//
//void testApp::blobMoved( int x, int y, int id, int order ){
////	ofxCvTrackedBlob blob = persistentTracker.getById( id );
////	
////	stripesController.blobMoved(&blob);
//}
//
//void testApp::blobOff( int x, int y, int id, int order ){
//}

