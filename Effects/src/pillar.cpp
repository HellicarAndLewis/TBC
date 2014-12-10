//
//  pillar.cpp
//  Effects
//
//  Created by James Bentley on 12/9/14.
//
//

#include "pillar.h"

Pillar::Pillar(int x, int y, int w, int h) : x(x), y(y), w(w), h(h)
{
    
}

void Pillar::display()
{
    ofSetColor(0);
    ofPushMatrix();
    ofTranslate(x, y-h);
    ofSetColor(255, 0, 0);
    //ofDrawCircle(w, 0, 10, 10);
    ofDrawLine(0, h, 0, 0);
    ofDrawLine(w, h-w/2, w, -w/2);
    ofDrawLine(-w, h-w/2, -w, -w/2);
    ofDrawLine(0, h, w, h-w/2);
    ofDrawLine(0, h, -w, h-w/2);
    for(int i = 0; i < 22; i++)
    {
        ofDrawLine(w-i, -w/2-i/2, 0-i, 0-i/2);
    }
    ofPopMatrix();
}