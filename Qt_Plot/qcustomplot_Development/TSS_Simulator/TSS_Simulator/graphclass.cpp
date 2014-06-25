#include "graphclass.h"
#include <cmath>

GraphClass::GraphClass(QString FName, bool rangeChecked) : Manager(FName)
{
    TimeHistory.resize(TraitClass::Size);
    TraitHistory.resize(TraitClass::Size);
    ExpectedDimorph.resize(TraitClass::Size);
    ExpectedDimorph = Manager.retStableDimorphKVector();
    ExpectedMonomorph = Manager.retStableMonoKVector();
    maxMembers = 0;
    maxTime = 0;
    jumpedSteps = 1;
    isRangeControled = rangeChecked;
    for(int i = 0; i < TraitClass::Size; ++i){
        TimeHistory[i].push_back(0);
        TraitHistory[i].push_back(Manager.getKMembers(i));
    }
}

bool GraphClass::isNearDimorph() const
{
    for(int i = 0; i < TraitClass::Size; ++i){
        double diff = TraitHistory[i].back() - ExpectedDimorph[i];
        if(diff > 5./sqrt(TraitClass::K) || diff < -5./sqrt(TraitClass::K))
            return false;
    }
    return true;
}

bool GraphClass::isNearMonomorph() const
{
    for(int i = 0; i < TraitClass::Size; ++i){
        double diff = TraitHistory[i].back() - ExpectedMonomorph[i];
        if(diff > 5./sqrt(TraitClass::K) || diff < -5./sqrt(TraitClass::K))
            return false;
    }
    return true;
}

bool GraphClass::isNearTSS(const int & chosen) const
{
    /// Check that there is only one surviver and store him in "activeTrait"
    /// FIXME: effektivere Schleife? Speichere vielleicht zusätzlich nur das dominante Trait?
    for(int i = 0; i < TraitClass::Size; ++i){
        if(i != chosen && Manager.getKMembers(i) > 0)
            return false;
    }
    /// Check if active Trait is close enough to its equilibrium
    double diff = TraitHistory[chosen].back() - ExpectedMonomorph[chosen];
    if(diff > 0.5/TraitClass::K || diff < -0.5/TraitClass::K)
        return false;
    return true;
}

void GraphClass::reserveSize(const int maxIt)
{
    for(int i = 0; i < TraitClass::Size; ++i){
        TimeHistory[i].reserve(maxIt);
        TraitHistory[i].reserve(maxIt);
    }
}

void GraphClass::makeJumpedEvSteps(int & Chosen, double & Time)
{
    for(int i = 0; i < jumpedSteps; ++i){
        Manager.EvolutionStep();
        Time += Manager.Events.EventTimes * 1;   //FIXME: make right convert into milliseconds
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
    TimeHistory[Chosen].push_back(Time);
    TraitHistory[Chosen].push_back(Manager.getKMembers(Chosen));
    maxMembers = maxMembers < Manager.getKMembers(Chosen) ? Manager.getKMembers(Chosen) : maxMembers;
}

/// FIXME: Just finished! Make a Test after Appointment!
void GraphClass::iterateMutationPoint(double &time, int &chosen)
{
    storeCurrentPoint(time, chosen);
    time += sampleMutationTime(chosen);
    choseMutatedTrait(chosen);
    makeMutant();
    storeCurrentPoint(time,chosen);

//    double MutationTime = 0;
//    if(Chosen == 0){
//        MutationTime = Manager.Dice.rollExpDist(Manager.Trait[Chosen+1].TotalBirthRate);
//        Chosen = Chosen+1;
//    }
//    else if(Chosen == TraitClass::Size-1){
//        MutationTime = Manager.Dice.rollExpDist(Manager.Trait[Chosen-1].TotalBirthRate);
//        Chosen = Chosen-1;
//    }
//    else{
//        MutationTime = Manager.Dice.rollExpDist(Manager.Trait[Chosen+1].TotalBirthRate + Manager.Trait[Chosen-1].TotalBirthRate);
//        Chosen = Chosen-1 + Manager.Dice.rollDiscrUnifDist(0,1)*2;
//    }
//    TimeLine[Manager.Events.ChosenTrait].push_back( Time + MutationTime);
//    TraitHistory[Manager.Events.ChosenTrait].push_back(ExpectedMonomorph[Manager.Events.ChosenTrait]);

//    Manager.Events.EventTimes = MutationTime;
//    Manager.Events.ChosenTrait = Chosen;
//    Manager.Events.isBirth = true;
//    Time += MutationTime;
//    TimeLine[Chosen].push_back(Time);
//    Manager.executeEventTypeOnTrait();
//    TraitHistory[Chosen].push_back(Manager.getKMembers(Chosen));
}


double GraphClass::sampleMutationTime(const int &chosen)
{
    double Rate = TraitClass::Mutation * Manager.Trait[chosen].TotalBirthRate;
    if(chosen == 0 || chosen == TraitClass::Size-1)
        Rate /= 2;
    Manager.Events.EventTimes = Manager.Dice.rollExpDist(Rate);
    return Manager.Dice.rollExpDist(Rate);
}

void GraphClass::storeCurrentPoint(double &Time, int &chosen)
{
    TimeHistory[chosen].push_back(Time);
    TraitHistory[chosen].push_back(Manager.getKMembers(chosen));
}

void GraphClass::choseMutatedTrait(int &chosen)
{
    if(chosen == 0)
        chosen = 1;
    else if(chosen == TraitClass::Size-1)
        chosen = TraitClass::Size-1;
    else
        chosen += -1 + 2*Manager.Dice.rollDiscrUnifDist(0,1);
    Manager.Events.ChosenTrait = chosen;
}

void GraphClass::makeMutant()
{
    Manager.Events.isBirth = true;
    Manager.executeEventTypeOnTrait();
}

int GraphClass::makeIterations(const int maxIt)
{
    int chosen;
    double time = 0;
    for(int i = 0; i < maxIt; i++){
        iterateGraphPoint(time, chosen);
        if(isRangeControled)
            if(isNearDimorph()){
                for(int j = 0; j < std::min(i/3, maxIt-i); ++j)
                    iterateGraphPoint(time, chosen);
                return i*jumpedSteps + std::min(i/3, maxIt-i)*jumpedSteps;
            }
    }
    return maxIt*jumpedSteps;
}
#include <QDebug>
int GraphClass::makeTSSIterations(const int maxIt)
{
    int chosen;
    double time = 0;
    for(int i = 0; i < maxIt; ++i){
        iterateGraphPoint(time, chosen);
        if(isNearTSS(chosen)){
            iterateMutationPoint(time, chosen);
            if(chosen == 1)
                qDebug()<<"1. Invasion:"<<time;
            if(chosen == 2)
                qDebug()<<"2. Invasion:"<<time;
        }
        if(Manager.getKMembers(2) > ExpectedMonomorph[2]){
            for(int i = 0; i < TraitClass::Size; ++i){
                qDebug()<< i+1 <<". Birthrate"<< Manager.Trait[i].TotalBirthRate;
            }
            qDebug()<<"Terminated after:"<<time;
            return i*jumpedSteps;
        }
    }
    for(int i = 0; i < TraitClass::Size; ++i){
        qDebug()<< i+1 <<". Birthrate"<< Manager.Trait[i].TotalBirthRate;
    }
    qDebug()<<"Not Terminated:"<<time;
    return maxIt*jumpedSteps;
}

int GraphClass::generateEvolution(int maxIt)
{
    calcJumpedSteps(maxIt);
    reserveSize(maxIt);
    return makeTSSIterations(maxIt);
}

double GraphClass::getMaxMembers() const
{
    return maxMembers;
}

double GraphClass::getMaxTime() const
{
    double max = 0;
    for(int i = 0; i < TraitClass::Size; ++i)
        if(max < TimeHistory[i].back())
            max = TimeHistory[i].back();
    return max;
}

QVector<double> GraphClass::getTimesOf(const int i) const
{
    return TimeHistory.at(i);
}

QVector<double> GraphClass::getTraitHistOf(const int i) const
{
    return TraitHistory.at(i);
}

QVector<double> GraphClass::getExpectedDimorphOf(const int i) const
{
    QVector<double> ExpV;
    ExpV.push_back(ExpectedDimorph[i]);
    ExpV.push_back(ExpectedDimorph[i]);
    return ExpV;
}

QVector<double> GraphClass::getExpectedMonomorphOf(const int i) const
{
    QVector<double> ExpV;
    ExpV.push_back(ExpectedMonomorph[i]);
    ExpV.push_back(ExpectedMonomorph[i]);
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
    return ExpectedDimorph.at(i);
}
