/* 
 * File:   STDPGroup.h
 * Author: bam4d
 *
 * Created on 07 July 2012, 18:04
 */

#ifndef STDPGROUP_H
#define	STDPGROUP_H

class STDPGroup : public group {
public:
    STDPGroup();
    
    void Init(int,int,RGB);
    
    STDPGroup(const STDPGroup& orig);
    virtual ~STDPGroup();
private:

};

#endif	/* STDPGROUP_H */

