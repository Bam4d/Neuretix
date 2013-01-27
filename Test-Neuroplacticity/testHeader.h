/* 
 * File:   testHeader.h
 * Author: bam4d
 *
 * Created on 31 December 2012, 16:56
 */

#ifndef TESTHEADER_H
#define	TESTHEADER_H

struct MindAndGenome
{
    CavalcadeMind* mind;
    Genome* genome;
    
};

void TestCompleted(int,bool);

//test definitions
MindAndGenome* StartTest1();
MindAndGenome* StartTest2();
MindAndGenome* StartTest3();


#endif	/* TESTHEADER_H */

