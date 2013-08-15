/* 
 * File:   CyclicCache.h
 * Author: bam4d
 *
 * Created on 15 November 2012, 14:40
 */
#ifndef CYCLICCACHE_H
#define	CYCLICCACHE_H

class CyclicCacheTimePoint;

class CyclicCache {
public:
    int maxPoints;

    CyclicCache();
    CyclicCache(int maxPoints, int maxEvents);
    ~CyclicCache();

    void Cycle();

    CyclicCacheTimePoint* currentTimePoint;
        
    CyclicCacheTimePoint* cache;

    CyclicCacheTimePoint* GetTimePointAtOffset(int offset);
    
    void LogState();
    void Release(); //clears the time points of their lists of axons

protected:
    int _currentPoint;
private:

};

#endif	/* CYCLICCACHE_H */

