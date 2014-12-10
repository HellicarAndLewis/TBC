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

class Pillar
{
public:
    void display();
    Pillar(int x, int y, int w, int h);
private:
    int w, h, x, y, d;
};

#endif /* defined(__Effects__pillar__) */
