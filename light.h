/* 
 * File:   light.h
 * Author: root
 *
 * Created on May 5, 2014, 3:35 PM
 */

#ifndef LIGHT_H
#define	LIGHT_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "math.h"
#include <algorithm>
#include "renderable.h"
#include <iostream>
#include <stdio.h>

using namespace std;

class Light : public Renderable {

public:
    //Light();
    //virtual void draw();
    Light(void);
    ~Light(void);

    void draw(void);
    float time;
};


#endif	/* LIGHT_H */