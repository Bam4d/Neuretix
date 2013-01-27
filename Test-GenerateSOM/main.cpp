#include "globals.h"

using namespace std;

#include <QtGui/QApplication>

#  define GLUT_WHEEL_UP   3
#  define GLUT_WHEEL_DOWN 4

void RenderGlut();

void RenderNeuralNet();
void ResizeNeuralNetGX(int,int);
void KeyboardNeuralNet(unsigned char,int,int);
void SpecNeuralNet(int, int, int);
void mouseFuncNeuralNet(int,int,int,int);
void mouseMoveNeuralNet(int,int);

void RenderDebug();
void ResizeDebugGX(int,int);
void KeyboardDebug(unsigned char,int,int);
void mouseFuncDebug(int,int,int,int);
void mouseMoveDebug(int,int);

void StartSimulation(bool);
void StopSimulation();
void ConnectAllNeurons(group* , group* , axonList * );
void SetupSOM();

void *EnvironmentUpdate(void*);

PlotPoint SetPoint(float setx, float sety, float setz)
{
	PlotPoint temp;
	temp.x = setx;
	temp.y = sety;
	temp.z = setz;
	return temp;

}

int currentMouseButton;

bool runNet = false;

static GLEngine NeuralNetOutput; //main neural network screen
static GLEngine DebugOutput; //debug output

long NNTID; //netthreadid
long QTTID;

pthread_t qtUIThread;

vector<CavalcadeMind> Minds;
Genome _Genome;

//looks after the Qt Window stuff on separate thread
void *QtUI(void *)
{
    /* set up the Qt window stuff*/
    QApplication app(NULL, NULL);
    
    app.exec();

    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    int rc;

    glutInit(&argc, argv);

    /* Select type of Display mode:
         Double buffer
         RGBA color
         Alpha components supported
         Depth buffer */
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);

      /* get a 640 x 480 window */
    glutInitWindowSize(1280,1024);

      /* the window starts at the upper left corner of the screen */
    glutInitWindowPosition(0, 0);

    //register all the functions associated with this window...
    NeuralNetOutput.CreateGLWindow("Neural Net Control",1280,1024);
    glutDisplayFunc(&RenderNeuralNet);
    glutReshapeFunc(&ResizeNeuralNetGX);
    glutKeyboardFunc(&KeyboardNeuralNet);
    glutSpecialFunc(&SpecNeuralNet);
    glutMotionFunc(&mouseMoveNeuralNet);
    glutMouseFunc(&mouseFuncNeuralNet);
    glutIdleFunc(&RenderGlut);
    
    SetupSOM();
    
    runNet = true;
    //start UI Thread here...
    rc = pthread_create(&qtUIThread, NULL, QtUI, NULL);

    /* Start Event Processing Engine */
    glutMainLoop();

    return 1;
}

void SetupSOM()
{
    Minds.push_back(CavalcadeMind());
    _Genome.ClusterMaps.push_back(ClusterMap());
    SelfOrganisingMap::SOM2D(&_Genome.ClusterMaps[0],200,200,0.15,0.4);
    
    GAEngine::GenomeToMind(&Minds[0],&_Genome);
    
    Minds[0].StartMindThread_TW(1000,true);
}

void ResizeNeuralNetGX(int width,int height)
{
    NeuralNetOutput.ReSizeGLScene(width,height);
}

void KeyboardNeuralNet(unsigned char key, int x, int y)
{
    if(key=='1')
    {
        pthread_mutex_lock(&Minds[0].TWmutex);
        Minds.back().Cluster[0]->Neuron[0]->Fire();
        pthread_mutex_unlock(&Minds[0].TWmutex);
        
    }
    
    if(key=='2')
    {
        ((STDPGroup*)Minds.back().Cluster[0])->ResetChannels();
    }
    
    if(key==ESCAPE)
    {
        for(int m_c = 0; m_c<Minds.size(); m_c++)
        {
            Minds[m_c].StopMindThread();
        }
        runNet = false;
        exit(0);
    }
    NeuralNetOutput.KeyPressed(key,x,y);
}

void SpecNeuralNet(int key, int x, int y)
{
    NeuralNetOutput.KeyPressed((unsigned char) key,x,y);
}

void mouseFuncNeuralNet(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN)
        currentMouseButton = button;
    else
        currentMouseButton = 0;

    switch(button)
    {
        case GLUT_LEFT_BUTTON:
            NeuralNetOutput.nmx = x;
            NeuralNetOutput.nmy = y;
            break;
        case GLUT_MIDDLE_BUTTON:

            break;
        case GLUT_RIGHT_BUTTON:
            NeuralNetOutput.nmx = x;
            NeuralNetOutput.nmy = y;
            break;
        case GLUT_WHEEL_UP:
            NeuralNetOutput.zDelta+=30;
            NeuralNetOutput.windowposz = GLEngine::CalcZoom(NeuralNetOutput.zDelta);
            break;
        case GLUT_WHEEL_DOWN:
            NeuralNetOutput.zDelta-=30;
            NeuralNetOutput.windowposz = GLEngine::CalcZoom(NeuralNetOutput.zDelta);
            break;
    }

    return;
}

void mouseMoveNeuralNet(int x,int y)
{
    switch(currentMouseButton)
    {
        case GLUT_LEFT_BUTTON:
            NeuralNetOutput.pmx = NeuralNetOutput.nmx;
            NeuralNetOutput.pmy = NeuralNetOutput.nmy;
            NeuralNetOutput.nmx = x;
            NeuralNetOutput.nmy = y;
            NeuralNetOutput.windowposx += GLEngine::CalcPan(-NeuralNetOutput.pmx,-NeuralNetOutput.nmx);
            NeuralNetOutput.windowposy += GLEngine::CalcPan(NeuralNetOutput.pmy,NeuralNetOutput.nmy);
            break;
        case GLUT_MIDDLE_BUTTON:

            break;
        case GLUT_RIGHT_BUTTON:
            NeuralNetOutput.pmx = NeuralNetOutput.nmx;
            NeuralNetOutput.pmy = NeuralNetOutput.nmy;
            NeuralNetOutput.nmx = x;
            NeuralNetOutput.nmy = y;
            NeuralNetOutput.windowrotx += GLEngine::CalcRot(NeuralNetOutput.pmx,NeuralNetOutput.nmx);
            NeuralNetOutput.windowroty += GLEngine::CalcRot(NeuralNetOutput.pmy,NeuralNetOutput.nmy);
            break;

    }
}

void RenderNeuralNet()
{
    NeuralNetOutput.BeginRender();	//updates positions of viewpoint and clears screen buffers also clears screen
    //test data
    for(int m_c = 0; m_c<Minds.size(); m_c++)
    {
    CavalcadeMind * CNN = &Minds[m_c];
    if(CNN->RenderGraphics)
    {
        axon * axon2Draw = CNN->Axons.Head; //make rendering as efficient as possible
        

        for(int l_c = 0; l_c<CNN->Cluster.size(); l_c++)
        {
            for(int n_c = 0; n_c<CNN->Cluster[l_c]->Neuron.size(); n_c++)
            {
                if(CNN->Cluster[l_c]->Neuron[n_c]->refractory_countdown>0)
                {
                    NeuralNetOutput.DrawCube(CNN->Cluster[l_c]->Neuron[n_c]->position.x,CNN->Cluster[l_c]->Neuron[n_c]->position.y,CNN->Cluster[l_c]->Neuron[n_c]->position.z,0.1f,1.0f,1.0f,1.0f);
                    //if the neuron is in TW mode, can use the refactory countdown here to animate
                    if(CNN->Cluster[l_c]->Neuron[n_c]->ParentMind->_t_Window != NULL)
                    CNN->Cluster[l_c]->Neuron[n_c]->refractory_countdown=0;
                }
                
                else
                {
                    NeuralNetOutput.DrawCube(CNN->Cluster[l_c]->Neuron[n_c]->position.x,CNN->Cluster[l_c]->Neuron[n_c]->position.y,CNN->Cluster[l_c]->Neuron[n_c]->position.z,0.1f,CNN->Cluster[l_c]->Neuron[n_c]->neuCol.r,CNN->Cluster[l_c]->Neuron[n_c]->neuCol.g,CNN->Cluster[l_c]->Neuron[n_c]->neuCol.b);
                }
               
            }

        }

//        if(axon2Draw!=NULL)
//        do
//        {
//
//            if(axon2Draw->destination != NULL) //destination will be null if fire goes to external function
//            {
//                PlotPoint nsourcepos = axon2Draw->source->position;
//                PlotPoint ndestpos = axon2Draw->destination->position;
////                if(axon2Draw->source->ParentGroupID == axon2Draw->destination->ParentGroupID && axon2Draw->destination->ID <= axon2Draw->source->ID)
////                {
////                //plot curves
////                    if(axon2Draw->source->refractory_countdown>0)
////                    {
////                        if(axon2Draw->fire_magnitude>0)
////                            NeuralNetOutput.DrawCurve(&axon2Draw->ctrlpoints[0][0],3,4,0,1.0,0);
////                        else
////                            NeuralNetOutput.DrawCurve(&axon2Draw->ctrlpoints[0][0],3,4,1.0f,0,0);
////
////                    }
////                    else
////                    {
////                        NeuralNetOutput.DrawCurve(&axon2Draw->ctrlpoints[0][0],3,4,0.3f,0.3f,1.0f);
////                    }
////                }
////                else
//                    if(axon2Draw->source->refractory_countdown>0)
//                    {
//
//                        if(axon2Draw->fire_magnitude>0)
//                            NeuralNetOutput.DrawLine(nsourcepos.x,nsourcepos.y,nsourcepos.z,ndestpos.x,ndestpos.y,ndestpos.z,0,1.0f,0);
//                        else
//                            NeuralNetOutput.DrawLine(nsourcepos.x,nsourcepos.y,nsourcepos.z,ndestpos.x,ndestpos.y,ndestpos.z,1.0f,0,0);
//                        
//                    }
//                    else
//                    {
//                        NeuralNetOutput.DrawLine(nsourcepos.x,nsourcepos.y,nsourcepos.z,ndestpos.x,ndestpos.y,ndestpos.z,0.3f,0.3f,1.0f);
//                    }
//                }
//                axon2Draw = axon2Draw->next;
//            }
//            while(axon2Draw != NULL);
            
    }
    }
    NeuralNetOutput.SwapBuffer();
}

void ConnectAllNeurons(group* L1, group* L2, axonList * _axon) // connects all the neurons in L1 to all the neurons in L2
{
    for(int firstlayer = 0; firstlayer<(L1->Neuron.size()); firstlayer++) //for all the neurons in the first layer
        for(int secondlayer = 0; secondlayer<(L2->Neuron.size()); secondlayer++) // all the neurons in the second layer
        {
            _axon->Add(new axon(L1->Neuron[firstlayer], L2->Neuron[secondlayer],DEF_FIRE_MAG,DEF_SYN_DELAY)); //assign a new axon to a source and desination neuron
        }
}

void RenderGlut()
{
    RenderNeuralNet();
}