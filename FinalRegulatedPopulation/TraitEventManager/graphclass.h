#ifndef GRAPHCLASS_H
#define GRAPHCLASS_H
#include "traiteventmanager.h"
#include <QVector>
#include <QString>

class GraphClass
{
public:
    GraphClass(QString FName, bool rangeChecked);

    int generateEvolution(int max_It);
    bool isNear() const;

    double getMaxMembers() const;
    double getMaxTime() const;
    double getExpectedOf(int i) const;
    QVector<double> getTimesOf(const int i) const;
    QVector<double> getTraitHistOf(const int i) const;
    QVector<double> getExpectedVectorOf(const int i) const;
    QVector<double> getXBorders() const;

    TraitEventManager Manager;
    int makeIterations(const int maxIt);
    void iterateGraphPoint(double &Time, int &Chosen);
private:
    void makeJumpedEvSteps(int &Chosen, double &Time);
    void calcJumpedSteps(int &maxIt);
    void reserveSize(const int maxIt);

    QVector<QVector<double> > TimeLine;
    QVector<QVector<double> > TraitHistory;
    QVector<double> Expected;
    double maxMembers, maxTime;
    int jumpedSteps;
    bool isRangeControled;
};

#endif // GRAPHCLASS_H
