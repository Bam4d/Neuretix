/* 
 * File:   SAxon.h
 * Author: bam4d
 *
 * Created on 28 October 2012, 18:21
 */

#ifndef SAXON_H
#define	SAXON_H

#include "../../../Neuretix/src/inc/Axon.h"

class Neuron;

class SAxon : public Axon {
public:
    SAxon();
    SAxon(const SAxon& orig);
    SAxon(Neuron * , Neuron * , double , int );
    
    void Fire_TW();
    
    virtual ~SAxon();
private:

};

#endif	/* SAXON_H */

