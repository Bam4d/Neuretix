/* 
 * File:   SAxon.h
 * Author: bam4d
 *
 * Created on 28 October 2012, 18:21
 */

#ifndef SAXON_H
#define	SAXON_H

/* template for playing with the palsticity of axons*/
class SAxon : public axon {
public:
    SAxon();
    SAxon(const SAxon& orig);
    SAxon(neuron * , neuron * , double , int );
    
    void Fire_TW();
    
    virtual ~SAxon();
private:

};

#endif	/* SAXON_H */

