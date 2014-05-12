/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011, 2012, 2013, 2014 Emanuel Eichhammer               **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: http://www.qcustomplot.com/                          **
**             Date: 07.04.14                                             **
**          Version: 1.2.1                                                **
****************************************************************************/

/************************************************************************************************************
**                                                                                                         **
**  This is the example code for QCustomPlot.                                                              **
**                                                                                                         **
**  It demonstrates basic and some advanced capabilities of the widget. The interesting code is inside     **
**  the "setup(...)Demo" functions of MainWindow.                                                          **
**                                                                                                         **
**  In order to see a demo in action, call the respective "setup(...)Demo" function inside the             **
**  MainWindow constructor. Alternatively you may call setupDemo(i) where i is the index of the demo       **
**  you want (for those, see MainWindow constructor comments). All other functions here are merely a       **
**  way to easily create screenshots of all demos for the website. I.e. a timer is set to successively     **
**  setup all the demos and make a screenshot of the window area and save it in the ./screenshots          **
**  directory.                                                                                             **
**                                                                                                         **
*************************************************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
    srand(QDateTime::currentDateTime().toTime_t());
  ui->setupUi(this);
  setGeometry(400, 250, 542, 390);
}

void MainWindow::setupQuadraticDemo(QCustomPlot *customPlot)
{
    // Cumstumazation:
    TraitEventManager Manager;
    QString FName = this->ui->lineEdit->text();
    Manager.Stream.initializeWithFile(FName, Manager.Trait);
//    demoName = "Quadratic Demo";

    // generate some data:
    int itterations = this->ui->lineEdit_Itterations->text().toInt();
    QVector<double> x(itterations); // initialize with entries 0..100
    QVector<QVector<double>> y(TraitClass::Size);
    QVector<double> tmpy(itterations);
    y.fill(tmpy);

    double max = Manager.getKMembers(0), currentMembers;


    for (int itterator=0; itterator<itterations; ++itterator)
    {
        Manager.EvolutionStep();
        for(int currentTrait = 0; currentTrait < TraitClass::Size; currentTrait++)
        {
            currentMembers = Manager.getKMembers(currentTrait);
            y[currentTrait][itterator] = currentMembers;
            if(max < currentMembers && itterator > itterator/10)
                max = currentMembers;
        }
        if(itterator == 0)
            x[itterator] = Manager.Events.EventTimes[itterator]*1000;
        else
            x[itterator] = x[itterator-1] + Manager.Events.EventTimes[itterator]*1000;
    }

    // create graph and assign data to it:
    for(int currentTrait = 0; currentTrait < TraitClass::Size; currentTrait++)
    {
        customPlot->addGraph();
        customPlot->graph()->setData(x, y[currentTrait]);
        QPen graphPen;
        graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
        ui->customPlot->graph()->setPen(graphPen);

        double expected;
        if(TraitClass::Size < 3)
            expected = Manager.getStableDimorphStateOf(currentTrait);
        else expected = -1;

        QVector<double> tmpx(itterations);
        tmpx.fill(expected);
        customPlot->addGraph();
        customPlot->graph()->setData(x,tmpx);
        ui->customPlot->replot();
    }

    // give the axes some labels:
    customPlot->xAxis->setLabel("Milliseconds");
    customPlot->yAxis->setLabel("Members");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(0, x[itterations-1]);
    customPlot->yAxis->setRange(0, max);

    ui->customPlot->replot();// eigentlich am ende
}

MainWindow::~MainWindow()
{
  delete ui;
}










































void MainWindow::on_pushButton_clicked()
{
    setupQuadraticDemo(ui->customPlot);
}
