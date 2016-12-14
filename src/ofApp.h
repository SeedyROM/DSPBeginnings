#pragma once

#include "ofMain.h"
#include "SvfLinearTrapOptimised2.hpp"
#include "Oscillator.hpp"

using SVFilter = SvfLinearTrapOptimised2;

class ofApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();

    void audioOut(float *, int, int);
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
    void exit();

    constexpr static int sampleRate = 48000;

    SineOsc lfo;
    SquareOsc saw;
    SineOsc sine;
    SVFilter filter;
    SVFilter peak;
};
