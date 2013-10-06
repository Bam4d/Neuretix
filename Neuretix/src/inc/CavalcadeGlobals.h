/*
 * CavalCade.h
 *
 *  Created on: 13 Aug 2013
 *      Author: bam4d
 */

#ifndef CAVALCADE_H_
#define CAVALCADE_H_

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

#endif /* CAVALCADE_H_ */
