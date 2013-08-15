/* 
 * File:   PreSynapticCycleCache.h
 * Author: bam4d
 *
 * Created on 16 November 2012, 14:34
 */

#ifndef PRESYNAPTICCYCLECACHE_H
#define	PRESYNAPTICCYCLECACHE_H

#include "../../../Neuretix/src/inc/CyclicCache.h"

class PreSynapticCyclicCache : public CyclicCache {
public:
    PreSynapticCyclicCache();
    PreSynapticCyclicCache(int maxPoints, int maxEvents);
    void Cycle(int cycles);
    
    void Reset();
    virtual ~PreSynapticCyclicCache();
private:

};

#endif	/* PRESYNAPTICCYCLECACHE_H */

