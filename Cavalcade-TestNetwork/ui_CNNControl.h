/********************************************************************************
** Form generated from reading UI file 'CNNControl.ui'
**
** Created: Sun Jan 27 15:16:47 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CNNCONTROL_H
#define UI_CNNCONTROL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CNNControl
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QPushButton *but_OpenCNN;
    QPushButton *but_SaveCNN;
    QGroupBox *groupBox_2;
    QPushButton *but_LoadGenome;
    QPushButton *but_LoadGenome_2;
    QPushButton *but_LoadGenome_TW;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CNNControl)
    {
        if (CNNControl->objectName().isEmpty())
            CNNControl->setObjectName(QString::fromUtf8("CNNControl"));
        CNNControl->resize(410, 177);
        centralwidget = new QWidget(CNNControl);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 20, 201, 171));
        but_OpenCNN = new QPushButton(groupBox);
        but_OpenCNN->setObjectName(QString::fromUtf8("but_OpenCNN"));
        but_OpenCNN->setGeometry(QRect(20, 30, 111, 27));
        but_SaveCNN = new QPushButton(groupBox);
        but_SaveCNN->setObjectName(QString::fromUtf8("but_SaveCNN"));
        but_SaveCNN->setGeometry(QRect(20, 60, 112, 27));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(230, 20, 231, 171));
        but_LoadGenome = new QPushButton(groupBox_2);
        but_LoadGenome->setObjectName(QString::fromUtf8("but_LoadGenome"));
        but_LoadGenome->setGeometry(QRect(20, 30, 111, 27));
        but_LoadGenome_2 = new QPushButton(groupBox_2);
        but_LoadGenome_2->setObjectName(QString::fromUtf8("but_LoadGenome_2"));
        but_LoadGenome_2->setGeometry(QRect(10, 170, 111, 27));
        but_LoadGenome_TW = new QPushButton(groupBox_2);
        but_LoadGenome_TW->setObjectName(QString::fromUtf8("but_LoadGenome_TW"));
        but_LoadGenome_TW->setGeometry(QRect(20, 70, 131, 27));
        CNNControl->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CNNControl);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 410, 25));
        CNNControl->setMenuBar(menubar);
        statusbar = new QStatusBar(CNNControl);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        CNNControl->setStatusBar(statusbar);

        retranslateUi(CNNControl);

        QMetaObject::connectSlotsByName(CNNControl);
    } // setupUi

    void retranslateUi(QMainWindow *CNNControl)
    {
        CNNControl->setWindowTitle(QApplication::translate("CNNControl", "CNNControl", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("CNNControl", "Network Options", 0, QApplication::UnicodeUTF8));
        but_OpenCNN->setText(QApplication::translate("CNNControl", "Load Network", 0, QApplication::UnicodeUTF8));
        but_SaveCNN->setText(QApplication::translate("CNNControl", "Save Network", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("CNNControl", "Genome Options", 0, QApplication::UnicodeUTF8));
        but_LoadGenome->setText(QApplication::translate("CNNControl", "Load Genome", 0, QApplication::UnicodeUTF8));
        but_LoadGenome_2->setText(QApplication::translate("CNNControl", "Load Genome", 0, QApplication::UnicodeUTF8));
        but_LoadGenome_TW->setText(QApplication::translate("CNNControl", "Load Genome TW", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CNNControl: public Ui_CNNControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CNNCONTROL_H
