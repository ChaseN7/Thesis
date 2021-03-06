#ifndef GRAPHCLASS_H
#define GRAPHCLASS_H
#include "traiteventmanager.h"
#include <QVector>
#include <QString>

class GraphClass
{
public:
    TraitEventManager Manager;

    GraphClass(QString FName, bool rangeChecked);

    int generateEvolution(int max_It);
    bool isNear() const;

    double getMaxMembers() const;
    double getMaxTime() const;
    double getExpectedOf(int i) const;
    QVector<double> getTimesOf(const int i) const;
    QVector<double> getTraitHistOf(const int i) const;
    QVector<double> getExpectedVectorOf(const int i) const;
    QVector<double> getExpectedVector() const;
    QVector<double> getXBorders() const;

    int makeIterations(const int maxIt);
    void iterateGraphPoint(double &Time, int &Chosen);

    /// private!
    /// Its only public for testing purpose!
    void calcJumpedSteps(int &maxIt);
    void reserveSize(const int maxIt);
private:
    void makeJumpedEvSteps(int &Chosen, double &Time);

    QVector<QVector<double> > TimeLine;
    QVector<QVector<double> > TraitHistory;
    QVector<double> Expected;
    double maxMembers, maxTime;
    int jumpedSteps;
    bool isRangeControled;
};

#endif // GRAPHCLASS_H
