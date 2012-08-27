/* 
 * File:   GenerateSOM.h
 * Author: bam4d
 *
 * Created on 28 June 2012, 21:41
 */

#ifndef GENERATESOM_H
#define	GENERATESOM_H

class SelfOrganisingMap {
public:
    static void SOM2D(ClusterMap* clusterMap,int dimx,int dimy, float separation, float inhibitoryDistance);
    static void SOM1D(ClusterMap* clusterMap,int dimx,float separation);
private:
    
    static float CalculateDistance(PlotPoint _a,PlotPoint _b);

};

#endif	/* GENERATESOM_H */
