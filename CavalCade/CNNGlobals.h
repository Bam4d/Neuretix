/* 
 * File:   CNNGlobals.h
 * Author: bam4d
 *
 * Created on 31 January 2011, 17:38
 */

#ifndef CNNGLOBALS_H
#define	CNNGLOBALS_H

#include <vector>
#include <stdlib.h>
#include <math.h>
#include <cstring>
#include <fstream>
#include <sys/time.h>

using namespace std;

/* ascii code for the escape key */
#define ESCAPE 27

#define DEF_REFRAC_LEV -0.3f //default refractory period potential
#define DEF_REFRAC_TIME 10 //default refractory period period
#define DEF_FIRETHRESH 0.7 //default neuron fire threshold
#define DEF_EXC_TC 500 //default neuron excitation decay time constant
#define DEF_FIRE_MAG 0.71 //default fire magnitude
#define DEF_SYN_DELAY 5 // default synaptic delay

#define DEF_SD_TC 2000.0f //default SDPD decay time constant
#define DEF_SD_MAG 0.5 //default magnitude of supply spikes
#define DEF_AXON_JOIN_THRESH 0.7 //default potential difference threshold to create a new axon
#define DEF_DIST_CONST 1


#define AVE_DIST 1.0f//multiplier distance between neurons

class PlotPoint //used to position neurons etc in the graphical output
{
public:
	float x,y,z;

        PlotPoint()
        {
            x = 0;
            y = 0;
            z = 0;
        }

        PlotPoint(float setx,float sety, float setz)
        {
            x = setx;
            y = sety;
            z = setz;
        }

        PlotPoint operator +(PlotPoint toAdd)
        {
            PlotPoint result;
            result.x = x+toAdd.x;
            result.y = y+toAdd.y;
            result.z = z+toAdd.z;
            return result;
        }
};

class RGB //used to position neurons etc in the graphical output
{
public:

	float r,g,b;
        RGB()
        {

        }
        
        RGB(float _r,float _g, float _b)
        {
            r = _r;
            g = _g;
            b = _b;
        }

};


#include "../CMarkup/Markup.h"


#include "CyclicCacheEvent.h"
#include "CyclicCacheTimePoint.h"
#include "CyclicCache.h"
#include "LeakyIntegrator.h"
#include "axon.h"
#include "axonList.h"
#include "neuron.h"
#include "group.h"
#include "ControlTimer.h"
#include "axon_event.h"
#include "TimePoint.h"
#include "CavalcadeMind.h"
#include "SaveLoadCNN.h"



#endif	/* CNNGLOBALS_H */

