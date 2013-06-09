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

void ConnectAllNeurons(group* , group* , axonList * );

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
vector<Genome> Genomes;
int sample(mglGraph *gr)
{
    gr->SetRanges(0,1,0,1,0,1);
    mglData x(50),y(50),z(50),rx(10),ry(10), a(20,30);
    a.Modify("30*x*y*(1-x-y)^2*(x+y<1)");
    x.Modify("0.25*(1+cos(2*pi*x))");
    y.Modify("0.25*(1+sin(2*pi*x))");
    rx.Modify("rnd"); ry.Modify("(1-v)*rnd",rx);
    z.Modify("x");

    gr->Title("Projection sample");
    gr->Ternary(4);
    gr->Rotate(50,60);      gr->Light(true);
    gr->Plot(x,y,z,"r2");   gr->Surf(a,"#");
    gr->Axis(); gr->Grid(); gr->Box();
    gr->Label('x',"X",1);   gr->Label('y',"Y",1);   gr->Label('z',"Z",1);
    return 0;
}

//looks after the Qt Window stuff on separate thread
void *QtUI(void *)
{
    /* set up the Qt window stuff*/
    QApplication app(NULL, NULL);

    QMainWindow *Wnd = new QMainWindow;
    Wnd->resize(810,610);  // for fill up the QMGL, menu and toolbars
    Wnd->setWindowTitle("QMathGL sample");
    // here I allow to scroll QMathGL -- the case
    // then user want to prepare huge picture
    QScrollArea *scroll = new QScrollArea(Wnd);

    // Create and setup QMathGL
    QMathGL *QMGL = new QMathGL(Wnd);
  //QMGL->setPopup(popup); // if you want to setup popup menu for QMGL
    QMGL->setDraw(sample);
    // or use QMGL->setDraw(foo); for instance of class Foo:public mglDraw
    QMGL->update();

    // continue other setup (menu, toolbar and so on)
    scroll->setWidget(QMGL);
    Wnd->setCentralWidget(scroll);
    Wnd->show();

    app.exec();

    pthread_exit(NULL);
}

void setupNetwork(Genome* genome, CavalcadeMind* mind) 
{
    genome->ClusterMaps.push_back(ClusterMap());
    //create the input group of 5 neurons
    ClusterMap* selfOrganisingLayer = &genome->ClusterMaps[0]; //everything has to be encoded with cluster map structures for simplicity of conversion into minds.
    
    group* inputGroup = new group();;
    inputGroup->Init(5,1,RGB(0,0,255));
    inputGroup->Line(1.0, PlotPoint(0,1.0,0), 0);
    selfOrganisingLayer->clusters.push_back(inputGroup);
    
    STDPGroup* somGroup = SelfOrganisingMap::SOM1D(selfOrganisingLayer,5,1.0, PlotPoint(0,0,0), 6.0);
    
    for(int firstlayer = 0; firstlayer<(inputGroup->Neuron.size()); firstlayer++) //for all the neurons in the first layer
        for(int secondlayer = 0; secondlayer<(somGroup->Neuron.size()); secondlayer++) // all the neurons in the second layer
        {
            selfOrganisingLayer->Axons.Add(new axon(inputGroup->Neuron[firstlayer], somGroup->Neuron[secondlayer],0.2,1)); //assign a new axon to a source and desination neuron
        }
    
   GAEngine::GenomeToMind(mind,genome);
   
    mind->StartMindThread_TW(1000,true);
    
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

    Minds.push_back(CavalcadeMind());
    Genomes.push_back(Genome());
    
    setupNetwork(&Genomes[0],&Minds[0]);
    
    runNet = true;
    //start UI Thread here...
    rc = pthread_create(&qtUIThread, NULL, QtUI, NULL);

    /* Start Event Processing Engine */
    glutMainLoop();

    return 1;
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
        pthread_mutex_lock(&Minds[0].TWmutex);
        Minds.back().Cluster[0]->Neuron[1]->Fire();
        pthread_mutex_unlock(&Minds[0].TWmutex);
        
    }
    
    if(key=='3')
    {
        pthread_mutex_lock(&Minds[0].TWmutex);
        Minds.back().Cluster[0]->Neuron[2]->Fire();
        pthread_mutex_unlock(&Minds[0].TWmutex);
        
    }
    
    if(key=='4')
    {
        pthread_mutex_lock(&Minds[0].TWmutex);
        Minds.back().Cluster[0]->Neuron[3]->Fire();
        pthread_mutex_unlock(&Minds[0].TWmutex);
        
    }
    
    if(key=='5')
    {
        pthread_mutex_lock(&Minds[0].TWmutex);
        Minds.back().Cluster[0]->Neuron[4]->Fire();
        pthread_mutex_unlock(&Minds[0].TWmutex);
        
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
                    NeuralNetOutput.DrawCube(CNN->Cluster[l_c]->Neuron[n_c]->position.x,CNN->Cluster[l_c]->Neuron[n_c]->position.y,CNN->Cluster[l_c]->Neuron[n_c]->position.z,0.1f,1.0f,1.0f,1.0f);
                else
                {
                    NeuralNetOutput.DrawCube(CNN->Cluster[l_c]->Neuron[n_c]->position.x,CNN->Cluster[l_c]->Neuron[n_c]->position.y,CNN->Cluster[l_c]->Neuron[n_c]->position.z,0.1f,CNN->Cluster[l_c]->Neuron[n_c]->neuCol.r,CNN->Cluster[l_c]->Neuron[n_c]->neuCol.g,CNN->Cluster[l_c]->Neuron[n_c]->neuCol.b);
                }
                        /*
                for(int x = 1; x<2000; x++)
                {
                        Screen.PlotLine((float)x/250.0f+10*l_c,PlotPoints[datacount][x]+n_c*1.5f,(float)(x-1)/250.0f+10*l_c,PlotPoints[datacount][x-1]+n_c*1.5f,0,0,1.0f,0,0);
                        Screen.PlotLine((float)x/250.0f+10*l_c,PlotPoints[datacount+1][x]+n_c*1.5f,(float)(x-1)/250.0f+10*l_c,PlotPoints[datacount+1][x-1]+n_c*1.5f,0,0,0,1.0f,0);
                        Screen.PlotLine((float)x/250.0f+10*l_c,PlotPoints[datacount+2][x]+n_c*1.5f,(float)(x-1)/250.0f+10*l_c,PlotPoints[datacount+2][x-1]+n_c*1.5f,0,0,0,0,1.0f);
                }
                datacount+=3;
*/
            }

        }

        if(axon2Draw!=NULL)
        do
        {

            if(axon2Draw->destination != NULL) //destination will be null if fire goes to external function
            {
                PlotPoint nsourcepos = axon2Draw->source->position;
                PlotPoint ndestpos = axon2Draw->destination->position;
                if(axon2Draw->source->ParentGroupID == axon2Draw->destination->ParentGroupID && axon2Draw->destination->ID <= axon2Draw->source->ID)
                {
                //plot curves
                    if(axon2Draw->source->refractory_countdown>0)
                    {
                        if(axon2Draw->fire_magnitude>0)
                            NeuralNetOutput.DrawCurve(&axon2Draw->ctrlpoints[0][0],3,4,0,1.0,0);
                        else
                            NeuralNetOutput.DrawCurve(&axon2Draw->ctrlpoints[0][0],3,4,1.0f,0,0);

                    }
                    else
                    {
                        NeuralNetOutput.DrawCurve(&axon2Draw->ctrlpoints[0][0],3,4,0.3f,0.3f,1.0f);
                    }
                }
                else
                    if(axon2Draw->source->refractory_countdown>0)
                    {

                        if(axon2Draw->fire_magnitude>0)
                            NeuralNetOutput.DrawLine(nsourcepos.x,nsourcepos.y,nsourcepos.z,ndestpos.x,ndestpos.y,ndestpos.z,0,1.0f,0);
                        else
                            NeuralNetOutput.DrawLine(nsourcepos.x,nsourcepos.y,nsourcepos.z,ndestpos.x,ndestpos.y,ndestpos.z,1.0f,0,0);
                    }
                    else
                    {
                        NeuralNetOutput.DrawLine(nsourcepos.x,nsourcepos.y,nsourcepos.z,ndestpos.x,ndestpos.y,ndestpos.z,0.3f,0.3f,1.0f);
                    }
                }
                axon2Draw = axon2Draw->next;
            }
            while(axon2Draw != NULL);
            
    }
    }
    NeuralNetOutput.SwapBuffer();
}

void RenderGlut()
{
    RenderNeuralNet();
}