#include <iostream>
#include <fstream>
#include <QFile>
#include <vector>
#include <cmath>
#include "traiteventmanager.h"

TraitEventManager::TraitEventManager():
    Dice(),
    Trait(),
    Events()
{

}

TraitEventManager::TraitEventManager(int n):
    Dice(),
    Trait(),
    Events()
{
    Trait.assign(n,TraitClass());
    TraitClass::setTraitSize(n);
}
TraitEventManager::TraitEventManager(QString FileName):
    Dice(),
    Trait(),
    Events()
{
    if(initWithFile(FileName))
        calculateEventRates();
}


//void TraitEventManager::addTotalCompDeathRateOf(int i)
//{
//    double extDeath = 0;
//    for(int j = 0; j < TraitClass::Size; j++)
//        extDeath += TraitClass::CompDeathRate.at(i).at(j) * Trait[j].Members;
//    extDeath *= Trait[i].Members;
//    Trait[i].TotalDeathRate += extDeath;
//}

//void TraitEventManager::setTotalIntrisicDeathRateOf(int i)
//{
//    Trait[i].TotalDeathRate = (Trait[i].DeathRate)*(Trait[i].Members);
//}

//void TraitEventManager::calculateTotalDeathRates()
//{
//    for(int k = 0; k < TraitClass::Size; ++k){
//        setTotalIntrisicDeathRateOf(k);
//        addTotalCompDeathRateOf(k);
//    }
//}

//void TraitEventManager::calculateTotalBirthRates()
//{
//    int n = TraitClass::Size;
//    for(int k = 0; k < n; ++k)
//        Trait[k].TotalBirthRate = (Trait[k].Members)*(Trait[k].BirthRate);
//    for(int k = 1; k < n-1; ++k){
//        Trait[k].TotalBirthRate += 0.5*(Trait[k-1].Members)*(Trait[k-1].BirthRate)*(TraitClass::Mutation);
//        Trait[k].TotalBirthRate += 0.5*(Trait[k+1].Members)*(Trait[k+1].BirthRate)*(TraitClass::Mutation);
//    }
//    Trait[n-1].TotalBirthRate += 0.5*(Trait[n-2].Members)*(Trait[n-2].BirthRate)*(TraitClass::Mutation);
//    Trait[0].TotalBirthRate += 0.5*(Trait[1].Members)*(Trait[1].BirthRate)*(TraitClass::Mutation);
//}

//void TraitEventManager::calculateTotalEventRate()
//{
//    for(int i = 0; i < TraitClass::Size; i++){
//        Trait[i].TotalTraitRate = Trait[i].TotalBirthRate + Trait[i].TotalDeathRate;
//        TraitClass::TotalEventRate += Trait[i].TotalTraitRate;
//    }
//}

//void TraitEventManager::calculateEventRates()
//{
//    calculateTotalDeathRates();
//    calculateTotalBirthRates();
//    calculateTotalEventRate();
//}


void TraitEventManager::addTotalCompDeathRateOf(int i)
{
    double extDeath = 0;
    for(int j = 0; j < TraitClass::Size; j++)
        extDeath += TraitClass::CompDeathRate.at(i).at(j) * Trait[j].Members;
    extDeath *= Trait[i].Members;
    Trait[i].TotalDeathRate += extDeath;
}

void TraitEventManager::addTotalIntrisicDeathRateOf(int i)
{
    Trait[i].TotalDeathRate += (Trait[i].DeathRate)*(Trait[i].Members);
}

void TraitEventManager::calculateTotalDeathRateOf(int TraitIndex)
{
    Trait[TraitIndex].TotalDeathRate = 0;
    addTotalCompDeathRateOf(TraitIndex);
    addTotalIntrisicDeathRateOf(TraitIndex);
}

void TraitEventManager::calculateTotalDeathRates()
{
    for(int k = 0; k < TraitClass::Size; ++k){
        Trait[k].TotalDeathRate = 0;
        addTotalCompDeathRateOf(k);
        addTotalIntrisicDeathRateOf(k);
    }
}

void TraitEventManager::calculateTotalBirthRates()
{
    int n = TraitClass::Size;
    for(int k = 0; k < n; ++k)
        Trait[k].TotalBirthRate = (Trait[k].Members)*(Trait[k].BirthRate);
    for(int k = 1; k < n-1; ++k){
        Trait[k].TotalBirthRate += 0.5*(Trait[k-1].Members)*(Trait[k-1].BirthRate)*(TraitClass::Mutation);
        Trait[k].TotalBirthRate += 0.5*(Trait[k+1].Members)*(Trait[k+1].BirthRate)*(TraitClass::Mutation);
    }
    Trait[n-1].TotalBirthRate += 0.5*(Trait[n-2].Members)*(Trait[n-2].BirthRate)*(TraitClass::Mutation);
    Trait[0].TotalBirthRate += 0.5*(Trait[1].Members)*(Trait[1].BirthRate)*(TraitClass::Mutation);
}


void TraitEventManager::calculateTotalEventRate()
{
    TraitClass::TotalEventRate = 0;
    for(int i = 0; i < TraitClass::Size; i++){
        Trait[i].TotalTraitRate = Trait[i].TotalBirthRate
                                    + Trait[i].TotalDeathRate;
        TraitClass::TotalEventRate += Trait[i].TotalTraitRate;
    }
}

void TraitEventManager::calculateEventRates()
{
//    for(int i = 0; i < TraitClass::Size; i++){
//        calculateTotalDeathRateOf(i);
//    }
    calculateTotalDeathRates();
    calculateTotalBirthRates();
    calculateTotalEventRate();
}

void TraitEventManager::sampleEventTime()
{
    double Parameter = TraitClass::TotalEventRate;
    double newEvent = Dice.rollExpDist(Parameter);
    Events.EventTimes = newEvent;
}

void TraitEventManager::choseTraitToChange()
{
    double Parameter = TraitClass::TotalEventRate;
    double HittenTrait = Dice.rollContUnifDist(Parameter);
    for(int i = 0; i < TraitClass::Size; i++){
        if(HittenTrait <= Trait[i].TotalTraitRate){
            Events.ChosenTrait = i;
            return;
        }
        HittenTrait -= Trait[i].TotalTraitRate;
    }
}

void TraitEventManager::choseEventType()
{
    int i = Events.ChosenTrait;
    double EventType = Dice.rollContUnifDist(Trait[i].TotalTraitRate);
    if(EventType < Trait[i].TotalBirthRate)
        Events.isBirth = true;
    else
        Events.isBirth = false;
}

void TraitEventManager::executeEventTypeOnTrait()
{
    int ChosenTrait = Events.ChosenTrait;
    if(Events.isBirth){
        Trait[ChosenTrait].Members += 1.;
    }
    else if(Trait[ChosenTrait].Members > 0)
        Trait[ChosenTrait].Members -= 1.;
}

void TraitEventManager::changeATrait()
{
    choseTraitToChange();
    choseEventType();
    executeEventTypeOnTrait();
}

void TraitEventManager::EvolutionStep()
{
    calculateEventRates();
    sampleEventTime();
    changeATrait();
}

void TraitEventManager::ImprovedEvolutionStep()
{
    sampleEventTime();
    changeATrait();
    adjustNewEventRates();
}

// ------------------ Performence Improvement start -----------------

void TraitEventManager::adjustNewEventRates()
{
    int currentTrait = Events.ChosenTrait;
    int sgn;
    if(Events.isBirth)
        sgn = 1;
    else
        sgn = -1;

    // Intrinsic Deathrates
    Trait[currentTrait].TotalDeathRate += sgn*Trait[currentTrait].DeathRate;
    // Extrinsic Deathrate
    for(int i = 0; i < TraitClass::Size; ++i)
        Trait[currentTrait].TotalDeathRate += sgn*TraitClass::CompDeathRate.at(i).at(currentTrait);
    // Birthrates and TraitRates
    Trait[currentTrait].TotalBirthRate += sgn*Trait[currentTrait].BirthRate;
    Trait[currentTrait].TotalTraitRate = Trait[currentTrait].TotalBirthRate + Trait[currentTrait].TotalDeathRate;
    if(currentTrait > 0){
        Trait[currentTrait-1].TotalBirthRate += sgn*TraitClass::Mutation*Trait[currentTrait].BirthRate*0.5;
        Trait[currentTrait-1].TotalTraitRate = Trait[currentTrait-1].TotalBirthRate + Trait[currentTrait-1].TotalDeathRate;
    }
    if(currentTrait < TraitClass::Size -1){
        Trait[currentTrait+1].TotalBirthRate += sgn*TraitClass::Mutation*Trait[currentTrait].BirthRate*0.5;
        Trait[currentTrait+1].TotalTraitRate = Trait[currentTrait+1].TotalBirthRate + Trait[currentTrait+1].TotalDeathRate;
    }
    TraitClass::TotalEventRate = 0;
    for(int i = 0; i < TraitClass::Size; ++i)
        TraitClass::TotalEventRate += Trait[i].TotalTraitRate;

}

// ------------------ Performence Improvement end -----------------

void TraitEventManager::clearData()
{
    TraitClass::setTraitSize(0);
    Events.clearEvents();
    Trait.clear();
}

bool TraitEventManager::initWithFile(QString FName)
{
    FileStreaming Stream;
    try{
        if(Stream.initializeWithFile(FName, Trait)){
            calcFitness();
            return true;
        }
        throw -1;
    }
    catch(int e){
        return false;
    }

}

double TraitEventManager::getKMembers(int TraitIndex) const
{
    return Trait[TraitIndex].Members / TraitClass::K;
}

double TraitEventManager::retStableDimorphKOf(int i) const
{
    int j;
    if(i > 0)
        j = 0;
    else
        j = 1;
    double expected;

    expected = (Trait[i].BirthRate - Trait[i].DeathRate)
                * TraitClass::CompDeathRate[j][j];
    expected -= (Trait[j].BirthRate - Trait[j].DeathRate)
                * TraitClass::CompDeathRate[i][j];

    double devisor = TraitClass::CompDeathRate[j][j]*TraitClass::CompDeathRate[i][i]
            - TraitClass::CompDeathRate[j][i]*TraitClass::CompDeathRate[i][j];
    if(devisor != 0)
        expected /= devisor;
    else
        expected = -1.;

    return expected/TraitClass::K;
}

QVector<double> TraitEventManager::retStableDimorphKVector() const
{
    QVector<double> expVals(TraitClass::Size);
    for(int i = 0; i < TraitClass::Size; ++i)
        expVals[i] = retStableDimorphKOf(i);
    return expVals;
}

QVector<double> TraitEventManager::retStableMonoKVector() const
{
    QVector<double> expVals(TraitClass::Size);
    for(int i = 0; i < TraitClass::Size; ++i)
        expVals[i] = retStableKMonoOf(i);
    return expVals;
}

double TraitEventManager::retStableKMonoOf(int i) const
{
    double expected = Trait[i].BirthRate /** (1-TraitClass::Mutation)*/ - Trait[i].DeathRate;
    double divisor = TraitClass::CompDeathRate[i][i];
    if(divisor > 0){
        expected /= TraitClass::CompDeathRate[i][i];
        return expected/TraitClass::K;
    }
    return -1.;
}

bool TraitEventManager::isNear(QVector<double> &Expected)
{
    bool close = true;
    double diff;
    for(int i = 0; i < TraitClass::Size; i++){
        diff = fabs(getKMembers(i) - Expected[i]);
        close = close && diff < 15./sqrt(TraitClass::K) && diff > -15./sqrt(TraitClass::K);
    }
    return close;
}

void TraitEventManager::calcFitness()
{
    for(int i = 0; i < TraitClass::Size; ++i){
        for(int j = 0; j < TraitClass::Size; ++j){
            double tmp = Trait[j].BirthRate /** (1 - TraitClass::Mutation)*/ - Trait[i].DeathRate - TraitClass::CompDeathRate[i][j] * TraitClass::K * retStableKMonoOf(i);
            TraitClass::Fitness[i][j] = round(tmp*pow(10,14))/pow(10,14);
        }
    }
}





