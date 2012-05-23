/* 
 * File:   CNNControl.h
 * Author: bam4d
 *
 * Created on 28 November 2010, 13:56
 */

#ifndef _CNNCONTROL_H
#define	_CNNCONTROL_H

#include "../CavalCade/CNNGlobals.h"
#include "../GenomeLoader/GenomeLoaderGlobals.h"
#include "ui_CNNControl.h"
#include <QString>
#include <QFileDialog>
#include <iostream>

using namespace std;


class CNNControl : public QMainWindow {
    Q_OBJECT
public:
    CNNControl(CavalcadeMind*,Genome*);
    
    virtual ~CNNControl();

public slots:
    void LoadNetwork();
    void SaveNetwork();
    void LoadGenomeToMind();
    void LoadGenomeToTWMind();

     
private:
    Ui::CNNControl widget;
    CavalcadeMind* _cnn;
    Genome* _genome;
 
};

#endif	/* _CNNCONTROL_H */
