//
//  pillar.h
//  Effects
//
//  Created by James Bentley on 12/9/14.
//
//

#ifndef __Effects__pillar__
#define __Effects__pillar__

#include "ofMain.h"
#include "Integrator.h"

class Pillar
{
public:
    void display();
    Pillar(int x, int y, int w, int h);
    void targetH(int _h);
    void resize();
private:
    int w, x, y, d;
    Integrator h;
};

#endif /* defined(__Effects__pillar__) */
