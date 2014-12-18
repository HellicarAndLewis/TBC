//
//  pillar.cpp
//  Effects
//
//  Created by James Bentley on 12/9/14.
//
//

#include "pillar.h"

Pillar::Pillar(int x, int y, int w, int _h) : x(x), y(y), w(w)
{
    h = Integrator(0);
    h = Integrator(_h);
}

void Pillar::display()
{
    ofSetColor(0);
    ofPushMatrix();
    ofTranslate(x, y-h.value);
    ofSetColor(255, 0, 0);
    ofDrawLine(0, h.value, 0, 0);
    ofDrawLine(w, h.value-w/2, w, -w/2);
    ofDrawLine(-w, h.value-w/2, -w, -w/2);
    ofDrawLine(0, h.value, w, h.value-w/2);
    ofDrawLine(0, h.value, -w, h.value-w/2);
    for(int i = 0; i < w; i++)
    {
        ofDrawLine(w-i, -w/2-i/2, 0-i, 0-i/2);
    }
    ofPopMatrix();
}

void Pillar::targetH(int _h)
{
    h.target(_h);
}

void Pillar::resize()
{
    h.update();
}