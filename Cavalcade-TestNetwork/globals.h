#ifndef GLOBALS
#define GLOBALS

#include <math.h>			// Header File For Windows Math Library
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdarg.h>			// Header File For Variable Argument Routines
#include <iostream>			// Header File for file writing
#include <fstream>			// Header File for file writing
#include <string.h>
#include <vector>
#include <cstdlib>
#define GL_GLEXT_PROTOTYPES 1
#include <GL/glut.h>    // Header File For The GLUT Library
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library

using namespace std;

/* ascii code for the escape key */
#define ESCAPE 27
//
//#define DEF_REFRAC_LEV -0.3f //default refractory period potential
//#define DEF_REFRAC_TIME 10 //default refractory period period
//#define DEF_FIRETHRESH 0.7 //default neuron fire threshold
//#define DEF_EXC_TC 500 //default neuron excitation decay time constant
//#define DEF_FIRE_MAG 0.71 //default fire magnitude
//#define DEF_SYN_DELAY 10 // default synaptic delay
//
//#define DEF_SD_TC 2000.0f //default SDPD decay time constant
//#define DEF_SD_MAG 0.5 //default magnitude of supply spikes
//#define DEF_AXON_JOIN_THRESH 0.7 //default potential difference threshold to create a new axon
//#define DEF_DIST_CONST 1
//
//
//#define AVE_DIST 1.0f//multiplier distance between neurons
//
//typedef struct PlotPoint //used to position neurons etc in the graphical output
//{
//	float x,y,z;
//} PlotPoint;
//
//typedef struct RGB //used to position neurons etc in the graphical output
//{
//	float r,g,b;
//} RGB;
//
//PlotPoint SetPoint(float setx, float sety, float setz);
//
//class axon;
//// function pointer of axon to fire
//typedef axon* axonToFire;

#include "GLEngine.h"
#include "../CavalCade/CNNGlobals.h"
#include "../GenomeLoader/GenomeLoaderGlobals.h"

//void GetRandomNumbers(int number, int dec_places, double * randoms, bool net)
//{
//
//	double * rands_d;
//	if(net)
//	{
//		char buffer[1024];
//		char * site;
//		site = new char[number*(dec_places+4)];
//		strcpy(site,"");
//		double random = 0.0f;
//		HINTERNET hINet, hFile;
//		hINet = InternetOpen(L"InetURL/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );
//
//		wchar_t urlstring[255];
//		wsprintf(urlstring,L"http://www.random.org/decimal-fractions/?num=%d&dec=%d&col=1&format=plain&rnd=new",number,dec_places);
//		hFile = InternetOpenUrl( hINet, urlstring, NULL, 0, 0, 0 ) ;
//		if ( hFile )
//		{
//			DWORD dwRead;
//			while ( InternetReadFile( hFile, buffer, 1023, &dwRead ) )
//			{
//				if ( dwRead == 0 )
//					break;
//				buffer[dwRead] = 0;
//				strcat(site, buffer);
//			}
//			InternetCloseHandle( hFile );
//		}
//
//		InternetCloseHandle( hINet );
//		//cout<<site<<endl;
//		char ** rands_s;
//
//		rands_s = new char*[number];
//		rands_d = new double[number];
//		rands_s[0] = strtok(site,"\n");
//		rands_d[0] = atof(rands_s[0]);
//
//		for(int rand_count = 1; rand_count<number; rand_count++)
//		{
//			rands_s[rand_count] = strtok(NULL,"\n");
//			rands_d[rand_count] = atof(rands_s[rand_count]);
//		}
//
//		memcpy(randoms,rands_d,number*sizeof(double));
//
//		delete rands_s;
//
//		delete site;
//	}
//	else
//	{
//		//generate random numbers using rand()
//		rands_d = new double[number];
//		srand(GetTickCount());
//		for(int rand_count = 1; rand_count<number; rand_count++)
//		{
//			rands_d[rand_count] = double(rand()%1000)/(double)1000;
//		}
//
//		memcpy(randoms,rands_d,number*sizeof(double));
//	}
//
//	delete rands_d;
//
//}

#endif