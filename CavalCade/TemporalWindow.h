/* 
 * File:   TemporalWindow.h
 * Author: bam4d
 *
 * Created on 19 February 2012, 18:06
 */

#ifndef TEMPORALWINDOW_H
#define	TEMPORALWINDOW_H

class TemporalWindow
{
public:


    int CurrentPoint;
    int MaxPoints;

    TemporalWindow(int maxPoints);
    ~TemporalWindow();
    

    TimePoint* Window;

    TimePoint* operator[](int position);
    
    void Release(); //clears the time points of their lists of axons

private:
    
    
};


#endif	/* TEMPORALWINDOW_H */

