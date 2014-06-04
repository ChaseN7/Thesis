#include "graphclass.h"
#include <cmath>

GraphClass::GraphClass(QString FName, bool rangeChecked) : Manager(FName)
{
    TimeLine.resize(TraitClass::Size);
    TraitHistory.resize(TraitClass::Size);
    ExpectedDimorph.resize(TraitClass::Size);
    ExpectedDimorph = Manager.retStableDimorphKVector();
    ExpectedMonomorph = Manager.retStableMonoKVector();
    maxMembers = 0;
    maxTime = 0;
    jumpedSteps = 1;
    isRangeControled = rangeChecked;
    for(int i = 0; i < TraitClass::Size; ++i){
        TimeLine[i].push_back(0);
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

bool GraphClass::isNearTSS() const
{
    /// Check that there is only one surviver and store him in "activeTrait"
    int activeTrait = -1;
    for(int i = 0; i < TraitClass::Size; ++i){
        if(activeTrait * TraitHistory[i].back() < 0)
            activeTrait = i;
        if(activeTrait * TraitHistory[i].back() > 0)
            return false;
    }
    /// Check if active Trait is close enough to its equilibrium
    double diff = TraitHistory[activeTrait].back() - ExpectedMonomorph[activeTrait];
    if(diff > pow(10,-10) || diff < -pow(10,-10))
        return false;
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
    TimeLine[Chosen].push_back(Time);
    TraitHistory[Chosen].push_back(Manager.getKMembers(Chosen));
    maxMembers = maxMembers < Manager.getKMembers(Chosen) ? Manager.getKMembers(Chosen) : maxMembers;
}

/// FIXME: Just finished! Make a Test after Appointment!
void GraphClass::iterateMutationPoint(double &Time, int &Chosen)
{
    RandomDice Dice;
    double MutationTime;
    if(Chosen == 0){
        MutationTime = Dice.rollExpDist(Manager.Trait[Chosen+1].TotalBirthRate);
        Chosen = Chosen+1;
    }
    else if(Chosen == TraitClass::Size-1){
        MutationTime = Dice.rollExpDist(Manager.Trait[Chosen-1].TotalBirthRate);
        Chosen = Chosen-1;
    }
    else{
        MutationTime = Dice.rollExpDist(Manager.Trait[Chosen+1].TotalBirthRate + Manager.Trait[Chosen-1].TotalBirthRate);
        Chosen = Chosen-1 + Dice.rollDiscrUnifDist(0,1)*2;
    }
    Manager.Events.EventTimes = MutationTime;
    Manager.Events.ChosenTrait = Chosen;
    Manager.Events.isBirth = true;
    Time += MutationTime;
    TimeLine[Chosen].push_back(Time);
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

int GraphClass::makeTSSIterations(const int maxIt)
{
    int chosen;
    double time = 0;
    for(int i = 0; i < maxIt; i++){
        iterateGraphPoint(time, chosen);
        if(isNearTSS()){
            iterateMutationPoint(time, chosen);
            return maxIt*jumpedSteps + 1;
        }
    }
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
