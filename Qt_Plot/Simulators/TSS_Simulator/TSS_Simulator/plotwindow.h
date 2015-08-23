#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QWidget>
//#include "traiteventmanager.h"
#include "graphclass.h"

//class TraitEventManager;
namespace Ui {
class PlotWindow;
}

class PlotRenderer : public QObject {
    Q_OBJECT
signals:
    void renderedData(const GraphClass *, int);

public slots:
    void renderData(int iterations, QString FName, bool RangeCheck);
};

class PlotWindow : public QWidget
{
    Q_OBJECT

signals:
    void request_plot(int, QString, bool);
    void graphDrawn();

public:
    explicit PlotWindow(QWidget *parent = 0);
    void rePlot(int iterations, QString FName, bool RangeCheck);
    void createTraitGraphs(QVector<double> Exp);
    void drawGraphsWithClass(const GraphClass *Graph);
    void addGraphWithName(QString GName, QPen graphPen);

    ~PlotWindow();

public slots:
    void drawGraph(const GraphClass *g, int iterations);

//    void Plot(int max_it, QString FName);

//    void createGraph(QVector<double> x, QVector<QVector<double>> y, TraitEventManager Manager);
//    void fillXandY(double& max, QVector<QVector<double> > &y, TraitEventManager Manager, QVector<double> &x, int iterations);
//    int storeCoordinates(TraitEventManager Manager, int max_it);
//    void drawGraphsWithStoredData(int amount);

//    void plotGraphsWithData(QTextStream &out, int amount);
private slots:
    void on_pushButton_saveImage_clicked();

private:
    Ui::PlotWindow *ui;
//    QVector<double> x;
//    QVector<QVector<double> > y;
};

#endif // PLOTWINDOW_H
