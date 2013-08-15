/* 
 * File:   STDPGroup.h
 * Author: bam4d
 *
 * Created on 07 July 2012, 18:04
 */

#ifndef STDPGROUP_H
#define	STDPGROUP_H

#include "../../../Neuretix/src/inc/Group.h"

class STDPGroup : public Group {
public:
    STDPGroup();
    
    void Init(int,int,RGB);
    
    void ResetChannels();
    
    STDPGroup(const STDPGroup& orig);
    virtual ~STDPGroup();
private:

};

#endif	/* STDPGROUP_H */

