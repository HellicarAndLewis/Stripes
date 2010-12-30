/*
 *  ofxFBOTexture.cpp
 *  openFrameworks
 *
 *  Created by Zach Gage on 3/28/08.
 *  Copyright 2008 STFJ.NET. All rights reserved.
 *
 *  http://addons.openframeworks.cc/projects/show/ofxfbotexture
 *
 *  Updated 22nd July 2009
 *
 */

#ifndef _FBO_TEX
#define _FBO_TEX


#include "ofMain.h"

#include <iostream>

//theo added multisampling from this excellent guide:
// http://blog.dexta.ch/2008/08/27/gl_ext_framebuffer_object-with-multisampling/

class ofxFBOTexture : public ofTexture {
public:

        void allocate(int w, int h, bool autoClear, int numSamples = 4);

        void swapIn();
        void swapOut();

        void setupScreenForMe();
        void setupScreenForThem();

        void begin() {
                swapIn();
                setupScreenForMe();
        }

        void end() {
                swapOut();
                setupScreenForThem();
        }

        void clear();
        void clear(float r, float g, float b, float a);

        void bindAsTexture();


protected:
        bool            _isActive;
        GLuint      fbo;                                 // Our handle to the FBO
		GLuint		mfbo;
        GLuint      depthBuffer;                        // Our handle to the depth render buffer
        GLuint      colorBuffer;                        // Our handle to the depth render buffer

        bool        autoClear;
        void        clean();
        float       clearColor[4];
		
		bool bUseMultiSample;
		
		int numSamples;

};

#endif
