//
//  Osc.cpp
//  firstSketch
//
//  Created by Zack Kollar on 12/12/16.
//
//

#include <iostream>
#include <math.h>

#include "ofApp.h"
#include "Oscillator.hpp"

Oscillator::Oscillator(float frequency, int sampleRate)
{
    setFrequency(frequency, sampleRate);
}

void Oscillator::setFrequency(float frequency, int sampleRate)
{
    _normalizedFreq = frequency / (double) sampleRate;
    _phaseInc       = _normalizedFreq * TWO_PI;
}

void Oscillator::setAmplitude(float amplitude) {
    _amplitude = amplitude;
}

void Oscillator::reset() {
    _phase = 0;
}

const float Oscillator::polyBlep(float t) {
    float dt = _phaseInc / TWO_PI;
    float polyBlep = 0.f;
    if(t < dt) {
        t /= dt;
        polyBlep = t+t - t*t - 1.f;
    } else if(t > 1.f - dt) {
        t = (t - 1.f) / dt;
        polyBlep = t*t + t+t + 1.f;
    }
    return polyBlep;
}