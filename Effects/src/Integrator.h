//
//  Integrator.h
//  Effects
//
//  Created by James Bentley on 12/18/14.
//
//

#ifndef __Effects__Integrator__
#define __Effects__Integrator__

#include "ofMain.h"

class Integrator
{
public:
    
    Integrator(float value);
    Integrator(float value, float damping, float attraction);
    void set(float v);
    void update();
    void target(float t);
    void noTarget();

    float DAMPING = 0.5f;
    float ATTRACTION = 0.2f;
    
    float value;
    float vel;
    float accel;
    float force;
    float mass = 1;
    
    float damping = DAMPING;
    float attraction = ATTRACTION;
    bool targeting;
    float targetVal;
    
};

#endif /* defined(__Effects__Integrator__) */
