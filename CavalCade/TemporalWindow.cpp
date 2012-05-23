/* 
 * File:   TemporalWindow.cpp
 * Author: bam4d
 * 
 * Created on 19 February 2012, 18:06
 */

#include "CNNGlobals.h"

TemporalWindow::TemporalWindow(int maxPoints) 
{
        Window = new TimePoint[maxPoints];
        CurrentPoint = 0;
        MaxPoints = maxPoints;
}



TimePoint* TemporalWindow::operator[](int position)
{
    return &Window[(CurrentPoint+position)%MaxPoints];
}

void TemporalWindow::Release()
{
    delete[] Window;
}


TemporalWindow::~TemporalWindow() {
}

