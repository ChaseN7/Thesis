#include "graphclass.h"
#include <cmath>

GraphClass::GraphClass(QString FName) : Manager(FName)
{
    TimeLine.resize(TraitClass::Size);
    TraitHistory.resize(TraitClass::Size);
    Expected.resize(TraitClass::Size);
    Expected = Manager.retStableDimorphVector();
    maxMembers = 0;
    jumpedSteps = 1;
    for(int i = 0; i < TraitClass::Size; ++i){
        TimeLine[i].push_back(0);
        TraitHistory[i].push_back(Manager.getKMembers(i));
    }
}

void GraphClass::reserveSize(int maxIt)
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

void GraphClass::makeIterations(int & maxIt)
{
    int Chosen;
    double Time = 0;
    for(int i = 0; i < maxIt; i++){
        makeJumpedEvSteps(Chosen, Time);
        TimeLine[Chosen].push_back(Time);
        TraitHistory[Chosen].push_back(Manager.getKMembers(Chosen));
        maxMembers = maxMembers < Manager.getKMembers(Chosen) ? Manager.getKMembers(Chosen) : maxMembers;
        if(isNear())
            break;
    }
}

void GraphClass::generateEvolution(int maxIt)
{
    calcJumpedSteps(maxIt);
    reserveSize(maxIt);
    makeIterations(maxIt);
}

bool GraphClass::isNear()
{
    for(int i = 0; i < TraitClass::Size; ++i){
        double diff = TraitHistory[i].back() - Expected[i];
        if(diff > 15./sqrt(TraitClass::K) || diff < -15./sqrt(TraitClass::K))
            return false;
    }
    return true;
}

double GraphClass::getMaxMembers()
{
    return maxMembers;
}

double GraphClass::getMaxTime()
{
    double max = 0;
    for(int i = 0; i < TraitClass::Size; ++i)
        if(max < TimeLine[i].back())
            max = TimeLine[i].back();
    return max;
}

QVector<double> GraphClass::getTimesOf(int i)
{
    return TimeLine.at(i);
}

QVector<double> GraphClass::getTraitHistOf(int i)
{
    return TraitHistory.at(i);
}

double GraphClass::getExpectedOf(int i)
{
    return Expected.at(i);
}
