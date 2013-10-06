/*
 * Rendering.h
 *
 *  Created on: 12 Aug 2013
 *      Author: bam4d
 */

#ifndef RENDERING_H_
#define RENDERING_H_

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

	RGB() {
		r = 0;
		g = 0;
		b = 0;
	}

	float r,g,b;

	RGB(float r,float g, float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}

};


#endif /* RENDERING_H_ */
