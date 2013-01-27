/* 
 * File:   main.cpp
 * Author: bam4d
 *
 * Created on 31 December 2012, 15:28
 */
#include "../CavalCade/CNNGlobals.h"
#include "../NeuroPlasticity/NeuroplasticityGlobals.h"
#include "../GenomeLoader/GenomeLoaderGlobals.h"
#include "testHeader.h"
#include <cstdlib>

using namespace std;

bool testcompleted = false;

void TestCompleted(int testNum, bool success)
{
    if(success)
        printf("\nTEST %d PASS\n\n", testNum);
    else
        printf("\n!!!!!!!!---TEST %d FAIL---!!!!!!!!\n\n", testNum);
    
    //reset the test completed flag
    testcompleted = true;
}

void DestroyNetwork(MindAndGenome* mindAndGenome)
{
    mindAndGenome->mind->StopMindThread_TW();
    mindAndGenome->genome->Clear();
    mindAndGenome->mind->Clear();
    delete mindAndGenome->mind;
    delete mindAndGenome->genome;
    delete mindAndGenome;
}


/*
 * 
 */
int main(int argc, char** argv) {

    testcompleted = false;
    MindAndGenome* mindAndGenome1 = StartTest1();
    while(!testcompleted);
    DestroyNetwork(mindAndGenome1);
    
    testcompleted = false;
    MindAndGenome* mindAndGenome2 = StartTest2();
    while(!testcompleted);
    DestroyNetwork(mindAndGenome2);
    
    testcompleted = false;
    MindAndGenome* mindAndGenome3 = StartTest3();
    while(!testcompleted);
    DestroyNetwork(mindAndGenome3);
    
    return 0;
}




