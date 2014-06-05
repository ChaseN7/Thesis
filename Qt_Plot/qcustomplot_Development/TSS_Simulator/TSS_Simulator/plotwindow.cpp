#include "plotwindow.h"
#include "ui_plotwindow.h"
#include <cmath>
#include <QThread>

bool isNear(double Value, double Expected, double K){
    double diff = Value - Expected;
    if( diff < 10./K && diff > -10./K)
        return true;
    return false;
}

/** \class PlotRenderer
 * \brief Simple QObject for data rendering
 *
 * This class takes account of the heavy work
 * which is being done by GraphClass::generateEvolution().
 *
 * Since generateEvolution() can take a huge amount of time,
 * one can simply move this class to another QThread
 *
 * \sa PlotWindow
*/

/** \brief Renders the data given by \a FName
 * \param iterations max number of iterations
 * \param FName file name of the data
 * \param RangeCheck whether to check the range of the data
 */
void PlotRenderer::renderData(int iterations, QString FName, bool RangeCheck){
    //! We use GraphClass to create the data
    GraphClass * graph = new GraphClass(FName, RangeCheck);

    int it_made = graph->generateEvolution(iterations);

    emit renderedData(graph, it_made);
}

// --------------------------------------

PlotWindow::PlotWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotWindow)
{
    ui->setupUi(this);
    ui->customPlot->xAxis->setLabel("Time");
    ui->customPlot->yAxis->setLabel("Population");

    PlotRenderer * plotter = new PlotRenderer;

    QThread * thread = new QThread(this);
    connect(this,SIGNAL(destroyed()), thread, SLOT(quit()));

    plotter->moveToThread(thread);

    connect(this,   SIGNAL(request_plot(int,QString,bool)),
            plotter,SLOT(renderData(int,QString,bool)),
            Qt::QueuedConnection);
    connect(plotter,SIGNAL(renderedData(const GraphClass*,int)),
            this, SLOT(drawGraph(const GraphClass*,int)),
            Qt::QueuedConnection);
    thread->start();
}

void PlotWindow::drawGraph(const GraphClass * Graph, int iterations){
    ui->customPlot->clearGraphs();
    ui->label_iterations->setText("Iterations: " + QString::number(iterations));
    createTraitGraphs(Graph->Manager.retStableMonoKVector());
    drawGraphsWithClass(Graph);

    emit graphDrawn();
}

void PlotWindow::addGraphWithName(QString GName, QPen graphPen)
{
    ui->customPlot->addGraph();
    ui->customPlot->graph()->setName(GName);
    ui->customPlot->graph()->setLineStyle(QCPGraph::lsStepLeft);
    ui->customPlot->graph()->setPen(graphPen);
}

void PlotWindow::createTraitGraphs(QVector<double> Exp)
{
    QVector<QPen> graphPen(TraitClass::Size);
    for(int currentTrait = 0; currentTrait < TraitClass::Size; currentTrait++){
        graphPen[currentTrait].setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
        addGraphWithName(QString::number(currentTrait+1) + ". Trait", graphPen[currentTrait]);
        graphPen[currentTrait].setStyle(Qt::DashDotLine);
        addGraphWithName(QString::number(currentTrait+1) + ". Exp: " + QString::number(Exp.at(currentTrait)), graphPen[currentTrait]);
    }
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void PlotWindow::drawGraphsWithClass(const GraphClass * Graph)
{
    for(int i = 0; i < TraitClass::Size; ++i){
        ui->customPlot->graph(i*2)->setData(Graph->getTimesOf(i),Graph->getTraitHistOf(i));
        ui->customPlot->graph(i*2+1)->setData(Graph->getXBorders(),Graph->getExpectedMonomorphOf(i));
    }
    ui->customPlot->yAxis->setRange(0,Graph->getMaxMembers());
    ui->customPlot->xAxis->setRange(0,Graph->getMaxTime());
    ui->customPlot->replot();
    delete Graph;
}

void PlotWindow::rePlot(int iterations, QString FName, bool RangeCheck)
{
    ui->lineEdit_ImageName->setText(FName);
    emit request_plot(iterations, FName, RangeCheck);
}

void PlotWindow::on_pushButton_saveImage_clicked()
{
    ui->customPlot->savePdf(ui->lineEdit_ImageName->text()+ ".pdf");
    ui->customPlot->savePng(ui->lineEdit_ImageName->text()+ ".png");
}

PlotWindow::~PlotWindow()
{
    delete ui;
}

//void PlotWindow::Plot(int max_it, QString FName)
//{
//    ui->customPlot->clearGraphs();
//    TraitEventManager Manager(FName);
//    double max = Manager.getKMembers(0);

//    int PointAmount = storeCoordinates(Manager, max_it);
//    drawGraphsWithStoredData(PointAmount);

//    ui->customPlot->yAxis->setRange(0, max);

//    ui->customPlot->replot();
//}

//void PlotWindow::plotGraphsWithData(QTextStream & out, int amount)
//{
//    double x_coord;
//    for (int itterator=0; itterator< amount; ++itterator){
//        out>>x_coord;
//        for(int currentTrait = 0; currentTrait < TraitClass::Size; currentTrait++){
//            double y_coord;
//            out>>y_coord;
//            ui->customPlot->graph(currentTrait)->addData(x_coord, y_coord);
//        }
//    }
//    ui->customPlot->xAxis->setRange(0, x_coord);
//}

//void PlotWindow::drawGraphsWithStoredData(int amount)
//{
//    createTraitGraphs();

//    QFile Storage("Storage.txt");
//    Storage.open(QFile::ReadOnly | QFile::Text);
//    QTextStream out(&Storage);

//    plotGraphsWithData(out, amount);

//    Storage.close();
//    QFile::remove("Storage.txt");
//}

//void PlotWindow::createGraph(QVector<double> x, QVector<QVector<double>> y, TraitEventManager Manager)
//{
//    for(int currentTrait = 0; currentTrait < TraitClass::Size; currentTrait++)
//    {
//        ui->customPlot->addGraph();
//        ui->customPlot->graph()->setName(QString::number(currentTrait+1) + ". Trait");
//        ui->customPlot->graph()->setData(x, y[currentTrait]);
//        QPen graphPen;
//        graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
//        ui->customPlot->graph()->setPen(graphPen);

//        double expected;
//        expected = Manager.retStableDimorphOf(currentTrait);

//        QVector<double> tmpy(2);
//        QVector<double> tmpx;
//        tmpx.push_back(0);
//        tmpx.push_back(x.last());
//        tmpy.fill(expected);
//        ui->customPlot->addGraph();
//        ui->customPlot->graph()->setName(QString::number(currentTrait+1) + ". Expected = " + QString::number(expected));
//        ui->customPlot->graph()->setData(tmpx,tmpy);
//        ui->customPlot->replot();
//    }
//}

//void PlotWindow::fillXandY(double& max, QVector<QVector<double>>& y,
//                           TraitEventManager Manager, QVector<double>& x, int max_iterations)
//{
//    std::vector<double> expected = Manager.retStableDimorphVector();
//    for (int itterator=0; itterator< max_iterations; ++itterator)
//    {
//        bool close = true;
//        Manager.EvolutionStep();
//        if(itterator == 0)
//            x.push_back(Manager.Events.EventTimes*1000);
//        else
//            x.push_back(x[itterator-1] + Manager.Events.EventTimes*1000);
//        for(int currentTrait = 0; currentTrait < TraitClass::Size; currentTrait++)
//        {
//            double currentMembers = Manager.getKMembers(currentTrait);
//            y[currentTrait].push_back(currentMembers);
//            //y[currentTrait][itterator] = currentMembers;
//            if(max < currentMembers && itterator > itterator/10)
//                max = currentMembers;
//            close = close && isNear(Manager.getKMembers(currentTrait), expected[currentTrait], TraitClass::K);
//        }
//        if(close)
//            return;
//    }
//}

//int PlotWindow::storeCoordinates(TraitEventManager Manager, int max_it)
//{
//    FileStreaming Stream;
//    return Stream.storeEvolution(Manager, max_it);
//}

