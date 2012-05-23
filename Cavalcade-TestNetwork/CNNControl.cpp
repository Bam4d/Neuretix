/*
 * File:   CNNControl.cpp
 * Author: bam4d
 *
 * Created on 28 November 2010, 13:56
 */

#include "CNNControl.h"


CNNControl::CNNControl(CavalcadeMind* cnn, Genome* genome) {
    widget.setupUi(this);

    _cnn = cnn;
    _genome = genome;
    connect(widget.but_OpenCNN,SIGNAL(clicked()),this,SLOT(LoadNetwork()));
    connect(widget.but_SaveCNN,SIGNAL(clicked()),this,SLOT(SaveNetwork()));
    connect(widget.but_LoadGenome,SIGNAL(clicked()),this,SLOT(LoadGenomeToMind()));
    connect(widget.but_LoadGenome_TW,SIGNAL(clicked()),this,SLOT(LoadGenomeToTWMind()));
}

void CNNControl::LoadNetwork()
{
    QString fileName;
    _cnn->StopMindThread();
    _cnn->Clear();

    fileName = QFileDialog::getOpenFileName(0,
     "Load Network", "./", "Cavalcade Neural Network Files (*.cnn)");

    SaveLoadCNN::LoadNetwork(fileName.toStdString(),&_cnn->Axons,&_cnn->Cluster,&_cnn->SimulationController);
    
    _cnn->StartMindThread(1000,true);
}

void CNNControl::SaveNetwork()
{
    QString fileName;
    _cnn->StopMindThread();

    fileName = QFileDialog::getSaveFileName(0,
     "Save Network", "/", "Cavalcade Neural Network Files (*.cnn)");

    SaveLoadCNN::SaveAxonData(_cnn->Axons,fileName.toStdString());


    _cnn->StartMindThread(1000,true);
}

void CNNControl::LoadGenomeToMind()
{
    QString fileName;
    _cnn->StopMindThread();
    _cnn->Clear();
    _genome->Clear();

    fileName = QFileDialog::getExistingDirectory(0,
     "Load Network", "Cavalcade Neural Network Genomes (*/)");
    string _fileName_std = fileName.toStdString();
    string _genomeID = _fileName_std.substr(_fileName_std.find_last_of('(')+1,_fileName_std.find_last_of(')')-(_fileName_std.find_last_of('(')+1));
    string _dataDir = _fileName_std.substr(0,_fileName_std.find_last_of('/',fileName.length()));
    if(_genome->LoadGenome(_dataDir,_genomeID,false)!=0)
        cout<<"Could not load genome "<<_fileName_std<<endl;
    else
        cout<<"Genome loaded!"<<endl;

    GAEngine::GenomeToMind(_cnn,_genome);

    _cnn->StartMindThread(1000,true);
}

void CNNControl::LoadGenomeToTWMind()
{
    QString _fileName;
    _cnn->StopMindThread_TW();
    _cnn->Clear();
    _genome->Clear();

    _fileName = QFileDialog::getExistingDirectory(0,
     "Load Network", "Cavalcade Neural Network Genomes (*/)");
    string _fileName_std = _fileName.toStdString();
    string _genomeID = _fileName_std.substr(_fileName_std.find_last_of('(')+1,_fileName_std.find_last_of(')')-(_fileName_std.find_last_of('(')+1));
    string _dataDir = _fileName_std.substr(0,_fileName_std.find_last_of('/',_fileName_std.length()));
    if(_genome->LoadGenome(_dataDir,_genomeID,false)!=0)
        cout<<"Could not load genome "<<_fileName_std<<endl;
    else
        cout<<"Genome loaded!"<<endl;
    
    GAEngine::GenomeToMind(_cnn,_genome);
    
    _cnn->StartMindThread_TW(1000,true);
}


CNNControl::~CNNControl() {
    _cnn->StopMindThread();
}
