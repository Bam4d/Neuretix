#include "globals.h"

HINSTANCE g_hInst;

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI Net_Update(LPVOID); //updates the neural network ever 1 milisecond

void ConnectAllNeurons(group*, group*, axonList*); // connects all the neurons in L1 to all the neurons in L2
void GenerateActivationPlot(int, int);

wchar_t szClassName[ ] = L"EventCascadeNetwork";
HWND hwnd;
GLEngine Screen; //main neural network screen
LRESULT CALLBACK NNProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
GLEngine debugvars; // screen to output debugging vars
LRESULT CALLBACK debugProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
UINT uTimer;
HANDLE NetworkThread; //handle to the network thread
DWORD id_NN; // ID of the neural net thread
vector<group> Cluster; //vector containing neuron clusters


vector<ControlTimer> SimulationController;


int net_timer = 1000; //number of microseconds between neural network updates
int Timer = 1; //set fire timer to 0 so we can calculate times between fires etc

using namespace std;

//http://stackoverflow.com/questions/85122/sleep-less-than-one-millisecond
//use winsock libraries for usleep() because microsoft Sleep(1) doenst guarantee milisecond..just "at least" a milisecond
WORD wVersionRequested = MAKEWORD(1,0);
WSADATA wsaData;


//define usleep() command for milisecond sleeping

int usleep(long usec)
{
    struct timeval tv;
    fd_set dummy;
    SOCKET s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    FD_ZERO(&dummy);
    FD_SET(s, &dummy);
    tv.tv_sec = usec/1000000L;
    tv.tv_usec = usec%1000000L;
	int result = select(0, 0, 0, &dummy, &tv);
	closesocket(s);
    return result;
}

int WINAPI WinMain(	HINSTANCE	hThisInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{

	               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

	hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           L"EventCascadeNetwork",         /* Classname */
           L"CNN Simulation Environment - Menu",       /* Title Text */
           WS_POPUP|WS_SYSMENU|WS_CAPTION, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           670,                 /* The programs width */
           300,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );
	

	
	
	if (!debugvars.CreateGLWindow(L"DebugWnd",L"CNN Simulation Environment - Data Ouput",1024,768,32,debugProc)) //create openGL Window
	{
		return 0;									// Quit If Window Was Not Created
	}

	if (!Screen.CreateGLWindow(L"MainWnd",L"CNN Simulation Environment - View",1024,768,32,NNProc)) //create openGL Window
	{
		return 0;									// Quit If Window Was Not Created
	}
	
	ShowWindow(hwnd, TRUE);
	g_hInst = hThisInstance;
	

	/* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }
	

	return int(messages.wParam);							// Exit The Program
}

void StartSimulation(bool _runNet)
{
	render_graphics = true;

	if(_runNet)
	{
		run_network = true;
		NetworkThread = CreateThread(0, (ULONG)0, Net_Update, (LPVOID)(ULONG)0, (ULONG)0, &id_NN);
	}
}

void StopSimulation()
{
	render_graphics = false;
	run_network = false;
	Sleep(100); //allow screen to finish rendering last batch
}

DWORD WINAPI Net_Update(LPVOID)
{
	
	char databuf[255]; //buffer to store data in before written to file
	axon * axon2Update;

	Cluster[1].Neuron[2].Fire();

	do
	{

		//stop thread for a milisecond 
		usleep(net_timer); //1000 microseconds = 1 milisecond
		for(int l_c = 0; l_c<Cluster.size(); l_c++) //update all the groups of neurons
			Cluster[l_c].UpdateGroup();

		axon2Update = Axon.Head; //make rendering as efficient as possible
		
		if(axon2Update!=NULL)
		do
		{
			axon2Update->UpdateAxon(); //update the timings of the axons
			axon2Update = axon2Update->next;
		}
		while(axon2Update!=NULL);

		for(int timeout_count = 0; timeout_count<SimulationController.size(); timeout_count++)
		{
			if(Timer%SimulationController[timeout_count].Timeout == 0)
			{

				for(int neuronrecords = 0; neuronrecords<SimulationController[timeout_count].RecordTheseNeurons.size(); neuronrecords++)
				{
					sprintf(databuf,"%.4f ", Cluster[SimulationController[timeout_count].RecordTheseNeurons[neuronrecords].ClusterID].Neuron[SimulationController[timeout_count].RecordTheseNeurons[neuronrecords].NeuronID].excitation_level);
					(*SimulationController[timeout_count].DataOut) << databuf;	
				}

				for(int spikerecords = 0; spikerecords<SimulationController[timeout_count].RecordTheseSpikes.size(); spikerecords++)
				{
					int address = SimulationController[timeout_count].RecordTheseSpikes[spikerecords].AxonID;
					int spike = Axon[address]->isFiring>0 ? 1:0;
					sprintf(databuf,"%d ",spike);
					(*SimulationController[timeout_count].DataOut) << databuf;
				}
				//write a new line in the log file as all data has been logged
				if((*SimulationController[timeout_count].DataOut) != NULL)
				{
					sprintf(databuf,"\n");
					(*SimulationController[timeout_count].DataOut) << databuf;
				}

				for(int firerecords = 0; firerecords<SimulationController[timeout_count].FireThese.size(); firerecords++)
				{
					Cluster[SimulationController[timeout_count].FireThese[firerecords].ClusterID].Neuron[SimulationController[timeout_count].FireThese[firerecords].NeuronID].FireNeuron();
				}
			}

		}


		Timer++;
		
	}
	while(run_network);

	return 0;
}

double Calculate_Firing_Frequency(neuron * tocalc) //calculates the firing frequency from supply value and system constants
{ 
	double lg = 1.0f-(double)DEF_SD_MAG/tocalc->S_peak;
	if(lg<0) return 0;
	else
	return 1000/(DEF_SD_TC*-log(lg));
}



void DemoDestroy() //frees up the variables for the XORProblem
{
	run_network = false; //stop running the network
	//KillTimer(hwnd,uTimer);
	Sleep(100);
	//delete Axons;
	//delete [] Axon;
	//delete neuron clusters
	Cluster.clear();


}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	axon * axon2set;
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
			WSAStartup(wVersionRequested, &wsaData); //initialise the winsock library so usleep can be used
			
			//save buttons
			CreateWindowEx (0,L"button",L"Save Axon Data",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,20,200,130,25,hwnd,(HMENU)1006,g_hInst,NULL);
			CreateWindowEx (0,L"button",L"Save Cluster Data",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,170,200,130,25,hwnd,(HMENU)1007,g_hInst,NULL);
			CreateWindowEx (0,L"button",L"Save Control Data",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,320,200,130,25,hwnd,(HMENU)1012,g_hInst,NULL);
			CreateWindowEx (0,L"button",L"Save Network",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,500,200,130,25,hwnd,(HMENU)1011,g_hInst,NULL);


			//load buttons
			CreateWindowEx (0,L"button",L"Load Axon Data",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,20,150,130,25,hwnd,(HMENU)1008,g_hInst,NULL);
			CreateWindowEx (0,L"button",L"Load Cluster Data",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,170,150,130,25,hwnd,(HMENU)1009,g_hInst,NULL);
			CreateWindowEx (0,L"button",L"Load Control Data",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,320,150,130,25,hwnd,(HMENU)1013,g_hInst,NULL);
			CreateWindowEx (0,L"button",L"Load Network",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,500,150,130,25,hwnd,(HMENU)1010,g_hInst,NULL);

			

			CreateWindowEx (WS_EX_CLIENTEDGE,L"edit",L"1000",WS_CHILD | WS_VISIBLE | ES_NUMBER,20,60,60,25,hwnd,(HMENU)1003,g_hInst,NULL);
			CreateWindowEx (0,L"button",L"Change Speed",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,20,20,140,25,hwnd,(HMENU)1004,g_hInst,NULL);

			HFONT cfont; //create font for control window
			cfont = CreateFont(18,0,0,0,0,0,0,0,ANSI_CHARSET,0,0,ANTIALIASED_QUALITY,DEFAULT_PITCH,L"Sylfaen");
			
			for(int c=1000; c<1020; c++)
			{ //set the default font for items
				SendMessage(GetDlgItem(hwnd, c),WM_SETFONT,(WPARAM)cfont,MAKELPARAM(true,0));
			}
			
			uTimer = SetTimer(hwnd,1,1,NULL); //graphics update at default timings for setTimer

			Cluster.reserve(50000); //reserve numbers of clusters and axons otherwise axon pointers point to nothing on re-arranges
			
			RGB anyrgb1;
			anyrgb1.r = 1.0f;
			anyrgb1.g = 1.0f;
			anyrgb1.b = 0.5f;

			RGB anyrgb2;
			anyrgb1.r = 0.5f;
			anyrgb1.g = 1.0f;
			anyrgb1.b = 0.5f;

			RGB anyrgb3;
			anyrgb1.r = 1.0f;
			anyrgb1.g = 0.5f;
			anyrgb1.b = 0.5f;
			
			//Cluster.push_back(group(1,0));
			//Cluster.back().Line(1.0,SetPoint(-3,0,0),0);
			//Cluster.push_back(group(3,1));
			//Cluster.back().Circle(1.0,SetPoint(0,0,0),0);
			//
			Cluster.push_back(group(400,1, anyrgb1));
			Cluster.back().Circle(1.5,SetPoint(3.0,0,0),1);

			Cluster.push_back(group(400,2, anyrgb2));
			Cluster.back().Circle(1.0,SetPoint(0,3.0,0),0);

			Cluster.push_back(group(400,3, anyrgb3));
			Cluster.back().Circle(1.0,SetPoint(0,0,3.0),2);

			ConnectAllNeurons(&Cluster[0],&Cluster[1],&Axon);
			ConnectAllNeurons(&Cluster[1],&Cluster[2],&Axon);
			ConnectAllNeurons(&Cluster[2],&Cluster[0],&Axon);
			axon2set = Axon.Head;
			srand(GetTickCount());
			do
			{
				axon2set->synaptic_delay = rand()%5000;
				axon2set = axon2set->next;
			}
			while(axon2set!=NULL);
			
			
			//test2 = neuron::FindNeuronByID(3,&group::FindGroupByID(3,&Cluster)->Neuron);
			//ConnectAllNeurons(&Cluster[0],&Cluster[2]);

			StartSimulation(true);
            break;
		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{

				case 1004: //change speed button
					if(HIWORD(wParam)==BN_CLICKED)
					{
						wchar_t s_miliseconds[7];
						GetDlgItemText(hwnd,1003,s_miliseconds,7);
						int temp_time = _wtoi(s_miliseconds);
						if(temp_time < 1000000 && temp_time>10)
							net_timer = temp_time;

					}
					break;
				case 1006: //save axon data button
					if(HIWORD(wParam)==BN_CLICKED)
					{
						OPENFILENAME ofn;
						wchar_t szFileName[MAX_PATH] = L"";

						ZeroMemory(&ofn, sizeof(ofn));

						ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
						ofn.hwndOwner = hwnd;
						ofn.lpstrFilter = L"Xml Files (*.xml)\0*.xml\0All Files (*.*)\0*.*\0";
						ofn.lpstrFile = szFileName;
						ofn.nMaxFile = MAX_PATH;
						ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
						ofn.lpstrDefExt = L"xml";

						if(GetSaveFileName(&ofn))
						{
							SaveLoadCNN::SaveAxonData(Axon, szFileName);
						}
					}
					break;
				case 1007: //save cluster data button
					if(HIWORD(wParam)==BN_CLICKED)
					{
						OPENFILENAME ofn;
						wchar_t szFileName[MAX_PATH] = L"";

						ZeroMemory(&ofn, sizeof(ofn));

						ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
						ofn.hwndOwner = hwnd;
						ofn.lpstrFilter = L"Xml Files (*.xml)\0*.xml\0All Files (*.*)\0*.*\0";
						ofn.lpstrFile = szFileName;
						ofn.nMaxFile = MAX_PATH;
						ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
						ofn.lpstrDefExt = L"xml";

						if(GetSaveFileName(&ofn))
						{
							SaveLoadCNN::SaveClusterData(Cluster, szFileName);
						}
					}
					break;
				case 1008: //load axon data button
					if(HIWORD(wParam)==BN_CLICKED)
					{
						OPENFILENAME ofn;
						wchar_t szFileName[MAX_PATH] = L"";

						ZeroMemory(&ofn, sizeof(ofn));

						ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
						ofn.hwndOwner = hwnd;
						ofn.lpstrFilter = L"Xml Files (*.xml)\0*.xml\0All Files (*.*)\0*.*\0";
						ofn.lpstrFile = szFileName;
						ofn.nMaxFile = MAX_PATH;
						ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
						ofn.lpstrDefExt = L"xml";

						if(GetOpenFileName(&ofn))
						{
							StopSimulation();
							SaveLoadCNN::LoadAxonData(szFileName,&Axon,&Cluster);
							StartSimulation(false);
						}
					}
					break;
				case 1009: //load Cluster data button
					if(HIWORD(wParam)==BN_CLICKED)
					{
						OPENFILENAME ofn;
						wchar_t szFileName[MAX_PATH] = L"";

						ZeroMemory(&ofn, sizeof(ofn));

						ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
						ofn.hwndOwner = hwnd;
						ofn.lpstrFilter = L"Xml Files (*.xml)\0*.xml\0All Files (*.*)\0*.*\0";
						ofn.lpstrFile = szFileName;
						ofn.nMaxFile = MAX_PATH;
						ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
						ofn.lpstrDefExt = L"xml";

						if(GetOpenFileName(&ofn))
						{
							StopSimulation();
							SaveLoadCNN::LoadClusterData(szFileName,&Cluster);
							StartSimulation(false);
						}
					}
					break;
				case 1010:
					if(HIWORD(wParam)==BN_CLICKED)
					{
						OPENFILENAME ofn;
						wchar_t szFileName[MAX_PATH] = L"";

						ZeroMemory(&ofn, sizeof(ofn));

						ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
						ofn.hwndOwner = hwnd;
						ofn.lpstrFilter = L"Xml Files (*.xml)\0*.xml\0All Files (*.*)\0*.*\0";
						ofn.lpstrFile = szFileName;
						ofn.nMaxFile = MAX_PATH;
						ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
						ofn.lpstrDefExt = L"xml";

						if(GetOpenFileName(&ofn))
						{
							StopSimulation();
							SaveLoadCNN::LoadNetwork(szFileName,&Axon,&Cluster,&SimulationController);
							StartSimulation(true);
						}
					}
					break;
				case 1012: //save ControlMap data button
					if(HIWORD(wParam)==BN_CLICKED)
					{
						OPENFILENAME ofn;
						wchar_t szFileName[MAX_PATH] = L"";

						ZeroMemory(&ofn, sizeof(ofn));

						ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
						ofn.hwndOwner = hwnd;
						ofn.lpstrFilter = L"Xml Files (*.xml)\0*.xml\0All Files (*.*)\0*.*\0";
						ofn.lpstrFile = szFileName;
						ofn.nMaxFile = MAX_PATH;
						ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
						ofn.lpstrDefExt = L"xml";

						if(GetSaveFileName(&ofn))
						{
							SaveLoadCNN::SaveControlMap(szFileName,&SimulationController);
						}
					}
					break;
				case 1013: //load ControlMap data button
					if(HIWORD(wParam)==BN_CLICKED)
					{
						OPENFILENAME ofn;
						wchar_t szFileName[MAX_PATH] = L"";

						ZeroMemory(&ofn, sizeof(ofn));

						ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
						ofn.hwndOwner = hwnd;
						ofn.lpstrFilter = L"Xml Files (*.xml)\0*.xml\0All Files (*.*)\0*.*\0";
						ofn.lpstrFile = szFileName;
						ofn.nMaxFile = MAX_PATH;
						ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
						ofn.lpstrDefExt = L"xml";

						if(GetOpenFileName(&ofn))
						{
							StopSimulation();
							SaveLoadCNN::LoadControlMap(szFileName,&SimulationController);
							StartSimulation(true);
						}
					}
					break;
			}
		}
		break;
		case WM_TIMER:
			
			if(render_graphics)
			{
				axon * axon2Draw = Axon.Head; //make rendering as efficient as possible
				Screen.BeginRender();	//updates positions of viewpoint and clears screen buffers also clears screen

				for(int l_c = 0; l_c<Cluster.size(); l_c++)
				{
					for(int n_c = 0; n_c<Cluster[l_c].Neuron.size(); n_c++)
					{
						if(Cluster[l_c].Neuron[n_c].refractory_countdown>0)
							Screen.DrawCube(Cluster[l_c].Neuron[n_c].position.x,Cluster[l_c].Neuron[n_c].position.y,Cluster[l_c].Neuron[n_c].position.z,0.1f,1.0f,1.0f,1.0f);
						else
						{
							Screen.DrawCube(Cluster[l_c].Neuron[n_c].position.x,Cluster[l_c].Neuron[n_c].position.y,Cluster[l_c].Neuron[n_c].position.z,0.1f,Cluster[l_c].Neuron[n_c].neuCol.r,Cluster[l_c].Neuron[n_c].neuCol.g,Cluster[l_c].Neuron[n_c].neuCol.b);
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
									Screen.DrawCurve(&axon2Draw->ctrlpoints[0][0],3,4,0,1.0,0);
								else
									Screen.DrawCurve(&axon2Draw->ctrlpoints[0][0],3,4,1.0f,0,0);
								
							}
							else
							{
								Screen.DrawCurve(&axon2Draw->ctrlpoints[0][0],3,4,0.3f,0.3f,1.0f);
							}
						}
						else
							if(axon2Draw->source->refractory_countdown>0)
							{
								
							if(axon2Draw->fire_magnitude>0)
									Screen.DrawLine(nsourcepos.x,nsourcepos.y,nsourcepos.z,ndestpos.x,ndestpos.y,ndestpos.z,0,1.0f,0);
								else
									Screen.DrawLine(nsourcepos.x,nsourcepos.y,nsourcepos.z,ndestpos.x,ndestpos.y,ndestpos.z,1.0f,0,0);
							}
							else
							{
								Screen.DrawLine(nsourcepos.x,nsourcepos.y,nsourcepos.z,ndestpos.x,ndestpos.y,ndestpos.z,0.3f,0.3f,1.0f);
							}
					}
					axon2Draw = axon2Draw->next;
				}
				while(axon2Draw != NULL);
				Screen.SwapBuffer();

				//print texual output onto the debug window
				double printheight = 0; //used to calculate where to print text on screen
				int printlines = 0; //number of lines printed
				debugvars.BeginRender();
				char buf[255];
				sprintf(buf,"%d No. Axons: %d",Timer,Axon.Count());
				debugvars.DrawText(-0.052f,0.04f,1.0f,1.0f,1.0f,buf);
				
				axon2Draw = Axon.Head;
				//if(axon2Draw!=NULL)
				//do
				//{
				//	if(axon2Draw->destination != NULL) //destination will be null if fire goes to external function
				//	{
				//		int destParentID = axon2Draw->destination->ParentGroupID;
				//		int sourceParentID = axon2Draw->source->ParentGroupID;
				//		//if(destowner == &Cluster[2])
				//		//{
				//		sprintf(buf,"Axon: %d Source: L%d:N%d Dest: L%d:N%d Fire Mag: %.5f",axon2Draw->ID,sourceParentID,axon2Draw->source->ID,destParentID,axon2Draw->destination->ID,axon2Draw->fire_magnitude);
				//			Screen.DrawText(0.01f,0.04f-(double)(axon2Draw->ID+1)/500.0f,1.0f,1.0f,1.0f,buf);
				//		//}
				//	}
				//axon2Draw = axon2Draw->next;
				//}
				//while(axon2Draw != NULL);
				debugvars.SwapBuffer();	// Swap Buffer (Double Buffering)
			}
			break;
        case WM_DESTROY:
			DemoDestroy();
			PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}

void ConnectAllNeurons(group* L1, group* L2, axonList * _axon) // connects all the neurons in L1 to all the neurons in L2
{
	
	for(int firstlayer = 0; firstlayer<(L1->Neuron.size()); firstlayer++) //for all the neurons in the first layer
		for(int secondlayer = 0; secondlayer<(L2->Neuron.size()); secondlayer++) // all the neurons in the second layer
		{
			_axon->Add(new axon(&L1->Neuron[firstlayer], &L2->Neuron[secondlayer],DEF_FIRE_MAG,DEF_SYN_DELAY)); //assign a new axon to a source and desination neuron
		}
}

LRESULT CALLBACK NNProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	

	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				Screen.active=TRUE;						// Program Is Active
			}
			else
			{
				Screen.active=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			DemoDestroy();
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}
		break;
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
			Screen.nmx = LOWORD(lParam);
			Screen.nmy = HIWORD(lParam);
			break;
		case WM_MOUSEMOVE:
			switch(wParam)
			{
				
				case MK_LBUTTON: //pan the screen
					Screen.pmx = Screen.nmx;
					Screen.pmy = Screen.nmy;
					Screen.nmx = LOWORD(lParam);
					Screen.nmy = HIWORD(lParam);
					Screen.windowposx += GLEngine::CalcPanX(Screen.pmx,Screen.nmx);
					Screen.windowposy += GLEngine::CalcPanY(Screen.pmy,Screen.nmy);
					break;
				case MK_RBUTTON:
					Screen.pmx = Screen.nmx;
					Screen.pmy = Screen.nmy;
					Screen.nmx = LOWORD(lParam);
					Screen.nmy = HIWORD(lParam);
					Screen.windowrotx += GLEngine::CalcRotX(Screen.pmx,Screen.nmx);
					Screen.windowroty += GLEngine::CalcRotY(Screen.pmy,Screen.nmy);
					break;
			}
			break;
		case WM_MOUSEWHEEL:
			Screen.zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			Screen.windowposz += GLEngine::CalcZoom(Screen.zDelta);
			break;
		case WM_KEYDOWN:							// Is A Key Being Held Down?
			
			return 0;								// Jump Back
		break;
		case WM_KEYUP:								// Has A Key Been Released?
		{
			switch(wParam)
			{
				case VK_F1:
				Screen.KillGLWindow();						// Kill Our Current Window
				Screen.fullscreen=!Screen.fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if(Screen.fullscreen)
				{
					if (!Screen.CreateGLWindow(L"MainWnd",L"CNN Simulation Environment - View",GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN),32,NNProc))
					{
						return 0;						// Quit If Window Was Not Created
					}
				}
				else
				if (!Screen.CreateGLWindow(L"MainWnd",L"CNN Simulation Environment - View",1024,768,32,NNProc)) //create openGL Window
				{
					return 0;									// Quit If Window Was Not Created
				}

				break;
			}
			return 0;								// Jump Back
		}
		break;

		case WM_SIZE:								// Resize The OpenGL Window
		{
			Screen.ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
		break;
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

LRESULT CALLBACK debugProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	int nmx = 0,nmy = 0; //previouse positions of mouse and new positions
	int zDelta = 0; //mouse wheel position indicator

	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				debugvars.active=TRUE;						// Program Is Active
			}
			else
			{
				debugvars.active=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			DemoDestroy();
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}
		break;
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
			nmx = LOWORD(lParam);
			nmy = HIWORD(lParam);
			break;
		case WM_MOUSEMOVE:
			switch(wParam)
			{
				
				case MK_LBUTTON: //pan the screen
					debugvars.pmx = nmx;
					debugvars.pmy = nmy;
					nmx = LOWORD(lParam);
					nmy = HIWORD(lParam);
					debugvars.windowposx += GLEngine::CalcPanX(debugvars.pmx,nmx);
					debugvars.windowposy += GLEngine::CalcPanY(debugvars.pmy,nmy);
					break;
				case MK_RBUTTON:
					debugvars.pmx = nmx;
					debugvars.pmy = nmy;
					nmx = LOWORD(lParam);
					nmy = HIWORD(lParam);
					debugvars.windowrotx += GLEngine::CalcRotX(debugvars.pmx,nmx);
					debugvars.windowroty += GLEngine::CalcRotY(debugvars.pmy,nmy);
					break;
			}
			break;
		case WM_MOUSEWHEEL:
			zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			debugvars.windowposz += GLEngine::CalcZoom(zDelta);
			break;
		case WM_KEYDOWN:							// Is A Key Being Held Down?
			switch(wParam)
			{
				case VK_F1:

				break;
			}
			return 0;								// Jump Back
		break;
		case WM_KEYUP:								// Has A Key Been Released?
		{
			
			return 0;								// Jump Back
		}
		break;
		
		break;
		case WM_SIZE:								// Resize The OpenGL Window
		{
			debugvars.ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
		break;
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

