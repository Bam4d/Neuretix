#include <vector>
#include <map>



#include "../../../Neuretix/src/inc/Mind.h"
#include "../../../Genome/src/inc/Genome.h"
#include "../../../Genome/src/inc/GAEngine.h"
#include "../../../Structures/src/inc/SelfOrganisingMap.h"
#include "../../../OpenGLRendering/src/inc/NeuralNetRenderer.h"



Mind* SetupSOM()
{

	//firstly set up a genome (this later gets bound to a mind)
	Genome* genome = new Genome();

	genome->clusterMaps.push_back(ClusterMap());

	//create a self organising map 200x200
	SelfOrganisingMap::SOM2D(&genome->clusterMaps[0],200,200,0.15,0.4);

    Mind* mind = new Mind();

    GAEngine::GenomeToMind(mind,genome);

    //start the mind thread using temporal windowing algorithm for processing
    mind->StartMindThread_TW(1000,true);

    return mind;
}

int main(int argc, char **argv)
{
	NeuralNetRenderer* neuralNetRenderer = new NeuralNetRenderer("Example Self-Organising Map");

    Mind* mind = SetupSOM();

    neuralNetRenderer->addMind(mind);

    neuralNetRenderer->start();

    delete neuralNetRenderer;
    delete mind;
    return 1;
}




