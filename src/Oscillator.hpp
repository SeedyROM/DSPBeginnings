//
//  Osc.hpp
//  firstSketch
//
//  Created by Zack Kollar on 12/12/16.
//
//
#pragma once

class Oscillator {
public:
    Oscillator() {};
    Oscillator(float frequency, int sampleRate);
    
    void setFrequency(float frequency, int sampleRate);
    void setAmplitude(float amplitude);
    void reset();
    
    virtual inline float tick() = 0;
    
protected:
    float _phase = 0.f;
    float _phaseInc = 0.f;
    float _normalizedFreq = 0.f;
    float _amplitude = 0.8f;
    
    const float polyBlep(const float t);
};

struct SineOsc : public Oscillator {
    inline float tick() override {
        float sample = 0.f;
        
        // Calc...
        sample = sin(_phase);
        
        // Incremement and wrap.
        _phase += _phaseInc;
        _phase = _phase >= TWO_PI ? _phase-TWO_PI : _phase;
        
        return sample * _amplitude; // Return with amplitude.
    }
};

struct SawtoothOsc : public Oscillator {
    inline float tick() override {
        float t = _phase / TWO_PI;
        float sample = (2.f * t) - 1.f;
        
        // Anti-alias...
        sample -= polyBlep(t);
        
        // Wrap and increment.
        _phase += _phaseInc;
        _phase = _phase >= TWO_PI ? _phase-TWO_PI : _phase;
        
        return sample * _amplitude; // Return with amplitude.
    }
};

struct SquareOsc : public Oscillator {
    inline float tick() override {
        float sample = 0;
        if (_phase < PI) {
            sample = 1.0;
        } else {
            sample = -1.0;
        }
        
        // Two bleps, gotta anti-alias.
        float t = _phase / TWO_PI;
        sample += polyBlep(t);
        sample -= polyBlep(fmod(t + 0.5, 1.0));
        
        // Wrap and increment.
        _phase += _phaseInc;
        _phase = _phase >= TWO_PI ? _phase-TWO_PI : _phase;
        
        return sample * _amplitude;
    }
    
    void setDutyCycle(float dutyCycle) {
        _dutyCycle = dutyCycle;
    }
    
private:
    float _dutyCycle = 0.5;
};
