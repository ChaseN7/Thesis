#include "graphclass.h"
#include <cmath>

GraphClass::GraphClass(QString FName, bool rangeChecked) : Manager(FName)
{
    TimeLine.resize(TraitClass::Size);
    TraitHistory.resize(TraitClass::Size);
    Expected.resize(TraitClass::Size);
    Expected = Manager.retStableDimorphVector();
    maxMembers = 0;
    maxTime = 0;
    jumpedSteps = 1;
    isRangeControled = rangeChecked;
    for(int i = 0; i < TraitClass::Size; ++i){
        TimeLine[i].push_back(0);
        TraitHistory[i].push_back(Manager.getKMembers(i));
    }
}

bool GraphClass::isNear() const
{
    for(int i = 0; i < TraitClass::Size; ++i){
        double diff = TraitHistory[i].back() - Expected[i];
        if(diff > 5./sqrt(TraitClass::K) || diff < -5./sqrt(TraitClass::K))
            return false;
    }
    return true;
}

void GraphClass::reserveSize(const int maxIt)
{
    for(int i = 0; i < TraitClass::Size; ++i){
        TimeLine[i].reserve(maxIt);
        TraitHistory[i].reserve(maxIt);
    }
}

void GraphClass::makeJumpedEvSteps(int & Chosen, double & Time)
{
    for(int i = 0; i < jumpedSteps; ++i){
        Manager.EvolutionStep();
        Time += Manager.Events.EventTimes * 1000;
        Chosen = Manager.Events.ChosenTrait;
    }
}

void GraphClass::calcJumpedSteps(int & maxIt)
{
    while(true){
        if(maxIt*TraitClass::Size > pow(10,7)){
            maxIt /= 10;
            jumpedSteps *= 10;
        }
        else
            break;
    }
}

void GraphClass::iterateGraphPoint(double & Time, int & Chosen)
{
    makeJumpedEvSteps(Chosen, Time);
    TimeLine[Chosen].push_back(Time);
    TraitHistory[Chosen].push_back(Manager.getKMembers(Chosen));
    maxMembers = maxMembers < Manager.getKMembers(Chosen) ? Manager.getKMembers(Chosen) : maxMembers;
}

int GraphClass::makeIterations(const int maxIt)
{
    int Chosen;
    double Time = 0;
    for(int i = 0; i < maxIt; i++){
        iterateGraphPoint(Time, Chosen);
        if(isRangeControled)
            if(isNear()){
                for(int j = 0; j < std::min(i/3, maxIt-i); ++j)
                    iterateGraphPoint(Time, Chosen);
                return i + std::min(i/3, maxIt-i);
            }
    }
    return maxIt;
}

int GraphClass::generateEvolution(int maxIt)
{
    calcJumpedSteps(maxIt);
    reserveSize(maxIt);
    return makeIterations(maxIt);
}

double GraphClass::getMaxMembers() const
{
    return maxMembers;
}

double GraphClass::getMaxTime() const
{
    double max = 0;
    for(int i = 0; i < TraitClass::Size; ++i)
        if(max < TimeLine[i].back())
            max = TimeLine[i].back();
    return max;
}

QVector<double> GraphClass::getTimesOf(const int i) const
{
    return TimeLine.at(i);
}

QVector<double> GraphClass::getTraitHistOf(const int i) const
{
    return TraitHistory.at(i);
}

QVector<double> GraphClass::getExpectedVectorOf(const int i) const
{
    QVector<double> ExpV;
    ExpV.push_back(Expected[i]);
    ExpV.push_back(Expected[i]);
    return ExpV;
}

QVector<double> GraphClass::getXBorders() const
{
    QVector<double> XBorders;
    XBorders.push_back(0.);
    XBorders.push_back(getMaxTime());
    return XBorders;
}

double GraphClass::getExpectedOf(int i) const
{
    return Expected.at(i);
}
