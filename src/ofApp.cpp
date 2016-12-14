#include <iostream>
#include <algorithm>
#include "ofApp.h"

template<typename T>
inline const float clip(const T& n, const T& lower, const T& upper) {
    return std::max(lower, std::min(n, upper));
}

//--------------------------------------------------------------
void ofApp::setup(){
    saw.setFrequency(440, sampleRate);
    sine.setFrequency(440, sampleRate);
    lfo.setFrequency(14, sampleRate);
    peak.setGain(5);
    
    ofSoundStreamSetup(2, 0, sampleRate, 512, 4);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapStringHighlight("SIGNWAVE! <><><><>", 20, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    const float pitch = abs(ofMap(x, 0, ofGetWidth(), 500, 2000));
    const float cutoff = abs(ofMap(y, 0, ofGetHeight(), 40, 5000));
    saw.setFrequency(pitch, sampleRate);
    sine.setFrequency(pitch, sampleRate);
}

//--------------------------------------------------------------
void ofApp::audioOut(float* buffer, int bufferSize, int nChannels) {
    for(unsigned int i = 0; i < bufferSize; i++) {
        float currentSample = 0;
        
        const float mod = ofMap(lfo.tick(), -1, 1, 250, 1000);
        
        peak.updateCoefficients(mod, 1,
                                SVFilter::BELL_FILTER,
                                sampleRate);
        
        filter.updateCoefficients(mod, 1,
                                  SVFilter::LOW_PASS_FILTER,
                                  sampleRate);
        
        currentSample = saw.tick();
        currentSample -= sine.tick();
        
        currentSample = filter.tick(peak.tick(currentSample));

        buffer[i*nChannels + 0] = currentSample;
        buffer[i*nChannels + 1] = currentSample;
    }
}

void ofApp::exit() {
    ofSoundStreamClose();
}
