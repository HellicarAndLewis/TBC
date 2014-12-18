//
//  Integrator.cpp
//  Effects
//
//  Created by James Bentley on 12/18/14.
//
//

#include "Integrator.h"

Integrator::Integrator(float value) : value(value) {
    DAMPING = 0.5f;
    ATTRACTION = 0.2f;
}

Integrator::Integrator(float value, float damping, float attraction) : value(value), DAMPING(damping), ATTRACTION(attraction) {
    
}

void Integrator::set(float v) {
    value = v;
}

void Integrator::update() {
    if (targeting) {
        force += attraction * (targetVal - value);
    }
    
    accel = force / mass;
    vel = (vel + accel) * damping;
    value += vel;
    
    force = 0;
}

void Integrator::target(float t) {
    targeting = true;
    targetVal = t;
}

void Integrator::noTarget() {
    targeting = false;
}