#ifndef GRAPHCLASS_H
#define GRAPHCLASS_H
#include "traiteventmanager.h"
#include <QVector>
#include <QString>

class GraphClass
{
public:
    GraphClass(QString FName);

    void generateEvolution(int max_It);
    bool isNear();

    double getMaxMembers();
    double getMaxTime();
    double getExpectedOf(int i);
    QVector<double> getTimesOf(int i);
    QVector<double> getTraitHistOf(int i);

    TraitEventManager Manager;
    void makeIterations(int & maxIt);
private:
    void makeJumpedEvSteps(int &Chosen, double &Time);
    void calcJumpedSteps(int &maxIt);
    void reserveSize(int maxIt);

    QVector<QVector<double> > TimeLine;
    QVector<QVector<double> > TraitHistory;
    QVector<double> Expected;
    double maxMembers, maxTime;
    int jumpedSteps;
};

#endif // GRAPHCLASS_H
